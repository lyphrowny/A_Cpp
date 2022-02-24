cmake_minimum_required(VERSION 3.21)
project(Calc)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Calc main.cpp
        tokenizer/Tokenizer.cpp tokenizer/Tokenizer.h
        operation/Operation.cpp operation/Operation.h
        tokens/Token.cpp tokens/Token.h
        evaluator/Evaluator.cpp evaluator/Evaluator.h calc/Calc.cpp calc/Calc.h)

target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
