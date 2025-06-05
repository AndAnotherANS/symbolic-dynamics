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

mkdir -p "${CMAKELISTSDIR}/build"
cmake -C "${CMAKELISTSDIR}" -B "${CMAKELISTSDIR}/build" -DBUILD_EXAMPLES
cmake --build "${CMAKELISTSDIR}/build"
"${CMAKELISTSDIR}/build/examples"
