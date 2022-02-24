#pragma once

#include<string>
#include<vector>
#include<functional>

/**
 * arity of operations
 */
enum Arity {
    UNARY, //< 1 argument
    BINARY //< 2 arguments
};

/**
 * alias
 */
using Function = std::function<double(std::vector<double> const&)>;

/**
 * represents calc operation (the function itself) and some of its characteristics
 */
class Operation {
private:
    int _precedence; //< precedence to differentiate the order of the operations
    std::string _name; //< convenient name of the operation
    Arity _arity; //< number of operands the function needs
    Function _func; //< the function itself

public:
    /**
     * constructor
     * @param precedence number, defines the order of the operation
     * @param name convenient name of the operation
     * @param func the function itself
     * @param arity number of arguments the function needs
     */
    Operation(const int precedence,
              std::string name,
              Function func = nullptr,
              Arity const& arity = BINARY) :
            _precedence(precedence),
            _name(std::move(name)),
            _arity(arity),
            _func(std::move(func)) {}

    /**
     * get the precedence
     * @return precedence
     */
    int getPrecedence() const { return this->_precedence; }

    /**
     * get the name
     * @return name
     */
    std::string& getName() { return this->_name; }

    /**
     * git the arity
     * @return arity
     */
    Arity& getArity() { return this->_arity; }

    /**
     * calls the operation
     * @param args arguments, the operation to be called with
     * @return result of the operation
     */
    double calcFunc(const std::vector<double>& args) { return this->_func(args); }
};
