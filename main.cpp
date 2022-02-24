#include<iostream>
#include<string>

#include "calc/Calc.h"

/**
 * main func
 * @return success
 */
int main() {

    Calc calc; //< the calculator itself
    std::string input, //< input string storage
            prompt(">>> "); //< prompt (design)

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
