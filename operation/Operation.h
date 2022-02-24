#pragma once

#include<string>
#include <utility>
#include<vector>
#include<functional>

//enum Precedence {
//    PAREN,
//    ADD = 1,
//    SUB = 1,
//    MUL = 2,
//    DIV = 2,
//    POWER = 3,
//    FACT = 4,
//    INV = 5
//};

enum Arity {
    UNARY,
    BINARY
};

enum Notation {
    PREFIX,
    INFIX,
    POSTFIX
};

using Function = std::function<double(std::vector<double> const&)>;

class Operation {
private:
    int _precedence;
    std::string _name;
    Arity _arity;
    Notation _notation;
    Function _func;

public:
    Operation(const int precedence,
              std::string name,
              Function func = nullptr,
              Arity const& arity = BINARY) :
                                            _precedence(precedence),
                                            _name(std::move(name)),
                                            _arity(arity),
                                            _func(std::move(func)) {}

    int getPrecedence() { return this->_precedence; }

    std::string& getName() { return this->_name; }

    Arity& getArity() { return this->_arity; }

    double calcFunc(std::vector<double> args) { return this->_func(args); }
};



