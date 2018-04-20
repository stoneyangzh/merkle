cmake_minimum_required(VERSION 3.9)
project(merkle)

set(CMAKE_CXX_STANDARD 11)

add_executable(MerkleTree
        main.cpp
        Node.cpp
        Node.h
        Tree.cpp
        Tree.h
        picosha2.h)