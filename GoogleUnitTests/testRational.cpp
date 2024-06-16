#include "gtest/gtest.h"
#include "C:\Users\User\Desktop\optimal tree\optimal search tree realisation\optimal search tree realisation\Rational.h"
#include <vector>
#include <iostream>


using namespace std;

/*
// Test suite for the Rational class
class Rational : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize resources for tests
    }

    void TearDown() override {
        // Clean up resources
    }
};
*/

TEST(RationalTest, SetAndGetNumer) {
    Rational r(0,0);
    r.setNumer(5);
    EXPECT_EQ(r.getNumer(), 5);
}

TEST(Rational, SetAndGetDenom) {
    Rational r;
    r.setDenom(10);
    EXPECT_EQ(r.getDenom(), 10);
}

TEST(Rational, SetNumerDoesNotAffectDenom) {
    Rational r;
    r.setDenom(10);
    r.setNumer(5);
    EXPECT_EQ(r.getDenom(), 10);
}

TEST(Rational, SetDenomDoesNotAffectNumer) {
    Rational r;
    r.setNumer(5);
    r.setDenom(10);
    EXPECT_EQ(r.getNumer(), 5);
}

TEST(Rational, InitialValues) {
    Rational r;
    EXPECT_EQ(r.getNumer(), 0); 
    EXPECT_EQ(r.getDenom(), 0);
}
