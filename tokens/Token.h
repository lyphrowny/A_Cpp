#pragma once

#include<iostream>
#include<string>
#include <utility>
#include <memory>

#include "../operation/Operation.h"

/**
 * semantic: atomic string element
 * reality: wrapper over `Operation` with `value`
 */
class Token {
    double _value = 0; //< value of the parsed token. Primarily used with `CONST` token
public:
    std::shared_ptr<Operation> op; //< wrapped operation

    /**
     * constructor. Token can be viewed as a wrapper over `Operation` with
     * one additional attribute - `value`, though they are different semantically
     * @param op operation to be wrapped
     */
    explicit Token(std::shared_ptr<Operation> op) : op(std::move(op)) {}

    /**
     * set the value of the token
     * @param value to be set
     */
    void setValue(double value) { _value = value; }

    /**
     * get the value of the token
     * @return the value of the token
     */
    double getValue() const { return _value; }
};
