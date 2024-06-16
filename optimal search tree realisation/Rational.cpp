#include "Rational.h"

/// @brief Sets the numerator of the rational number.
/// @param num Numerator to be set.
void Rational::setNumer(int num) {
    this->numerator = num;
}

/// @brief Sets the denominator of the rational number.
/// @param num Denominator to be set.
void Rational::setDenom(int num) {
    this->denominator = num;
}

/// @brief Gets the numerator of the rational number.
/// @return The numerator of the rational number.
int Rational::getNumer() const {
    return this->numerator;
}

/// @brief Gets the denominator of the rational number.
/// @return The denominator of the rational number.
int Rational::getDenom() const {
    return this->denominator;
}
