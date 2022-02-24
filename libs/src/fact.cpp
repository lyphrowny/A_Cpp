#include "../include/lib_header.h"

extern "C" Operation getFact() {
    return {5, "!", [](std::vector<double> const& args) {
        if (args[0] < 0)
            throw std::invalid_argument("Negative argument");
        return std::tgamma(args[0] + 1);
    }, Arity::UNARY};
}
