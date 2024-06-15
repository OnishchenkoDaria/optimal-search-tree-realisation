#pragma once
class Rational
{
private:
    int numerator;
    int denominator;

public:
    Rational(int num1, int num2) {
        this->setNumer(num1);
        this->setDenom(num2);
    }

    void setNumer(int num);

    void setDenom(int num);

    int getNumer() const;

    int getDenom() const;
};

