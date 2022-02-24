#include<iostream>
#include<string>

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
    return 0;
}
