#pragma once

#include<string>
#include<stack>
#include<list>
#include<map>
#include <utility>

#include "../tokens/Token.h"

class Tokenizer {
    std::list<std::unique_ptr<Token>> _tokens;
    std::map<std::string, std::shared_ptr<Operation>> _availableOps;
    std::string _toTokenize;

public:
    Tokenizer(std::string toTokenize,
              std::map<std::string, std::shared_ptr<Operation>> availableOps) : _toTokenize(std::move(toTokenize)),
                                                              _availableOps(
                                                                      std::move(availableOps)) {}

//    explicit Tokenizer(std::string toTokenize) : _toTokenize(std::move(toTokenize)) {}

    std::list<std::unique_ptr<Token>> tokenize();

//    static int _precedence(std::string const& tName);
};



