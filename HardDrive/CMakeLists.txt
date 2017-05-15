cmake_minimum_required(VERSION 3.5)
project(HardDrive)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")

set(SOURCE_FILES
        main.c hd_tr_interface.c hd_tr_interface.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
