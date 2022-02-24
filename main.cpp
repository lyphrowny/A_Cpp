#include <iostream>

#include<string>
#include<set>
#include<vector>
#include <list>
#include<cmath>


#include "operation/Operation.h"
#include "tokens/Token.h"
#include "tokenizer/Tokenizer.h"
#include "evaluator/Evaluator.h"


int main() {
//    operation token = {Precedence::ADD, "+", Arity::BINARY, Notation::INFIX, [](
//            std::vector<double> const& args) {
//        return args[0] + args[1];
//    }};
    std::list<Operation> operations = {
            {0, "(",     nullptr,                                                                  Arity::UNARY},
            {0, "CONST", [](std::vector<double> const& args) { return args[0]; },                  Arity::UNARY},
            {1, "+",     [](std::vector<double> const& args) { return args[0] + args[1]; }},
            {1, "-",     [](std::vector<double> const& args) { return args[0] - args[1]; }},
            {2, "*",     [](std::vector<double> const& args) { return args[0] * args[1]; }},
            {2, "/",     [](std::vector<double> const& args) { return args[0] / args[1]; }},
            {3, "^",     [](std::vector<double> const& args) { return std::pow(args[0], args[1]); }},
            {4, "sin",   [](std::vector<double> const& args) { return std::sin(args[0]); },        Arity::UNARY},
            {4, "tan",   [](std::vector<double> const& args) { return std::tan(args[0]); },        Arity::UNARY},
            {5, "!",     [](std::vector<double> const& args) { return std::tgamma(args[0] + 1); }, Arity::UNARY},
            {6, "~",     [](std::vector<double> const& args) { return -args[0]; },                 Arity::UNARY}
    };
    std::map<std::string, std::shared_ptr<Operation>> tokenMap;
    for (auto && op: operations)
        tokenMap[op.getName()] = std::make_shared<Operation>(op);


//    std::set<std::string> tokenNames = {
//            "+", "-", "CONST"
//    };
//    for (auto&& token: tokens)
//        tokenNames.insert(token.getName());

    std::string input = "3 + 3";

//    for (auto&& token: tokenNames)
//        std::cout << token << std::endl;

    Tokenizer tokenizer(input, tokenMap);
    std::list<std::unique_ptr<Token>> toks = tokenizer.tokenize();
    for (auto&& tok: toks)
        std::cout << tok->op->getName() << "(" << tok->getValue() << ") ";
    std::cout << std::endl;

//    Evaluator evaluator;
    std::cout << "Answer: " << Evaluator::evaluate(toks) << std::endl;

//    std::cout << (tokenizer.tokenize()) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
