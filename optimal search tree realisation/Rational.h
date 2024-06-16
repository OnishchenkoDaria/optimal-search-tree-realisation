#pragma once

/// @file Rational.h
/// @brief Defines the Rational class representing rational numbers.

/// @class Rational
/// @brief Class representing a rational number.
///
/// The Rational class provides methods to set and get the numerator and denominator of a rational number.
class Rational
{
private:
    int numerator;   ///< Numerator of the rational number
    int denominator; ///< Denominator of the rational number

public:
    /// @brief Constructs a Rational object with specified numerator and denominator.
    /// @param num1 Numerator of the rational number.
    /// @param num2 Denominator of the rational number.
    Rational(int num1, int num2);

    /// @brief Constructs a Rational object with default values (0/0).
    Rational();

    /// @brief Sets the numerator of the rational number.
    /// @param num Numerator to be set.
    void setNumer(int num);

    /// @brief Sets the denominator of the rational number.
    /// @param num Denominator to be set.
    void setDenom(int num);

    /// @brief Gets the numerator of the rational number.
    /// @return The numerator of the rational number.
    int getNumer() const;

    /// @brief Gets the denominator of the rational number.
    /// @return The denominator of the rational number.
    int getDenom() const;
};

/// @brief Constructs a Rational object with specified numerator and denominator.
/// @param num1 Numerator of the rational number.
/// @param num2 Denominator of the rational number.
Rational::Rational(int num1, int num2) : numerator(num1), denominator(num2) {}

/// @brief Constructs a Rational object with default values (0/0).
Rational::Rational() : numerator(0), denominator(0) {}

/// @brief Sets the numerator of the rational number.
/// @param num Numerator to be set.
void Rational::setNumer(int num) {
    numerator = num;
}

/// @brief Sets the denominator of the rational number.
/// @param num Denominator to be set.
void Rational::setDenom(int num) {
    denominator = num;
}

/// @brief Gets the numerator of the rational number.
/// @return The numerator of the rational number.
int Rational::getNumer() const {
    return numerator;
}

/// @brief Gets the denominator of the rational number.
/// @return The denominator of the rational number.
int Rational::getDenom() const {
    return denominator;
}
