cmake_minimum_required(VERSION 3.5)
project(lab3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c)

set(lib graph.c graph.h)

add_library(bc ${lib})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(../cmake-build-debug/lab2)
target_link_libraries(${PROJECT_NAME} bc term)
