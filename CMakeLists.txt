cmake_minimum_required(VERSION 3.12)
project(Cephalopod)

set(CMAKE_CXX_STANDARD 14)

add_executable(Cephalopod main.cpp board.h Player.h Neighbour.h Coordinate.h)