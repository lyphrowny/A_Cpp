cmake_minimum_required(VERSION 3.21)
project(Engine)

set(CMAKE_CXX_STANDARD 14)

add_executable(Engine
        main.cpp
        toWrap/toWrap.h
        wrapper/Wrapper.h
        engine/Engine.h
        )
