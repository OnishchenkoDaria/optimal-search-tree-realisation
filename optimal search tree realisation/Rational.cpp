#include "Rational.h"

void Rational::setNumer(int num) {
    this->numerator = num;
}

void Rational::setDenom(int num) {
    this->denominator = num;
}

int Rational::getNumer() const {
    return this->numerator;
}

int Rational::getDenom() const {
    return this->denominator;
}