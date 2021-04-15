cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(enumpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-DBOOST_PP_VARIADICS=1)

add_executable(enum_pp_demo enum_pp_demo.cpp)

