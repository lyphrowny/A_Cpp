#pragma once

#include<string>
#include<list>
#include<map>

#include "../tokens/Token.h"

class Tokenizer {
    std::string CONST{"CONST"};
    char LPAR = '(', RPAR = ')', DOT = '.';
    std::list<std::unique_ptr<Token>> _tokens;
    std::map<std::string, std::shared_ptr<Operation>> _availableOps;
    std::string _toTokenize;

public:
    Tokenizer(std::string toTokenize,
              std::map<std::string,
                      std::shared_ptr<Operation>> availableOps) : _toTokenize(std::move(toTokenize)),
                                                                  _availableOps(std::move(availableOps)) {}

    std::list<std::unique_ptr<Token>> tokenize();
};


