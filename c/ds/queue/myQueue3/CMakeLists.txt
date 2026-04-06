
cmake_minimum_required(VERSION 3.10)
project(myQueue3)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)


include_directories(${CMAKE_CURRENT_LIST_DIR}) 
add_executable(myQueue3 main.c queue3.c)

