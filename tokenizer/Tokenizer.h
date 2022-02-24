#pragma once

#include<string>
#include<list>
#include<map>

#include "../tokens/Token.h"

/**
 * splits the input string on tokens, producing reverse polish notation
 */
class Tokenizer {
    std::string CONST{"CONST"}; //< special type of token
    char LPAR = '(', RPAR = ')', DOT = '.'; //< special characters
    std::list<std::unique_ptr<Token>> _tokens; //< split tokens in RPN
    std::map<std::string, std::shared_ptr<Operation>> _availableOps; //< name, operation
    std::string _toTokenize; //< string to split

public:
    /**
     * constructor
     * @param toTokenize string to split
     * @param availableOps names of available operations and the operations themselves
     */
    Tokenizer(std::string toTokenize,
              std::map<std::string,
                      std::shared_ptr<Operation>> availableOps) : _toTokenize(std::move(toTokenize)),
                                                                  _availableOps(std::move(availableOps)) {}

    /**
     * splits the string on tokens in RPN
     * @return list of tokens in RPN
     */
    std::list<std::unique_ptr<Token>> tokenize();
};


