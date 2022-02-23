#pragma once

#include<string>
#include <utility>
#include<vector>
#include<functional>

enum Precedence {
    PAREN,
    FACT,
    POWER,
    MUL,
    ADD
};

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

class Token {
private:
    Precedence _precedence;
    std::string _name;
    Arity _arity;
    Notation _notation;
    Function _func;

public:
    Token(Precedence const& precedence = ADD, std::string name = "", Arity const& arity = BINARY,
          Notation const& notation = INFIX, Function func = nullptr) : _precedence(precedence),
                                                                       _name(std::move(name)),
                                                                       _arity(arity),
                                                                       _notation(notation),
                                                                       _func(std::move(func)) {}

    std::string& getName() { return this->_name; }
};



