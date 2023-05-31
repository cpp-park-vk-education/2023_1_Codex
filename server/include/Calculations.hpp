#pragma once
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "Exceptions.hpp"
#include "ITask.hpp"
#include "TaskInfo.hpp"

const double pi = 2 * asin(1.0);

class ICalculatable {
   public:
    virtual double Calculate() const = 0;
};

class Number : public ICalculatable {
   public:
    Number(double value_) : value(value_) {}

    double Calculate() const override {
        return value;
    }

   private:
    double value;
};

//Бинарные
class Add : public ICalculatable {
   public:
    Add(std::unique_ptr<ICalculatable> left_, std::unique_ptr<ICalculatable> right_)
        : left(std::move(left_)), right(std::move(right_)) {}
    double Calculate() const override {
        return left->Calculate() + right->Calculate();
    }

   private:
    std::unique_ptr<ICalculatable> left;
    std::unique_ptr<ICalculatable> right;
};

class Subtraction : public ICalculatable {
   public:
    Subtraction(std::unique_ptr<ICalculatable> left_, std::unique_ptr<ICalculatable> right_)
        : left(std::move(left_)), right(std::move(right_)) {}
    double Calculate() const override {
        return left->Calculate() - right->Calculate();
    }

   private:
    std::unique_ptr<ICalculatable> left;
    std::unique_ptr<ICalculatable> right;
};

class Division : public ICalculatable {
   public:
    Division(std::unique_ptr<ICalculatable> left_, std::unique_ptr<ICalculatable> right_)
        : left(std::move(left_)), right(std::move(right_)) {}
    double Calculate() const override {
        double denominator = right->Calculate();
        if (denominator == 0) throw Tasks::TaskInvalidData("Division by zero");
        return left->Calculate() / denominator;
    }

   private:
    std::unique_ptr<ICalculatable> left;
    std::unique_ptr<ICalculatable> right;
};

class Multiplication : public ICalculatable {
   public:
    Multiplication(std::unique_ptr<ICalculatable> left_, std::unique_ptr<ICalculatable> right_)
        : left(std::move(left_)), right(std::move(right_)) {}
    double Calculate() const override {
        return left->Calculate() * right->Calculate();
    }

   private:
    std::unique_ptr<ICalculatable> left;
    std::unique_ptr<ICalculatable> right;
};

class Degree : public ICalculatable {
   public:
    Degree(std::unique_ptr<ICalculatable> left_, std::unique_ptr<ICalculatable> right_)
        : left(std::move(left_)), right(std::move(right_)) {}
    double Calculate() const override {
        try {
            double result = pow(left->Calculate(), right->Calculate());
            if (std::isnan(result)) {
                throw Tasks::TaskInvalidData("Even root of negative number is not defined ");
            }
            return result;
        } catch (const std::exception& ex) {
            throw Tasks::TaskInvalidData("Even root of negative number is not defined ");
        }
    }

   private:
    std::unique_ptr<ICalculatable> left;
    std::unique_ptr<ICalculatable> right;
};

//Унарные

//Триганометрия

class Sinus : public ICalculatable {
   public:
    Sinus(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        return sin(left->Calculate());
    }

   private:
    std::unique_ptr<ICalculatable> left;
};
class Arcsinus : public ICalculatable {
   public:
    Arcsinus(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        return asin(left->Calculate());
    }

   private:
    std::unique_ptr<ICalculatable> left;
};

class Cosine : public ICalculatable {
   public:
    Cosine(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        return cos(left->Calculate());
    }

   private:
    std::unique_ptr<ICalculatable> left;
};

class Arcosine : public ICalculatable {
   public:
    Arcosine(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        return acos(left->Calculate());
    }

   private:
    std::unique_ptr<ICalculatable> left;
};

class Tangent : public ICalculatable {
   public:
    Tangent(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        double num = left->Calculate();
        if (num == pi / 2) throw Tasks::TaskInvalidData(" Tangent of pi/2 is infinity ");
        return tan(num);
    }

   private:
    std::unique_ptr<ICalculatable> left;
};

class Arctangent : public ICalculatable {
   public:
    Arctangent(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        return atan(left->Calculate());
    }

   private:
    std::unique_ptr<ICalculatable> left;
};

class Cotangent : public ICalculatable {
   public:
    Cotangent(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        double num = left->Calculate();
        if (num == 0) throw Tasks::TaskInvalidData("Cotangent of 0 is infinity");
        return 1 / tan(num);
    }

   private:
    std::unique_ptr<ICalculatable> left;
};

class Arcotangent : public ICalculatable {
   public:
    Arcotangent(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        double num = left->Calculate();
        return pi / 2 - atan(num);
    }

   private:
    std::unique_ptr<ICalculatable> left;
};

// Другие операторы

class Exponenta : public ICalculatable {
   public:
    Exponenta(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        return exp(left->Calculate());
    }

   private:
    std::unique_ptr<ICalculatable> left;
};

class Absolute : public ICalculatable {
   public:
    Absolute(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        return abs(left->Calculate());
    }

   private:
    std::unique_ptr<ICalculatable> left;
};

class SquareRoot : public ICalculatable {
   public:
    SquareRoot(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        double num = left->Calculate();
        if (num < 0) throw Tasks::TaskInvalidData("Square root of a negative number is not defined");
        return sqrt(num);
    }

   private:
    std::unique_ptr<ICalculatable> left;
};

class Logarithm : public ICalculatable {
public:
    Logarithm(std::unique_ptr<ICalculatable> left_, double base_) : left(std::move(left_)), base(base_) {}
    double Calculate() const override {
        double num = left->Calculate();
        if (num <= 0 || base <= 0 || base == 1) {
            throw Tasks::TaskInvalidData("Logarithm is not defined");
        }
        if (base == 10) {
            return log10(num);
        }
        return log(num)/log(base);
    }

private:
    std::unique_ptr<ICalculatable> left;
    double base;
};

class LogarithmNatural : public ICalculatable {
public:
    LogarithmNatural(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        double num = left->Calculate();
        if (num <= 0) {
            throw Tasks::TaskInvalidData("Logarithm is not defined");
        }
        return log(num);
    }

private:
    std::unique_ptr<ICalculatable> left;
};

class Factorial : public ICalculatable {
public:
    Factorial(std::unique_ptr<ICalculatable> left_) : left(std::move(left_)) {}
    double Calculate() const override {
        double num = left->Calculate();
        if (num > 12) {
            throw Tasks::TaskInvalidData("Factorial is too big");
        }
        if (std::fmod(num, 1) != 0){
            throw Tasks::TaskInvalidData("Factorial shoul be integer");
        }
        if (num == 0) {
            return 1;
        }
        double res = 1;
        for (int i = 1; i <= num; i++) {
            res *= i;
        }
        return res;
    }

private:
    std::unique_ptr<ICalculatable> left;
};