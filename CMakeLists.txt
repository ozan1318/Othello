cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp Game.h Player.h Position.h Board.h Game.cpp Player.cpp Position.cpp Board.cpp)
