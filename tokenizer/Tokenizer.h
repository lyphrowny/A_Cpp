#pragma once

#include<string>
#include<stack>
#include<list>

#include "../tokens/Token.h"

class Tokenizer {
    std::list<Token> _tokens;
    std::string _toTokenize;

public:
    explicit Tokenizer(std::string toTokenize) : _toTokenize(std::move(toTokenize)) {}

    std::list<Token>& tokenize();

    static int _precedence(std::string const& tName);
};



