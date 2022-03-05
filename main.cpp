#include <iostream>

#include "wrapper/Wrapper.h"
#include "engine/Engine.h"
#include "toWrap/toWrap.h"


int main() {
    Arithmetic ar;
    Trigonometry tr;
    Wrapper add(&ar, &Arithmetic::add, {
            {"b", 0},
            {"a", 1}
    }),
            sub(&ar, &Arithmetic::sub, {
            {"a", 0},
            {"b", 0}
    }),
            sin(&tr, &Trigonometry::sin, {{"x", .5}}),
            cos(&tr, &Trigonometry::cos, {{"x", 1.414}});

    Engine engine;
    engine.register_command(&add, "add");
    engine.register_command(&sub, "sub");
    engine.register_command(&sin, "sin");
    engine.register_command(&cos, "cos");

    std::cout << "add(2, 3) = " << engine.execute("add", {
            {"a", 3},
            {"c", 9},
            {"b", 2},
    }) << std::endl;
    std::cout << "sin(.5) = " << engine.execute("sin", {{"x", .5}}) << std::endl;
    std::cout << "sub(5, 3) = " << engine.execute("sub", {
            {"a", 5},
            {"b", 3},
    }) << std::endl;
    std::cout << "sub(3, 5) = " << engine.execute("sub", {
            {"b", 5},
            {"a", 3},
    }) << std::endl;
    return 0;
}
