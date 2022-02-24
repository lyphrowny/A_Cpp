cmake_minimum_required(VERSION 3.18.4)

project (addon)

add_library(${PROJECT_NAME} SHARED src/fact.cpp src/sin.cpp include/lib_header.h)

target_include_directories(${PROJECT_NAME} PRIVATE include)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/lib_header.h)
