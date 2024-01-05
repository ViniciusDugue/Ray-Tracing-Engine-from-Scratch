#!/bin/bash

# Run CMake build from parent folder (usually its cmake --build.)
cmake --build build

# Run the executable and redirect output to image.ppm
build/Debug/InOneWeekend.exe > ./image.ppm

# run this in Ray-Tracer-Engine directory with: ./build_and_run.sh