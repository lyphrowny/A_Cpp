#pragma once

#include "../tokenizer/Tokenizer.h"

class Evaluator {
public:
    double evaluate(std::list<Token>& rpn);
};



