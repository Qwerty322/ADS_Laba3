cmake_minimum_required(VERSION 3.17)
project(ADS_Laba3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libstdc++ -static-libgcc")

set(SOURCE_FILES main.cpp)

add_executable(ADS_Laba3 main.cpp)