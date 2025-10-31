cmake_minimum_required(VERSION 3.10)
project(AVLTreeProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(avltree
    src/main.cpp
    src/AVLTree.cpp
)