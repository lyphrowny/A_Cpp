#pragma once

#include <cmath>

/**
 * provides basic arithmetic functions
 */
class Arithmetic {
public:
    /**
     * sum of two doubles
     * @param a addend
     * @param b addend
     * @return result of the addition
     */
    double add(double a, double b) { return a + b; }

    /**
     * subtracts one double from another
     * @param a minuend
     * @param b subtrahend
     * @return difference
     */
    double sub(double a, double b) { return a - b; }
};

/**
 * provides basic trigonometric functions
 */
class Trigonometry {
public:
    /**
     * sin
     * @param x argument of sin
     * @return sin of the argument
     */
    double sin(double x) { return std::sin(x); }

    /**
     * cos
     * @param x argument of cos
     * @return cos of the argument
     */
    double cos(double x) { return std::cos(x); }
};
