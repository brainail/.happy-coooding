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

"""This file implements the main function for the contest initializer, which
uses the ContestManager class in the lib directory."""

import os, sys, optparse
from lib import constants
from lib import data_manager
from lib import contest_manager
from lib import error

def main():
  """Main function for the contest initializer script.

  This script receives one positional argument, which is the contest id.
  """
  try:
    # Create an option parser and use it to parse the supplied arguments.
    program_version = 'GCJ contest crawler {0}'.format(
        constants.VERSION)
    parser = optparse.OptionParser(usage='%prog [options] contest_id',
                                   version=program_version)
    parser.add_option('-p', '--passwd', action='store', dest='password',
                      help=('Password used to login in the server, will be '
                            'asked if not specified'))
    options, args = parser.parse_args()

    # Check that the number of arguments is valid.
    if len(args) == 1:
        # Extract the contest id and initialize the contest.
        contest_id = args[0]
    else:
        # Attempt to read off contest_id from config file
        try:
            contest_data = data_manager.ReadData()
            contest_id = contest_data['contest_id']
        except KeyError as e:
            # Indicate that no host or cookie was configured and exit with error.
            raise error.ConfigurationError('No host or login cookie found in the '
                                           'configuration file: {0}.\n'.format(e))
            raise error.OptionError('requires single argument: contest_id')

    contest_manager.Initialize(contest_id, options.password)

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
