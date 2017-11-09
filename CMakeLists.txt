cmake_minimum_required(VERSION 3.8)
project(Train_Lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        caltrain-runner.c
        caltrain.c
        caltrain.h)

add_executable(Train_Lab3 ${SOURCE_FILES})