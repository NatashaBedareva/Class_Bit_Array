cmake_minimum_required(VERSION 3.11)
project(Bit_Array VERSION 0.2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_subdirectory(test)

add_executable(Bit_Array main.cpp)

#cmake -S. -Bbuild -DBUILD_MOCK=OFF --fresh
#cmake --build build
#./build/Debug/kvadraturawn.exe