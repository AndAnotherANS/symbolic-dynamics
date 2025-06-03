#!/usr/bin/env bash

# install eigen
wget https://gitlab.com/libeigen/eigen/-/archive/3.3.9/eigen-3.3.9.tar.gz
gzip -d eigen-3.3.9.tar.gz
tar x -f eigen-3.3.9.tar
cd eigen-3.3.9
mkdir build
cd build
cmake ..
sudo make install

# install library
cd ../..
mkdir build
cd build
cmake ..
make