#pragma once

#include<string>
#include<vector>
#include<functional>


enum Arity {
    UNARY,
    BINARY
};

using Function = std::function<double(std::vector<double> const&)>;

class Operation {
private:
    int _precedence;
    std::string _name;
    Arity _arity;
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

    int getPrecedence() const { return this->_precedence; }

    std::string& getName() { return this->_name; }

    Arity& getArity() { return this->_arity; }

    double calcFunc(const std::vector<double>& args) { return this->_func(args); }
};
