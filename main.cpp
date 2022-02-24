#include <iostream>

#include<string>
#include<vector>
#include<list>
#include<cmath>
#include<limits>

#include<filesystem>
//#include<windows>
//#include<iostream>

//#include "lib_header.h"
#include <dlfcn.h>

#include "operation/Operation.h"


//#include "libs/include/lib_header.h"
#include "tokens/Token.h"
#include "tokenizer/Tokenizer.h"
#include "evaluator/Evaluator.h"


int main() {

    void* handle;
    Operation (* sin)(void);
    Operation (* fact)(void);
    char* error;

    std::filesystem::path cwd = std::filesystem::current_path();
    std::cout << cwd.string() << std::endl;

    handle = dlopen("../libs/build/libaddon.so", RTLD_LAZY | RTLD_LOCAL);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    sin = (Operation (*)(void)) dlsym(handle, "getSin");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    fact = (Operation (*)(void)) dlsym(handle, "getFact");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }


    std::list<Operation> operations = {
            {0, "(",     nullptr,                                                           Arity::UNARY},
            {0, "CONST", nullptr,                                                           Arity::UNARY},
            {1, "+",     [](std::vector<double> const& args) { return args[0] + args[1]; }},
            {1, "-",     [](std::vector<double> const& args) { return args[0] - args[1]; }},
            {2, "*",     [](std::vector<double> const& args) { return args[0] * args[1]; }},
            {2, "/",     [](std::vector<double> const& args) {
                if (args[1] == 0)
                    throw std::invalid_argument("Division by zero");
                return args[0] / args[1];
            }},
            {3, "^",     [](std::vector<double> const& args) {
                if (args[0] < 0 &&
                    std::fabs(int(args[1]) - args[1]) >= std::numeric_limits<double>::epsilon())
                    throw std::invalid_argument("Base in negative and finite, while exp is not integer");
                else if (std::fabs(int(args[0]) - 0) >= std::numeric_limits<double>::epsilon() && args[1] <= 0)
                    throw std::invalid_argument("Base is zero, exp is less or equal to zero");
                return std::pow(args[0], args[1]);
            }},
//            {4, "sin",   [](std::vector<double> const& args) { return std::sin(args[0]); }, Arity::UNARY},
            {4, "tan",   [](std::vector<double> const& args) { return std::tan(args[0]); }, Arity::UNARY},
//            {5, "!",     [](std::vector<double> const& args) {
//                if (args[0] < 0)
//                    throw std::invalid_argument("Negative argument");
//                return std::tgamma(args[0] + 1);
//            },                                                                              Arity::UNARY},
            {6, "~",     [](std::vector<double> const& args) { return -args[0]; },          Arity::UNARY}
    };

    Operation op1 = (*fact)(), op2 = (*sin)();
    auto sh1 = std::make_shared<Operation>(op1);
    auto sh2 = std::make_shared<Operation>(op2);
    operations.push_back(op1);
    operations.push_back(op2);

//    dlclose(handle);

//    std::cout << op1.getName() << op2.getName() << std::endl;

//    std::cout << (*fact)().getName() << (*sin)().getName() << std::endl;

//    std::map<std::string, Operation*> tMap;
//    for (auto&& op: operations)
//        tMap[op.getName()] = &op;

    std::map<std::string, std::shared_ptr<Operation>> tokenMap;
    for (auto&& op: operations)
        tokenMap[op.getName()] = std::make_shared<Operation>(op);

//    tokenMap[(*fact)()->getName()] = std::make_shared<Operation>(*(*fact)());
//    tokenMap[(*sin)()->getName()] = std::make_shared<Operation>(*(*sin)());

    std::string input = "3 + ~3 + sin(3.141592/6) - 4!";

    Tokenizer tokenizer(input, tokenMap);
    std::list<std::unique_ptr<Token>> toks = tokenizer.tokenize();
    for (auto&& tok: toks)
        std::cout << tok->op->getName() << "(" << tok->getValue() << ") ";
    std::cout << std::endl;

    std::cout << "Answer: " << Evaluator::evaluate(toks) << std::endl;
    std::cout << "Hello, World!" << std::endl;

//    toks.clear();
//    tokenMap.clear();
//    operations.clear();

//    dlclose(handle);

    return 0;
}
