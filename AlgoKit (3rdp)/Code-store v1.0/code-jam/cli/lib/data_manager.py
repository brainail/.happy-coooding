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

"""This module exposes two public function ReadData() and WriteData(), that
can be used to retrieve or put data into the configuration files."""



import re
import sys

from lib import constants
from lib import error

_INPUT_NAME_REGEXP = re.compile(r'^[a-z0-9_]+$')

_DEFAULT_DATA = {
    'input_spec': {'small': {'input_id': '0',
                             'time_limit': 4 * 60,
                             'public': True},
                   'large': {'input_id': '1',
                             'time_limit': 8 * 60,
                             'public': False},
                   }
    }


def _ReadDataImpl(filename):
  """Read the persistent data from the specified file, which should be
  formatted as a python dict.

  Args:
    filename: Name of the file with the data to load.

  Returns:
    A python dictionary with the file contents.

  Raises:
    error.InternalError: If there is any error while reading the data from the
      file.
  """
  # Open the specified file and get its contents. Then evaluate the file data
  # directly, as it is formatted as a python dict.
  try:
    file = open(filename, 'rt')
    file_data = file.read()
    file.close()
    return eval(file_data, {}, {})
  except IOError as e:
    raise error.InternalError('IO error happened while reading data from file '
                              '"{0}" : {1}.\n'.format(filename, e))


def _WriteDataImpl(data, filename):
  """Write the specified data to the specified file, which will
  be formatted as a python dict.

  Args:
    data: Python dictionary with the data to write to the file.
    filename: Name of the file where the data should be written.

  Raises:
    error.InternalError: If there is any error while writing the data to the
      file.
  """
  try:
    # Calculate the space needed for the keys and create a format string
    # for each data item.
    key_width = max(len(repr(key)) for key in data.iterkeys())
    item_format = '{0:%d} : {1},' % key_width

    # Open the file and store each item inside it.
    file = open(filename, 'wt')
    file.write('{\n');
    for key, value in sorted(data.iteritems()):
      item_line = item_format.format(repr(key), repr(value))
      file.write('{0}\n'.format(item_line))
    file.write('}\n');
    file.close()
  except IOError as e:
    raise error.InternalError('IO error happened while writing data to file '
                              '"{0}" : {1}.\n'.format(filename, e))


def _ValidateData(data):
  """Check that all configuration data is valid.

  Args:
    data: Dictionary with the configuration data to validate.

  Raises:
    error.ConfigurationError: If there is any invalid field in the
      configuration.
  """
  # There should be an user and it cannot be the default value.
  if 'user' not in data:
    raise error.ConfigurationError('Username was not found in user data '
                                   'file.\n')
  if data['user'] == 'your-name-here@gmail.com':
    raise error.ConfigurationError('Remember to set your username in the user '
                                   'configuration file "{0}".\n'.format(
                                       constants.USER_CONFIG_FILE))

  # All input type names should not contain only lowercase letters and digits.
  if 'input_spec' not in data:
    raise error.ConfigurationError('Input specification was not found in data '
                                   'files.\n')
  for input_name in data['input_spec']:
    if not _INPUT_NAME_REGEXP.match(input_name):
      raise error.ConfigurationError('Input name "{0}" in input specification '
                                     'is invalid, it should contain only '
                                     'lowercase letters and digits.\n'.format(
                                         input_name))


def ReadData(default_data=None):
  """Read tool configuration data.

  Args:
    default_data: Dictionary with default values for fields that do not appear
      in both configuration files.

  Returns:
    A dictionary with the validated configuration data.

  Raises:
    error.InternalError: If there is any problem while reading the user
      configuration file.
  """
  # Read the user data and check if it was read successfully.
  try:
    user_data = _ReadDataImpl(constants.USER_CONFIG_FILE)
  except error.InternalError:
    raise error.InternalError('Unable to read used data.\n')

  # Read the current contest data and show warning if not read successfully.
  try:
    current_data = _ReadDataImpl(constants.CURRENT_CONFIG_FILE)
  except error.InternalError:
    sys.stderr.write('Warning: Cannot read current data.\n')
    current_data = {}

  # Start with the default data, patch it with the current data and then with
  # the user's data, so the latter ones have more priority. Then validate and
  # return the data.
  final_data = dict(default_data or _DEFAULT_DATA)
  final_data.update(current_data)
  final_data.update(user_data)
  _ValidateData(final_data)
  return final_data


def WriteData(data):
  """Write tool configuration data into the current file.

  Args:
    data: Dictionary with tool configuration.

  Raises:
    error.InternalError: If there is any problem while writing the current
      configuration file.
  """
  # Just forward the data to the current configuration file, the user
  # configuration should not be changed by the tool.
  try:
    _WriteDataImpl(data, constants.CURRENT_CONFIG_FILE)
  except error.InternalError:
    raise error.InternalError('Cannot write data to the current '
                              'configuration.\n')
