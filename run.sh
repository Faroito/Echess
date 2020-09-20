#!/bin/sh

(rm -rf build &&
    mkdir build &&
    cd build &&
    conan install .. --build=missing &&
    cmake .. -G "Unix Makefiles") &&
(cd build/ && make) &&
./build/bin/Echess