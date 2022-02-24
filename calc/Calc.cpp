#include<dlfcn.h>

#include "Calc.h"

/**
 * alias
 */
using dvec = std::vector<double> const;

/**
 * basic operations
 */
std::list<Operation> Calc::_ops = {
        {0, "(",     nullptr,                                      Arity::UNARY},
        {0, "CONST", nullptr,                                      Arity::UNARY},
        {1, "+",     [](dvec& args) { return args[0] + args[1]; }},
        {1, "-",     [](dvec& args) { return args[0] - args[1]; }},
        {2, "*",     [](dvec& args) { return args[0] * args[1]; }},
        {2, "/",     [](dvec& args) {
            if (args[1] == 0)
                throw std::invalid_argument("Division by zero");
            return args[0] / args[1];
        }},
        {3, "^",     [](dvec& args) {
            if (args[0] < 0 &&
                std::fabs(int(args[1]) - args[1]) >= std::numeric_limits<double>::epsilon())
                throw std::invalid_argument("Base in negative and finite, while exp is not integer");
            else if (std::fabs(int(args[0]) - 0) >= std::numeric_limits<double>::epsilon() && args[1] <= 0)
                throw std::invalid_argument("Base is zero, exp is less or equal to zero");
            return std::pow(args[0], args[1]);
        }},
        {4, "tan",   [](dvec& args) { return std::tan(args[0]); }, Arity::UNARY},
        {6, "~",     [](dvec& args) { return -args[0]; },          Arity::UNARY}
};

/**
 * constructor
 * @param soPath alternative path for .so
 */
Calc::Calc(std::string soPath) {
    if (!soPath.empty())
        _soPath = std::move(soPath);

    using getFunc = Operation (*)();
    char* error;
    void* handle = dlopen(_soPath.c_str(), RTLD_LAZY | RTLD_LOCAL);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(RC::SO_NOT_LOADED);
    }
    // clear any error
    dlerror();

    std::list<std::string> funcsToLoad{"getSin", "getFact"};

    for (auto&& fName: funcsToLoad) {
        auto func = reinterpret_cast<getFunc>(dlsym(handle, fName.c_str()));
        if ((error = dlerror()) != nullptr) {
            fprintf(stderr, "%s\n", error);
            exit(RC::FUNC_NOT_LOADED);
        }
        _ops.push_back(func());
    }

    for (auto&& op: _ops)
        _opsMap[op.getName()] = std::make_shared<Operation>(op);
}

/**
 * calculates the passed string
 * @param toCalc string to calculate
 * @return calculated value
 */
double Calc::calculate(std::string const& toCalc) {
    Tokenizer tokenizer(toCalc, _opsMap);
    return Evaluator::evaluate(std::move(tokenizer.tokenize()));
}
