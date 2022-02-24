#pragma once

#include<iostream>
#include<string>
#include <utility>
#include <memory>

#include "../operation/Operation.h"


class Token {
    double _value = 0;
public:
    std::shared_ptr<Operation> op;

    explicit Token(std::shared_ptr<Operation> op) : op(std::move(op)) {}

    void setValue(double value) { _value = value; }

    double getValue() const { return _value; }
};

//class Token {
//    std::string _name;
//    double _value;
//
//public:
//    explicit Token(std::string name, double value = 0) : _name(std::move(name)), _value(value) {}
//
//    std::string getName() const { return this->_name; }
//
//    double getValue() const { return this->_value; }
//
//    friend std::ostream& operator<<(std::ostream& os, Token const& token) {
//        return os << token.getName() << "(" << token.getValue() << ")";
//    }
//
//    Token() : _value(0) {}
//
//    void setName(std::string name) { _name = std::move(name); }
//
//    void setValue(double value) { _value = value; }
//};
//
//
//
