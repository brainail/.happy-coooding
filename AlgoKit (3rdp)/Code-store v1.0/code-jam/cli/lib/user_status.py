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

"""Classes and methods to get current user's status."""



import httplib
import json
import sys
import time

from lib import error
from lib import http_interface


def _ClusterByGroups(data, group_size):
  return zip(*[iter(data)] * group_size)


class ProblemInputStatus(object):
  def __init__(self, input_type, solved_time, wrong_tries, current_attempt,
               submitted):
    """Constructor.

    Args:
      input_type: Either 'small' or 'large'.
      solved_time: Number of seconds elapsed since the beginning of the contest
          at which this problem input was solved, or -1 if it has not been
          solved yet.
      wrong_tries: How many wrong tries have been done for this problem input,
          does not include the current one.
      current_attempt: Number of seconds left to submit the output for the
          current attempt for this problem input, or -1 if there is no timer
          active for this problem input.
      submitted: Boolean indicating if there is an output submitted for this
          problem input.
    """
    self.input_type = input_type
    self.solved_time = solved_time
    self.wrong_tries = wrong_tries
    self.current_attempt = current_attempt
    self.submitted = submitted


class UserStatus(object):
  def __init__(self, rank, points, problem_inputs):
    """Constructor.

    Args:
      rank: Position of the user in the scoreboard.
      points: Number of points of the user.
      problem_inputs: The position [p][i] contains the status for the input i of
          problem p.
    """
    self.rank = rank
    self.points = points
    self.problem_inputs = problem_inputs

  @staticmethod
  def FromJsonResponse(json_response, input_spec):
    """Construct an UserStatus object using a server json_response.

    Args:
      json_response: JSON response returned by the server when asked for the
          current user status.
      input_spec: List of (input_name, time_limit) tuples, each one specifying
          the type of inputs per problem.

    Returns:
      An UserStatus object with the information contained in the json_response,
      or None if the user is not participating/did not participate in this
      contest.

    Raises:
      error.ServerError: If there is a key missing from the server response.
    """
    try:
      # Extract the rank and check if the user is participating or participated
      # in this contest.
      rank = json_response['rank']
      if rank == -1:
        return None

      # Extract problem information from the response and create problem input
      # status objects for each problem.
      json_attempts = json_response['a']
      json_solved_time = json_response['s']
      json_current = json_response['p']
      json_submitted = json_response['submitted']
      plain_problem_inputs = []
      for index, (attempts, solved, current_passed, submitted) in enumerate(zip(
          json_attempts, json_solved_time, json_current, json_submitted)):
        # Remove the correct submission and the current attempt from the wrong
        # tries, if any.
        wrong_tries = attempts
        if solved != -1: wrong_tries -= 1
        if current_passed != -1: wrong_tries -= 1

        # Get the input type and time left for this input, then create a problem
        # input status object for it.
        input_type, total_time = input_spec[index % len(input_spec)]
        time_left = -1 if current_passed == -1 else total_time - current_passed
        plain_problem_inputs.append(ProblemInputStatus(
            input_type, solved, wrong_tries, time_left, bool(submitted)))

      # Extract the user status and clusterize the problem inputs. Then return
      # an user status object with the extracted information.
      points = json_response['pts']
      problem_inputs = _ClusterByGroups(plain_problem_inputs, len(input_spec))
      return UserStatus(rank, points, problem_inputs)

    except KeyError as e:
      raise error.ServerError('Cannot find needed key in server status '
                              'response: {0}.\n'.format(e))


def GetUserStatus(host, cookie, middleware_token, contest_id, input_spec):
  """Get the current user's status from the server.

  Args:
    host: Domain name of the server where the contest is running.
    cookie: Cookie for the current user.
    middleware_token: Middleware authentication token for the current user.
    contest_id: Id of the contest where the user is participating.
    input_spec: Dictionary with the input specification, mapping from input name
        to another dictionary with a 'time_limit' key.

  Returns:
    An UserStatus object with the current user's status.

  Raises:
    error.ConfigurationError: If there is an input specification without time
      limit.
    error.NetworkError: If a network error occurs while communicating with the
      server.
    error.ServerError: If the server answers code distinct than 200 or the
      response is a malformed JSON.
  """
  # Send an HTTP request to get the user status.
  sys.stdout.write('Getting user status at contest {0} from "{1}"...\n'.format(
      contest_id, host))
  request_referer = 'http://{0}/codejam/contest/dashboard?c={1}'.format(
      host, contest_id)
  request_arguments = {
      'cmd': 'GetUserStatus',
      'contest': contest_id,
      'zx': str(int(time.time())),
      'csrfmiddlewaretoken': str(middleware_token),
      }
  request_headers = {
      'Referer': request_referer,
      'Cookie': cookie,
      }
  try:
    status, reason, response = http_interface.Get(
        host, '/codejam/contest/dashboard/do', request_arguments,
        request_headers)
  except httplib.HTTPException as e:
    raise error.NetworkError('HTTP exception while user status from the Google '
                             'Code Jam server: {0}.\n'.format(e))

  # Check if the status is not good.
  if status != 200 or reason != 'OK':
    raise error.ServerError('Error while communicating with the server, cannot '
                            'get user status. Check that the host, username '
                            'and contest id are valid.\n')

  # Sort and extract information from the input specification.
  try:
    parsed_input_spec = [
        (input_data['input_id'], input_name, input_data['time_limit'])
        for input_name, input_data in input_spec.iteritems()]
    parsed_input_spec.sort()
    input_spec = [input_data[1:] for input_data in parsed_input_spec]
  except KeyError:
    raise error.ConfigurationError('Wrong input specification, "time_limit" '
                                   'key not found.\n')

  # Parse the JSON response and return an object with the user status.
  try:
    json_response = json.loads(response)
    return UserStatus.FromJsonResponse(json_response, input_spec)
  except ValueError as e:
    raise error.ServerError('Invalid response received from the server, cannot '
                            'get user status. Check that the contest id is '
                            'valid: {0}.\n'.format(e))
