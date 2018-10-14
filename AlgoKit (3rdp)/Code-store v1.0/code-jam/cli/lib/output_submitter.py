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

"""This module exposes a class to submit solutions to the codejam server."""



import httplib
import json
import os
import random
import shutil
import sys

from lib import error
from lib import http_interface
from lib import multipart_data
from lib import zip_utils


class OutputSubmitter(object):
  """Class to submit outputs from a specific problem."""
  def __init__(self, host, cookie, middleware_token, contest_id, problem_id):
    """Initialize an output submitter for a specific problem.

    Args:
      host: Name of the server running the contest.
      cookie: Cookie obtained when the user authenticated in the server.
      middleware_token: Input token scrapped from the dashboard.
      contest_id: Identifier of the running contest.
      problem_id: Identifier of the problem whose input must be downloaded.
    """
    self.host = host
    self.cookie = cookie
    self.middleware_token = middleware_token
    self.contest_id = contest_id
    self.problem_id = problem_id

  def _PrepareSourceFiles(self, source_names):
    """ Zip all source directories into files and return a list with the names
    of the zipped files, the ignored zips and the temporary files to erase, that
    includes the zipped files.

    Args:
      source_names: List with all the files to include with the solution.

    Returns:
      A tuple with three elements: a list with the zipped files names, a list
      with the internal, ignored zip files, and a list with the temporary files
      that should be erased.
    """
    # Initialze set for the source names, the ignored zip files and all
    # temporary created files.
    new_source_names = set()
    ignored_zips = set()
    tmp_files = set()

    # Process each source specified by the user.
    for source in source_names:
      # Check if the source is a directory or a file.
      if os.path.isdir(source):
        # Create a zip file for the folder and add it to the prepared sources
        # and the temporary files to erase.
        zip_filename = '{1}_{0}.zip'.format(random.randrange(0, 2**31 - 1),
                                            source.replace('\\', '_').replace(
                                                '/', '_'))
        sys.stdout.write('Compressing directory "{0}" into file '
                         '"{1}"...'.format(source, zip_filename))
        ignored_zips.update(zip_utils.MakeZipFile([source], zip_filename,
                                                  ['.zip']))
        new_source_names.add(zip_filename)
        tmp_files.add(zip_filename)
      else:
        # Add files directly to the prepared sources.
        new_source_names.add(source)

    # Return all generated sets.
    return new_source_names, ignored_zips, tmp_files

  def _ParseResult(self, response_data, input_public):
    """Extract the result from the server response data.

    Args:
      response_data: The response body obtained from the server, which is
        formatted like a python dictionary.
      input_public: Boolean indicating whether the answer is public or not.

    Returns:
      The returned message from the server, or the string 'No message found' if
      there was no answer message.

    Raises:
      error.ServerError: If the server response is malformed.
    """
    # Convert the response data to a dictionary and return the message.
    try:
      result = json.loads(response_data)
      msg = result.get('msg', 'No message found')
      if not result.get('hasAnswer', False):
        return 'Rejected: ' + msg
      elif not input_public:
        return 'Submitted: ' + msg
      elif result.get('ok', False):
        return 'Correct: ' + msg
      else:
        return 'Incorrect: ' + msg
    except ValueError as e:
      raise error.ServerError('Invalid response received from the server, '
                              'cannot submit solution. Check that the host, '
                              'user and contest id are valid: {0}.\n'.format(e))

  def Submit(self, input_id, output_name, source_names, input_public,
             gzip_body=True, zip_sources=False, add_ignored_zips=False):
    """Submit the specified output and sources file to the problem.

    Args:
      input_id: Identifier of the output to submit ('0' for the small output,
        '1' for the large output).
      output_name: Name of the file with the output data.
      source_names: Names of the source files to be included with the output.
      input_public: Boolean indicating whether the answer is public or not.
      gzip_body: Boolean indicating whether the body has to be gzipped or not.
      zip_sources: Boolean indicating whether all sources should be put inside a
        zip file or not.
      add_ignored_zips: Boolean indicating whether zip files that are not
        included directly but are inside a included directory should be
        submitted or not.

    Raises:
      error.InternalError: If an error occurs while copying ignored zip files
        to the final location.
      error.NetworkError: If a network error occurs while communicating with the
        server.
      error.ServerError: If the server answers code distinct than 200.
    """
    # Prepare the source files (zipping all directories). After this,
    # source_names will only contain text files and zip files specified directly
    # or by compressing a directory.
    source_names, ignored_zips, tmp_files=self._PrepareSourceFiles(
        set(source_names))

    try:
      # Check if the user requested to zip source files.
      if zip_sources:
        # Generate a random name for the zipped source files and print message.
        zip_filename = '__plain_files_{0}.zip'.format(
            random.randrange(0, 2**31 - 1))
        sys.stdout.write('Compressing files "{1}" into file "{0}"...\n'.format(
            zip_filename, ', '.join(
                source for source in source_names
                if os.path.splitext(source)[1] != '.zip')))

        # Fill the zip file with the remaining text sources (ignoring zip
        # files). Then, substitute the list with the ignored zip files and the
        # new one, adding it to the temporary file list.
        source_names = zip_utils.MakeZipFile(
            source_names, zip_filename, ignore_exts = ['.zip'])
        source_names.add(zip_filename)
        tmp_files.add(zip_filename)

      # Check if the user requested to add the ignored zip files inside
      # included directories.
      if add_ignored_zips:
        # Copy and add each ignored file to the source list.
        for ignored_zip in ignored_zips:
          # Generate the zip copy filename by substituting path with underscores
          # and adding a random number to prevent collisions.
          path, ext = os.path.splitext(ignored_zip)
          zip_copy_filename = '{1}_{0}{2}'.format(
              random.randrange(0, 2**31 - 1),
              path.replace('\\', '_').replace('/', '_'), ext)
          sys.stdout.write('Copying file "{1}" to temporary file '
                           '"{0}"...\n'.format(zip_copy_filename,
                                               os.path.basename(ignored_zip)))

          # Make a copy of the ignored zip file and add the copy to the sources
          # list and the temporary list.
          try:
            shutil.copy(ignored_zip, zip_copy_filename)
            source_names.add(zip_copy_filename)
            tmp_files.add(zip_copy_filename)
          except OSError as e:
            raise error.InternalError('OS error happened while copying zip '
                                      'file "{0}" to "{1}": {2}.\n'.format(
                                          ignored_zip, zip_copy_filename, e))

      # Print message and check that at least one source file was included.
      if source_names:
        sys.stdout.write('Sending output file "{0}" and source(s) {1} to "{2}"'
                         '...\n'.format(output_name,
                                        ', '.join('"{0}"'.format(source)
                                                  for source in source_names),
                                        self.host))
      else:
        # Print warning saying that no source file is being included, this might
        # cause disqualification in a real contest.
        sys.stdout.write('Warning, no source files are being sent for output '
                         'file "{0}"!\n'.format(output_name))
        sys.stdout.write('Sending output file "{0}" to "{1}"...\n'.format(
            output_name, self.host))

      # Generate a random boundary string to separate multipart data and
      # create a multipart data object with it. Then fill it with the necessary
      # arguments.
      multipart_boundary = '----gcjMultipartBoundary{0}'.format(
          random.randrange(0, 2**31 - 1))
      body_data = multipart_data.MultipartData(multipart_boundary)
      body_data.AddString('csrfmiddlewaretoken', self.middleware_token)
      body_data.AddFile('answer', output_name)
      for i, source in enumerate(source_names):
        body_data.AddFile('source-file{0}'.format(i), source)
        body_data.AddString('source-file-name{0}'.format(i), source)
      body_data.AddString('cmd', 'SubmitAnswer')
      body_data.AddString('contest', self.contest_id)
      body_data.AddString('problem', self.problem_id)
      body_data.AddString('input_id', input_id)
      body_data.AddString('num_source_files', str(len(source_names)))

      # Get the message body and check if compression was requested.
      request_body = str(body_data)
      if gzip_body:
        compressed_body = zip_utils.ZipData(request_body)
        sys.stdout.write('Sending {0} bytes to server ({1} uncompressed)'
                         '...\n'.format(len(compressed_body),
                                        len(request_body)))
        request_body = compressed_body
      else:
        sys.stdout.write('Sending {0} bytes to server...\n'.format(
            len(request_body)))

      # Send an HTTP request with the output file and the source files.
      request_url = '/codejam/contest/dashboard/do'
      request_referer = 'http://{0}/codejam/contest/dashboard?c={1}'.format(
          self.host, self.contest_id)
      request_arguments = {}
      request_headers = {
          'Content-Encoding': 'gzip' if gzip_body else 'text/plain',
          'Content-Type': 'multipart/form-data; boundary={0}'.format(
              multipart_boundary),
          'Referer': request_referer,
          'Cookie': self.cookie,
          }
      try:
        status, reason, response = http_interface.Post(
            self.host, request_url, request_arguments, request_headers,
            request_body)
      except httplib.HTTPException as e:
        raise error.NetworkError('HTTP exception while sending solution to the '
                                 'Google Code Jam server: {0}.\n'.format(e))

      # Check if the status is not good.
      if status != 200 or reason != 'OK':
        raise error.ServerError('Error while communicating with the server, '
                                'cannot submit solution. Check that the host, '
                                'username and contest id are valid.\n')

      # Check if the server accepted the input or just ignored it. If it
      # accepted it, parse the response and print the submission result.
      if response:
        submit_result = self._ParseResult(response, input_public)
        sys.stdout.write('{0}\n'.format(submit_result))
      else:
        raise error.ServerError(
            'No response received from the server. This generally happens if '
            'you try to submit the large output before solving the small '
            'input.\n')

    finally:
      # Remove all temporary zip files. Do not exit in case of error, other
      # files might still be erased successfully.
      remove_errors = []
      for tmp_file in tmp_files:
        try:
          os.remove(tmp_file)
        except OSError as e:
          remove_errors.append('OS error while removing temporary file "{0}": '
                               '{1}.\n'.format(tmp_file, e))
      if remove_errors:
        raise error.InternalError('\n'.join(remove_errors))
