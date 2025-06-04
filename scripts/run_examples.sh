#!/usr/bin/env bash

cd examples || exit
mkdir build
cmake -B build
cmake --build build
./build/examples