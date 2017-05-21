cmake_minimum_required(VERSION 3.5)
project(Main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCE_FILES
    main.c terminal.c head/terminal.h asm.c head/asm.h basic.c head/basic.h rpn.c head/rpn.h commands.c head/commands.h)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} rk term bc sc)
