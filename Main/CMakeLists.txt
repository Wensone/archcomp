cmake_minimum_required(VERSION 3.5)
project(Main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCE_FILES
        main.c terminal.c asm.c rpn.c  basic.c)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} rk term bc sc)
