#!/bin/bash

cd TIMGE/

mkdir build/

cmake -S . -B build/linux_x64-Debug/
cmake --build build/linux_x64-Debug/ -j4

cp build/linux_x64-Debug/libTIMGE.a ../Sandbox/lib/
cp -r build/linux_x64-Debug/include/TIMGE/ ../Sandbox/include/

cd ../Sandbox/

mkdir build/

cmake -S . -B build/linux_x64-Debug/
cmake --build build/linux_x64-Debug/ -j4

build/linux_x64-Debug/TIMGESandbox
