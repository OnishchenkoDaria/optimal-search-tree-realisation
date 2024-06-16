#pragma once
class Rational
{
private:
    int numerator;
    int denominator;

public:
    Rational(int num1, int num2) :numerator(num1),denominator(num2)
    {}

    Rational() :numerator(0),denominator(0)
    {}

    void setNumer(int num);

    void setDenom(int num);

    int getNumer() const;

    int getDenom() const;
};

