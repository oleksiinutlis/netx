cmake_minimum_required(VERSION 4.0)
project(netx)

set(CMAKE_CXX_STANDARD 23)

add_executable(netx main.cpp
        netx/Socket.h
        Socket.cpp)
