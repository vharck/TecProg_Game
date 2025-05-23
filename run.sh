#!/usr/bin/env bash

# Optional: Clean the build folder if needed
if [ "$1" == "clean" ]; then
    rm -rf build
fi

mkdir -p build
cd build
cmake ..
make
./SimpleGame
cd ..