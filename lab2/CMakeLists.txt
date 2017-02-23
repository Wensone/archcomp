cmake_minimum_required(VERSION 3.5)
project(lab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c)

set(lib term.c term.h)

add_library(term ${lib})

add_executable(lab2 ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} term)
