#pragma once
#include <cmath>

class IPunderationFunction {
public:
    virtual ~IPunderationFunction() = default;
    IPunderationFunction() = default;
    virtual int compute(int value) = 0;
};

template<typename T>
class ProductPunderationFunction : public IPunderationFunction {
private:
    T m_factor;
public:
    ProductPunderationFunction(T factor) : m_factor(factor) {}

    int compute(int value) override {
        return value * m_factor;
    }
};

class SumPunderationFunction : public IPunderationFunction {
private:
    int m_factor;
public:
    SumPunderationFunction(int factor) : m_factor(factor) {}

    int compute(int value) override {
        return value + m_factor;
    }
};

class IdentityPunderationFunction : public IPunderationFunction {
public:
    int compute(int value) override {
        return value;
    }
};

class SquarePunderationFunction : public IPunderationFunction {
private:
    double m_factor;
public:
    SquarePunderationFunction(double factor) : m_factor(factor) {}

    int compute(int value) override {
        return (int) pow(value, m_factor);
    }
};

class AbsPunderationFunction : public IPunderationFunction {
public:
    int compute(int value) override {
        return abs(value);
    }
};