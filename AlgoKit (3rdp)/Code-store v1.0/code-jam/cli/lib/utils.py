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

"""Utility methods used to simplify code in the library and scripts."""



import datetime
import sys


def AskConfirmation(message, action, skip, sinput=sys.stdin, output=sys.stdout):
  """Ask for confirmation about something and return the user response.

  Args:
    message: Message shown to the user before asking.
    action: Verb with the action to be performed upon confirmation.
    skip: Boolean indicating if check should be skipped or not.
    sinput: Input file where confirmation should be read from.
    output: Output file where messages should be written to.

  Returns:
    True if the user confirmed the action of a skip was requested.
  """
  # If the confirmation should be skipped just show the message. Otherwise,
  # show the message and ask for confirmation.
  output.write(message)
  if skip:
    output.write('\n')
    return True
  else:
    output.write(' {0}? (y/N) '.format(action))
    user_input = sinput.readline()
    return user_input[:1].lower() == 'y'


def AskConfirmationOrDie(message, action, skip, sinput=sys.stdin,
                         output=sys.stdout, exit_value=1):
  """Ask for confirmation about something and abort on a negative answer.

  Args:
    message: Message shown to the user before asking.
    action: Verb with the action to be performed upon confirmation.
    skip: Boolean indicating if check should be skipped or not.
    sinput: Input file where confirmation should be read from.
    output: Output file where messages should be written to.
    exit_value: Process' return value to use when user didn't confirm.
  """
  # Ask for confirmation and exit if user didn't confirm.
  if not AskConfirmation(message, action, skip, sinput, output):
    output.write('Aborted.\n')
    sys.exit(exit_value)


def _AppendTimeToken(value, unit, tokens):
  # Only append non-null tokens, being careful for plural terminations.
  if value > 0:
    plural_terminator = 's' if value != 1 else ''
    tokens.append('%s %s%s' % (value, unit, plural_terminator))


def FormatHumanTime(seconds):
  """Format the number of seconds into a human readable string.

  This function expects to receive small values only (on the order of minutes),
  and will display minutes as the biggest unit.

  Args:
    seconds: Number of seconds to be formatted.

  Returns:
    A string with the formatted timestamp.
  """
  # If the seconds is null, just return 0 seconds.
  if seconds == 0:
    return '0 seconds'

  # Put the seconds into a datetime object and extract the minute and second
  # values, which then are returned in a human readable string.
  timestamp = datetime.datetime.fromtimestamp(seconds).time()
  tokens = []
  _AppendTimeToken(timestamp.minute, 'minute', tokens)
  _AppendTimeToken(timestamp.second, 'second', tokens)
  return ', '.join(tokens)


def GetIndexFromInputId(input_spec, input_id):
  """Get the 0-based index of the input_id inside input_spec.

  Args:
    input_spec: Dictionary with the input specification, mapping from input name
        to another dictionary with a 'time_limit' key.
    input_id: Id whose index must be retrieved.

  Returns:
    0-based index of the input_id inside input_spec.
  """
  # The index computation does not check if the input_id exists, so make a
  # separate check for it.
  if not any(input_data['input_id'] == input_id
             for _, input_data in input_spec.iteritems()):
    return None

  # The index of input_id is equivalent to the number of ids lower than it.
  return sum(1
             for _, input_data in input_spec.iteritems()
             if input_data['input_id'] < input_id)
