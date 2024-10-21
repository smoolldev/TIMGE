#!/bin/bash

cd TIMGE/

mkdir build/

cmake -S . -B build/linux_x64-Debug/
cmake --build build/linux_x64-Debug/ -j4

rm ../Sandbox/lib/libTIMGE.a
rm -rf ../Sandbox/include/TIMGE

rm ../Sandbox/lib/libstb_image.a
cp build/linux_x64-Debug/vendor/stb_image/libstb_image.a ../Sandbox/lib/

cp build/linux_x64-Debug/libTIMGE.a ../Sandbox/lib/
cp -r ./include/TIMGE/ ../Sandbox/include/
cp build/linux_x64-Debug/compile_commands.json ./

cd ../Sandbox/

mkdir build/

cmake -S . -B build/linux_x64-Debug/
cmake --build build/linux_x64-Debug/ -j4

cp build/linux_x64-Debug/compile_commands.json ./

build/linux_x64-Debug/TIMGESandbox
