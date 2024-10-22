# cmake version
cmake_minimum_required(VERSION 3.10)

# project name
project(midterm-exams)

# set C standard version
set(CMAKE_C_STANDARD 11)

# add library directories
include_directories(include)

# executable program
add_executable(my_ls src/main.c src/ls_utils.c)