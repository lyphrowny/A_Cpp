#include<iostream>
#include<string>
#include<dlfcn.h>

#include "calc/Calc.h"


int main() {

    Calc calc;
    std::string input, prompt(">>> ");

    std::cout << prompt;
    while (std::getline(std::cin, input) && input != "q") {
        try {
            std::cout << calc.calculate(input) << std::endl << prompt;
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl << prompt;
        }
    }

    void* handle;
    Operation (* sin)(void);
    Operation (* fact)(void);
    char* error;

//    std::filesystem::path cwd = std::filesystem::current_path();
//    std::cout << cwd.string() << std::endl;

//    handle = dlopen("../libs/build/libaddon.so", RTLD_LAZY | RTLD_LOCAL);
//    if (!handle) {
//        fprintf(stderr, "%s\n", dlerror());
//        exit(1);
//    }
//    dlerror();
//
//    sin = (Operation (*)(void)) dlsym(handle, "getSin");
//    if ((error = dlerror()) != nullptr) {
//        fprintf(stderr, "%s\n", error);
//        exit(1);
//    }
//
//    fact = (Operation (*)(void)) dlsym(handle, "getFact");
//    if ((error = dlerror()) != nullptr) {
//        fprintf(stderr, "%s\n", error);
//        exit(1);
//    }
//
//
//    std::list<Operation> operations = {
//            {0, "(",     nullptr,                                                           Arity::UNARY},
//            {0, "CONST", nullptr,                                                           Arity::UNARY},
//            {1, "+",     [](std::vector<double> const& args) { return args[0] + args[1]; }},
//            {1, "-",     [](std::vector<double> const& args) { return args[0] - args[1]; }},
//            {2, "*",     [](std::vector<double> const& args) { return args[0] * args[1]; }},
//            {2, "/",     [](std::vector<double> const& args) {
//                if (args[1] == 0)
//                    throw std::invalid_argument("Division by zero");
//                return args[0] / args[1];
//            }},
//            {3, "^",     [](std::vector<double> const& args) {
//                if (args[0] < 0 &&
//                    std::fabs(int(args[1]) - args[1]) >= std::numeric_limits<double>::epsilon())
//                    throw std::invalid_argument("Base in negative and finite, while exp is not integer");
//                else if (std::fabs(int(args[0]) - 0) >= std::numeric_limits<double>::epsilon() && args[1] <= 0)
//                    throw std::invalid_argument("Base is zero, exp is less or equal to zero");
//                return std::pow(args[0], args[1]);
//            }},
//            {4, "tan",   [](std::vector<double> const& args) { return std::tan(args[0]); }, Arity::UNARY},
//            {6, "~",     [](std::vector<double> const& args) { return -args[0]; },          Arity::UNARY}
//    };
//
//    Operation op1 = (*fact)(), op2 = (*sin)();
//    auto sh1 = std::make_shared<Operation>(op1);
//    auto sh2 = std::make_shared<Operation>(op2);
//    operations.push_back(op1);
//    operations.push_back(op2);
//
//    std::map<std::string, std::shared_ptr<Operation>> tokenMap;
//    for (auto&& op: operations)
//        tokenMap[op.getName()] = std::make_shared<Operation>(op);
//
//
//    std::string _input = "3 + ~3 + sin(3.141592/6) - 4!";
//
//    Tokenizer tokenizer(_input, tokenMap);
//    std::list<std::unique_ptr<Token>> toks = tokenizer.tokenize();
//    for (auto&& tok: toks)
//        std::cout << tok->op->getName() << "(" << tok->getValue() << ") ";
//    std::cout << std::endl;
//
//    std::cout << "Answer: " << Evaluator::evaluate(std::move(toks)) << std::endl;
//    std::cout << "Hello, World!" << std::endl;
//
//    // no unloading for two reasons:
//    // 1. the loaded funcs exist till the end of the program
//    // 2. running the unloading func causes SEGFAULT
//    //    dlclose(handle);

    return 0;
}
