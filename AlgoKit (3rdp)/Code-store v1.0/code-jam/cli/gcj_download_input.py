#!/usr/bin/python2
# -*- coding: utf-8 -*-
#
# Copyright 2011 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""This file implements the main function for the input downloader, which uses
the InputDownloader class in the lib directory."""



import optparse
import os
import re
import sys

from lib import code_jam_login
from lib import constants
from lib import contest_manager
from lib import data_manager
from lib import error
from lib import google_login
from lib import input_downloader
from lib import user_status
from lib import utils


def main():
  """Main function for the input downloader script.

  This script receives three positional arguments, the problem letter, the input
  size and the submit id.
  """
  try:
    # Create an option parser and use it to parse the supplied arguments.
    program_version = 'GCJ input downloader {0}'.format(
        constants.VERSION)
    parser = optparse.OptionParser(usage='%prog [options] problem input id',
                                   version=program_version)
    parser.add_option('-l', '--login', action='store_true', dest='renew_cookie',
                      help='Ignore the stored cookie, and log in again')
    parser.add_option('-p', '--passwd', action='store', dest='password',
                      help=('Password used to log in. You will be prompted for '
                            'a password if one is required and this flag is '
                            'left empty and there is no password in the '
                            'configuration files'))
    parser.add_option('-f', '--force', action='store_true', dest='force',
                      help=('Skip check to verify that user wants to start a '
                            'new timer'))
    parser.add_option('-d', '--data-directory', action='store',
                      dest='data_directory',
                      help='Directory with the I/O files and main source files')
    parser.add_option('-i', '--input-name', action='store', dest='input_name',
                      help='Name of the file where the input should be stored')
    parser.set_defaults(renew_cookie=False, force=False)
    options, args = parser.parse_args()

    # Check that the number of arguments is valid.
    if len(args) != 3:
      raise error.OptionError('need 3 positional arguments')

    # Check that the problem idenfier is valid.
    problem_letter = args[0].upper()
    if len(problem_letter) != 1 or not problem_letter.isupper():
      raise error.OptionError('invalid problem {0}, must be one letter'.format(
          problem_letter))

    # Check that the submit id is a valid identifier.
    id = args[2]
    if not re.match('^\w+$', id):
      raise error.OptionError('invalid id {0}, can only have numbers, letters '
                              'and underscores'.format(id))

    # Check that the contest has been initialized.
    if not contest_manager.IsInitialized():
      raise error.ConfigurationError(
          'Contest is not initialized, please initialize the contest before '
          'trying to download input files.\n');

    # Read user and input information from the config file.
    try:
      current_config = data_manager.ReadData()
      host = current_config['host']
      user = current_config['user']
      input_spec = current_config['input_spec']
    except KeyError as e:
      raise error.ConfigurationError(
          'Cannot find all required user data in the configuration files: {0}. '
          'Please fill the missing fields in the user configuration '
          'file.\n'.format(e))

    # Check that the input type is valid.
    input_type = args[1].lower()
    if input_type not in input_spec:
      raise error.OptionError(
          'invalid input type {0}, must be one of ({1})'.format(
              input_type, ','.join(input_spec)))

    # Read current contest information from the config file.
    try:
      middleware_tokens = current_config['middleware_tokens']
      cookie = None if options.renew_cookie else current_config['cookie']
      contest_id = current_config['contest_id']
      problems = current_config['problems']
    except KeyError as e:
      raise error.ConfigurationError(
          'Cannot find all required contest data in configuration files: {0}. '
          'Reinitializing the contest might solve this error.\n'.format(e))

    # Get the needed middleware tokens to request the file and check for running
    # attempts.
    try:
      get_initial_values_token = middleware_tokens['GetInitialValues']
      download_input_token = middleware_tokens['GetInputFile']
      user_status_token = middleware_tokens['GetUserStatus']
    except KeyError as e:
      raise error.ConfigurationError(
          'Cannot find {0} token in configuration file. Reinitializing the '
          'contest might solve this error.\n'.format(e))

    # Calculate the problem index and check if it is inside the range.
    problem_index = ord(problem_letter) - ord('A')
    if problem_index < 0 or problem_index >= len(problems):
      raise error.UserError(
          'Cannot find problem {0}, there are only {1} problem(s).\n'.format(
              problem_letter, len(problems)))

    # Get the problem specification and the input id from the configuration.
    problem = problems[problem_index]
    try:
      input_id = input_spec[input_type]['input_id']
    except KeyError:
      raise error.ConfigurationError(
          'Input specification for "{1}" has no input_id.\n'.format(input_type))

    # Get the data directory from the options, if not defined, get it from the
    # configuration, using './source' as the default value if not found. In the
    # same way, get the input filename format.
    data_directory = (options.data_directory or
                      current_config.get('data_directory', './source'))
    input_name_format = (options.input_name or
                         current_config.get('input_name_format',
                                            '{problem}-{input}-{id}.in'))

    # Generate the input file name using the specified format and then return.
    try:
      input_basename = input_name_format.format(
          problem=problem_letter, input=input_type, id=id)
      input_filename = os.path.normpath(os.path.join(data_directory,
                                                     input_basename))
    except KeyError as e:
      # Print error message and exit.
      raise error.ConfigurationError(
          'Invalid input name format {0}, {1} is an invalid key, only use '
          '"problem", "input" and "id".\n'.format(input_name_format, e))

    # Print message indicating that an input is going to be downloaded.
    print '-' * 79
    print '{0} input for "{1} - {2}" at "{3}"'.format(
        input_type.capitalize(), problem_letter, problem['name'],
        input_filename)
    print '-' * 79

    # Renew the cookie if the user requested a new login or the cookie has
    # expired.
    if google_login.CookieHasExpired(cookie):
      print 'Cookie has expired, logging into the Code Jam servers...'
      cookie = None
    if not cookie or options.renew_cookie:
      cookie = code_jam_login.Login(options.password)

    # Get the contest status and check if it is accepting submissions.
    contest_status = contest_manager.GetContestStatus(
        host, cookie, get_initial_values_token, contest_id)
    if not options.force and not contest_manager.CanSubmit(contest_status):
      raise error.UserError('Cannot download inputs from this contest, its not '
                            'active or in practice mode.\n')

    # Get the user status and check if it is participating or not.
    input_index = utils.GetIndexFromInputId(input_spec, input_id)
    current_user_status = user_status.GetUserStatus(
        host, cookie, user_status_token, contest_id, input_spec)
    if (contest_status == contest_manager.ACTIVE and
        current_user_status is not None):
      # Check if this problem input can be downloaded or not. An input can be
      # downloaded as long as it has not been solved yet; a non-public input
      # also cannot have wrong tries.
      problem_inputs = current_user_status.problem_inputs
      problem_input_state = problem_inputs[problem_index][input_index]
      input_public = input_spec[input_type]['public']
      can_download = problem_input_state.solved_time == -1
      if not input_public:
        can_download = can_download and problem_input_state.wrong_tries == 0
      if not options.force and not can_download:
        raise error.UserError(
            'You cannot download {0}-{1}, it is already {2}.\n'.format(
                problem_letter, input_type,
                'solved' if input_public else ('submitted and the timer '
                                               'expired')))

      # Check if there is a pending attempt for this problem input. If there is
      # no pending attempt, show warning indicating that a new timer has
      # started.
      if problem_input_state.current_attempt == -1:
        # Show a warning message to the user indicating that a new input is
        # being downloaded, including the time available to solve it.
        remaining_time = input_spec[input_type]['time_limit']
        download_message = ('You will have {0} to submit your answer for '
                            '{1}-{2}.'.format(utils.FormatHumanTime(
                                remaining_time), problem_letter, input_type))
        utils.AskConfirmationOrDie(download_message, 'Download', options.force)
        print 'Downloading new input file.'
      else:
        # Show a message to the user indicating that the same input file is
        # being downloaded, including the time left to solve it.
        remaining_time = problem_input_state.current_attempt
        print ('You still have {0} to submit your answer for {1}-{2}.'.format(
            utils.FormatHumanTime(remaining_time), problem_letter, input_type))
        print 'Redownloading previous input file.'
    else:
      print 'Downloading practice input file.'

    # Create the input downloader and request the file.
    downloader = input_downloader.InputDownloader(
        host, cookie, download_input_token, contest_id, problem['id'])
    downloader.Download(input_id, input_filename)

  except error.OptionError as e:
    parser.print_usage()
    program_basename = os.path.basename(sys.argv[0])
    sys.stderr.write('{0}: error: {1}\n'.format(program_basename, e))
    sys.exit(1)

  except error.UserError as e:
    sys.stderr.write(str(e))
    sys.exit(1)

  except error.CommandlineError as e:
    sys.stderr.write('{0}: {1}'.format(e.__class__.__name__, e))
    sys.exit(1)


if __name__ == '__main__':
  main()
