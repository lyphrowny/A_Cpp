#include "../include/lib_header.h"

extern "C" Operation getSin() {
    return {4, "sin", [](std::vector<double> const& args) {
        return std::sin(args[0]); }, Arity::UNARY};
}
