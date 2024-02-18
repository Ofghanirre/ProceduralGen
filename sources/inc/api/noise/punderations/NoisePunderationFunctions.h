#pragma once
#include <cmath>
#include <memory>

class IPunderationFunction {
public:
    virtual ~IPunderationFunction() = default;
    IPunderationFunction(std::shared_ptr<IPunderationFunction> next) : m_next(next), m_hasNext(true) {}
    IPunderationFunction() : m_next(nullptr), m_hasNext(false) {}
    virtual int compute(int value) = 0;

    bool hasNext() const {
        return m_hasNext;
    }

    void setNext(std::shared_ptr<IPunderationFunction> next) {
        m_next = next;
        m_hasNext = true;
    }

protected:
    std::shared_ptr<IPunderationFunction> m_next;
    bool m_hasNext;
};

class FilterPunderationFunction: public IPunderationFunction {
public:
    FilterPunderationFunction(bool (*predicate)(int), std::shared_ptr<IPunderationFunction> next) : m_predicate(predicate), IPunderationFunction(next) {}
    FilterPunderationFunction(bool (*predicate)(int)) : m_predicate(predicate), IPunderationFunction() {}

    int compute(int value) override {
        if (m_predicate(value) & m_hasNext) {
            return m_next->compute(value);
        }
        return value;
    }
private:
    bool (*m_predicate)(int);
};

template<typename T>
class ProductPunderationFunction : public IPunderationFunction {
private:
    T m_factor;
public:
    ProductPunderationFunction(T factor, std::shared_ptr<IPunderationFunction> next) : m_factor(factor), IPunderationFunction(next) {}
    ProductPunderationFunction(T factor) : m_factor(factor), IPunderationFunction() {}

    int compute(int value) override {
        if (m_hasNext) {
            return m_next->compute(value * m_factor);
        }
        return value * m_factor;
    }
};

class SumPunderationFunction : public IPunderationFunction {
private:
    int m_factor;
public:
    SumPunderationFunction(int factor, std::shared_ptr<IPunderationFunction> next) : m_factor(factor), IPunderationFunction(next) {}
    SumPunderationFunction(int factor) : m_factor(factor), IPunderationFunction() {}

    int compute(int value) override {
        if (m_hasNext) {
            return m_next->compute(value + m_factor);
        }
        return value + m_factor;
    }
};

class IdentityPunderationFunction : public IPunderationFunction {
public:
    IdentityPunderationFunction(std::shared_ptr<IPunderationFunction> next) : IPunderationFunction(next) {}
    IdentityPunderationFunction() : IPunderationFunction() {}

    int compute(int value) override {
        if (m_hasNext) {
            return m_next->compute(value);
        }
        return value;
    }
};

class PowerPunderationFunction : public IPunderationFunction {
private:
    double m_factor;
public:
    PowerPunderationFunction(double factor, std::shared_ptr<IPunderationFunction> next) : m_factor(factor), IPunderationFunction(next) {}
    PowerPunderationFunction(double factor) : m_factor(factor), IPunderationFunction() {}

    int compute(int value) override {
        if (m_hasNext) {
            return m_next->compute((int) pow(value, m_factor));
        }
        return (int) pow(value, m_factor);
    }
};

class AbsPunderationFunction : public IPunderationFunction {
public:
    AbsPunderationFunction(std::shared_ptr<IPunderationFunction> next) : IPunderationFunction(next) {}
    AbsPunderationFunction() : IPunderationFunction() {}

    int compute(int value) override {
        if (m_hasNext) {
            return m_next->compute(abs(value));
        }
        return abs(value);
    }
};