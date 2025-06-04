#!/usr/bin/env bash

# install eigen
wget https://gitlab.com/libeigen/eigen/-/archive/3.3.9/eigen-3.3.9.tar.gz
gzip -d eigen-3.3.9.tar.gz
tar x -f eigen-3.3.9.tar
cd eigen-3.3.9 || exit
mkdir build
cd build || exit
cmake ..
sudo make install

# install library
cd ../..
mkdir build
cmake -B build
cmake --build build
cmake --install build
