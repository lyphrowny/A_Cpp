#pragma once

#include<string>
#include <cmath>

#include "../tokenizer/Tokenizer.h"
#include "../evaluator/Evaluator.h"

/**
 * return codes
 */
enum RC {
    SO_NOT_LOADED, //< the shared lib wasn't loaded
    FUNC_NOT_LOADED, //< the function wasn't found in the lib
};

/**
 * combines all other classes, providing more convenient API
 */
class Calc {
    std::string _soPath = "../libs/build/libaddon.so"; //< path to the .so to load
    static std::list<Operation> _ops; //< list of the basic operations
    std::map<std::string, std::shared_ptr<Operation>> _opsMap; //< op_name, operation

public:
    /**
     * constructor
     * @param soPath alternative path for .so
     */
    explicit Calc(std::string soPath = "");

    /**
     * calculates the passed string
     * @param toCalc string to calculate
     * @return calculated value
     */
    double calculate(std::string const& toCalc);
};



