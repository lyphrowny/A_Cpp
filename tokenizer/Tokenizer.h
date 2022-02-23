#pragma once

#include<string>
#include<stack>

#include "../tokens/Token.h"

class Tokenizer {
    std::stack<Token> _tokens;
    std::string _toTokenize;

public:
    explicit Tokenizer(std::string toTokenize) : _toTokenize(std::move(toTokenize)) {}

    std::stack<Token>& tokenize();
};



