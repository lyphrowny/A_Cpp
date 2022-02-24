#pragma once

#include "../tokenizer/Tokenizer.h"

class Evaluator {
public:
    static double evaluate(std::list<std::unique_ptr<Token>>&& rpn);
};



