cmake_minimum_required(VERSION 3.21)
project(Calc)

set(CMAKE_CXX_STANDARD 14)

add_executable(Calc main.cpp
        tokenizer/Tokenizer.cpp tokenizer/Tokenizer.h
        operation/Operation.cpp operation/Operation.h
        tokens/Token.cpp tokens/Token.h
        evaluator/Evaluator.cpp evaluator/Evaluator.h)
