#include <iostream>

#include<string>
#include<set>
#include<vector>
#include <list>

#include "operation/Operation.h"
#include "tokenizer/Tokenizer.h"


int main() {
//    operation token = {Precedence::ADD, "+", Arity::BINARY, Notation::INFIX, [](
//            std::vector<double> const& args) {
//        return args[0] + args[1];
//    }};
    std::list<Operation> operations = {
            {Precedence::ADD, "+", Arity::BINARY, Notation::INFIX, [](
                    std::vector<double> const& args) {
                return args[0] + args[1];
            }},
            {Precedence::ADD, "-", Arity::BINARY, Notation::INFIX, [](
                    std::vector<double> const& args) {
                return args[0] - args[1];
            }}
    };
    std::set<std::string> tokenNames = {
            "+", "-", "CONST"
    };
//    for (auto&& token: tokens)
//        tokenNames.insert(token.getName());

    std::string input = "1.7980 + ~.1567869 ^sin(449) -tan ~48!";

    for (auto&& token: tokenNames)
        std::cout << token << std::endl;

    Tokenizer tokenizer(input);
    std::list<Token> toks = tokenizer.tokenize();
    for (auto&& tok : toks)
        std::cout << tok << " ";
    std::cout << std::endl;
//    std::cout << (tokenizer.tokenize()) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
