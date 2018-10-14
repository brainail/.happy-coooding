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

"""This module contains functions used to zip or unzip data."""



import gzip
import os
import random
import zipfile

from lib import error


def UnzipData(zipped_data):
  """Unzip the specified data using a temporary file and the gzip library.
  After the data is unzipped, the temporary file is erased, so no special
  cleanup is necessary.

  Args:
    A byte array with the zipped data.

  Returns:
    A byte array with the unzipped data.

  Raises:
    error.InternalError: If any I/O or OS error occurs while unzipping the data.
  """
  # Write the zipped data into a temporary file (using a random name to prevent
  # collisions).
  try:
    zip_filename = 'tempZipFile_{0}.gz'.format(random.randrange(0, 2**31 - 1))
    zip_file = open(zip_filename, 'wb')
    zip_file.write(zipped_data)
    zip_file.close()
  except IOError as e:
    raise error.InternalError('I/O error while writing zipped data to "{0}": '
                              '{1}.\n'.format(zip_filename, e))

  # Open the file using gzip and get the unzipped contents.
  try:
    unzipped_file = gzip.open(zip_filename, 'rb')
    unzipped_data = unzipped_file.read()
    unzipped_file.close()
  except IOError as e:
    raise error.InternalError('I/O error while reading unzipped data from '
                              '"{0}": {1}.\n'.format(zip_filename, e))

  # Remove the temporary zipped file.
  try:
    os.remove(zip_filename)
  except OSError as e:
    raise error.InternalError('OS error while removing zipped data at "{0}": '
                              '{1}.\n'.format(zip_filename, e))

  # Return the unzipped string.
  return unzipped_data


def ZipData(unzipped_data):
  """Zip the specified data using a temporary file and the gzip library.
  After the data is zipped, the temporary file is erased, so no special
  cleanup is necessary.

  Args:
    A byte array with the unzipped data.

  Returns:
    A byte array with the zipped data.

  Raises:
    error.InternalError: If any I/O or OS error occurs while unzipping the data.
  """
  # Compress the data and write it to a temporary file (using a random name to
  # prevent collisions).
  try:
    zip_filename = 'tempZipFile_{0}.gz'.format(random.randrange(0, 2**31 - 1))
    compress_file = gzip.open(zip_filename, 'wb')
    compress_file.write(unzipped_data)
    compress_file.close()
  except IOError as e:
    raise error.InternalError('I/O error while compressing data into "{0}": '
                              '{1}.\n'.format(zip_filename, e))

  # Open the file normally and get the zipped contents.
  try:
    zipped_file = open(zip_filename, 'rb')
    zipped_data = zipped_file.read()
    zipped_file.close()
  except IOError as e:
    raise error.InternalError('I/O error while reading unzipped data from '
                              '"{0}": {1}.\n'.format(zip_filename, e))

  # Remove the temporary zipped file.
  try:
    os.remove(zip_filename)
  except OSError as e:
    raise error.InternalError('OS error happened while removing zipped data at '
                              '"{0}": {1}.\n'.format(zip_filename, e))

  # Return the zipped string.
  return zipped_data


def MakeZipFile(source_files, zip_filename, ignore_exts=None):
  """Create a zip file with the specified source files, which can include
  directories. Specified directories will be traversed and added recursively
  to the output file, ignoring those with the banned extensions.

  Args:
    source_files: A collection with all source files or directories to zip.
    zip_filename: Name of the zip file to generate.
    ignore_exts: A collection with all the extensions to ignore.

  Returns:
    A list with all the ignored files during the zip file creation.

  Raises:
    error.InternalError: If any I/O or OS error occurs while unzipping the data.
  """
  if ignore_exts is None:
    ignore_exts = []

  try:
    # Open the destination zip file and initialize the ignored files set.
    zip_file = zipfile.ZipFile(zip_filename, 'w', zipfile.ZIP_DEFLATED)
    ignored_files = set()

    # Put all specified sources in the zip file, ignoring files with the
    # specified extensions.
    for source_filename in source_files:
      # If the source is a directory, walk over it, adding each file inside it.
      if os.path.isdir(source_filename):
        # Walk over the specified directory.
        for dirpath, dirnames, filenames in os.walk(source_filename):
          # Create the directory inside the zip file and process all
          # files in the current directory.
          zip_file.write(dirpath)
          for filename in filenames:
            # Create the base filename and check if it extension is not in the
            # extenstions ignore list. Otherwise, add it to the ignored files
            # set.
            base_filename = os.path.join(dirpath, filename)
            if os.path.splitext(filename)[1] not in ignore_exts:
              zip_file.write(base_filename)
            else:
              ignored_files.update([base_filename])
      else:
        # Add a file to the zip if and only if it extension is not in the
        # ignore list. Otherwise, add it to the ignored files set.
        if os.path.splitext(source_filename)[1] not in ignore_exts:
          zip_file.write(source_filename)
        else:
          ignored_files.update([source_filename])

    # Close the zip file and return the ignored files set.
    zip_file.close()
    return ignored_files

  except IOError as e:
    raise error.InternalError('I/O error while creating zip file "{0}": '
                              '{1}.\n'.format(zip_filename, e))

  except OSError as e:
    raise error.InternalError('OS error while creating zip file "{0}": '
                              '{1}.\n'.format(zip_filename, e))
