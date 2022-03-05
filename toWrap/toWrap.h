#pragma once

#include <cmath>

class Arithmetic {
public:
    double add(double a, double b) { return a + b; }

    double sub(double a, double b) { return a - b; }
};

class Trigonometry {
public:
    double sin(double x) { return std::sin(x); }

    double cos(double x) { return std::cos(x); }
};
