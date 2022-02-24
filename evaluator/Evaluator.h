#pragma once

#include "../tokenizer/Tokenizer.h"

/**
 * evaluates the tokens in RPN
 */
class Evaluator {
public:
    /**
     * evaluates the list of tokens in RPN
     * @param rpn list of tokens in RPN
     * @return result
     */
    static double evaluate(std::list<std::unique_ptr<Token>>&& rpn);
};



