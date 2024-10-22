#!/bin/bash

cd TIMGE/

mkdir build/

cmake -S . -B build/linux_x64-Debug/ -D GLFW_BUILD_WAYLAND=OFF
cmake --build build/linux_x64-Debug/ -j4

cd ../Sandbox

rm lib/libTIMGE.a
rm lib/libstb_image.a
rm -rf include/TIMGE

cp ../TIMGE/build/linux_x64-Debug/vendor/stb_image/libstb_image.a lib/

cp ../TIMGE/build/linux_x64-Debug/libTIMGE.a ../Sandbox/lib/
cp -r ../TIMGE/include/TIMGE/ include/
cp ../TIMGE/build/linux_x64-Debug/compile_commands.json ./

mkdir build/

cmake -S . -B build/linux_x64-Debug/
cmake --build build/linux_x64-Debug/ -j4

cp build/linux_x64-Debug/compile_commands.json ./

build/linux_x64-Debug/TIMGESandbox
