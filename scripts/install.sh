#!/usr/bin/env bash

# read the directory with CMakeLists.txt from the commandline,
# or if not specified, use the current directory
CMAKELISTSDIR="$1"
if [[ ! -n "$CMAKELISTSDIR" ]]; then
  CMAKELISTSDIR="$PWD"
endif

if [[ ! -f "$CMAKELISTSPATH" ]]; then
  echo "Error! CMakeFiles.txt not found"
  echo "Make sure to be in the same directory as a CMakeLists.txt"
  echo "or specify path to a directory with"
  echo "a CMakeLists.txt file on the command line"
endif

# install the library
mkdir -p "${CMAKELISTSDIR}/build"
cmake -C "${CMAKELISTSDIR}" -B "${CMAKELISTSDIR}/build"
cmake --build "${CMAKELISTSDIR}/build"
cmake --install "${CMAKELISTSDIR}/build"
