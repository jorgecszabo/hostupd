cmake_minimum_required(VERSION 3.23)
project(hostupd)

set(CMAKE_CXX_STANDARD 14)

add_executable(hostupd src/main.cpp src/ping.cpp src/ping.h)
