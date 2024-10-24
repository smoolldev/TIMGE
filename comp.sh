#!/bin/bash

cd TIMGE/

#rm -rf build/
mkdir build/

cmake -S . -B build/linux_x64-Debug/ -DCMAKE_C_COMPILER=/usr/local/bin/gcc -DCMAKE_CXX_COMPILER=/usr/local/bin/g++ -D GLFW_BUILD_WAYLAND=OFF
cmake --build build/linux_x64-Debug/ -j4

cp build/linux_x64-Debug/compile_commands.json ./

cd ../Sandbox

rm lib/libTIMGE.a
rm lib/libstb_image.a
rm -rf include/TIMGE

cp ../TIMGE/build/linux_x64-Debug/libTIMGE.a lib/
cp ../TIMGE/build/linux_x64-Debug/vendor/stb_image/libstb_image.a lib/

cp -r ../TIMGE/include/TIMGE/ include/

#rm -rf build/
mkdir build/

cmake -S . -B build/linux_x64-Debug/ -DCMAKE_C_COMPILER=/usr/local/bin/gcc -DCMAKE_CXX_COMPILER=/usr/local/bin/g++
cmake --build build/linux_x64-Debug/ -j4

cp build/linux_x64-Debug/compile_commands.json ./

build/linux_x64-Debug/TIMGESandbox
