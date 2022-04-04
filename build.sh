#!/usr/bin/env bash

# create bin directory if it does not already exist
if [ ! -d bin ]
then
    mkdir bin
fi

# compile the code and put the executable in the bin directory
g++ -Wall -g -o bin/hw3 src/*.cpp
