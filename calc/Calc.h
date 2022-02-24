#pragma once

#include<string>
#include <cmath>

#include "../tokenizer/Tokenizer.h"
#include "../evaluator/Evaluator.h"

enum RC {
    SO_NOT_LOADED,
    FUNC_NOT_LOADED,
};

class Calc {
    std::string _soPath = "../libs/build/libaddon.so";
    static std::list<Operation> _ops;
    std::map<std::string, std::shared_ptr<Operation>> _opsMap;

public:
    explicit Calc(std::string soPath = "");
    double calculate(std::string const& toCalc);
};



