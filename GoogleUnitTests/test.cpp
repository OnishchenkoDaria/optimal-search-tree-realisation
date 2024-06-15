#include "pch.h"
#include "C:\Users\User\Desktop\optimal tree\optimal search tree realisation\optimal search tree realisation\OptimalBST.h"
#include <vector>

using namespace std;

// A simple implementation of the Rational class for testing purposes
class Rational {
public:
    Rational(int numer, int denom) : numer(numer), denom(denom) {}
    int getNumer() const { return numer; }
    int getDenom() const { return denom; }
private:
    int numer;
    int denom;
};

class OptimalBSTTest : public ::testing::Test {
protected:
    OptimalBST* optimalBST = OptimalBST::getInstance(1);
};

TEST_F(OptimalBSTTest, WeightTest) {
    vector<Rational> m = { Rational(1, 2), Rational(3, 4), Rational(5, 6) };
    int weight = optimalBST->weight(0, 2, m);
    EXPECT_EQ(weight, 44); //expected result based on getNumer()*getDenom()
}

TEST_F(OptimalBSTTest, GoTest) {
    vector<Rational> m = { Rational(1, 2), Rational(3, 4), Rational(5, 6) };
    optimalBST->initialize(m);
    int cost = optimalBST->go(0, 2, m);
    EXPECT_EQ(cost, 0); 
}

TEST_F(OptimalBSTTest, InitializeTest) {
    vector<Rational> m = { Rational(1, 2), Rational(3, 4), Rational(5, 6) };
    optimalBST->initialize(m);
    EXPECT_EQ(optimalBST->t[0][0], 0);
    EXPECT_EQ(optimalBST->sum[3], 44); 
}

TEST_F(OptimalBSTTest, TestSequential) {
    vector<Rational> m = { Rational(1, 2), Rational(3, 4), Rational(5, 6) };
    optimalBST->testSequential(m);
    int optimal_cost = optimalBST->t[0][2];
    EXPECT_EQ(optimal_cost, 16); }

TEST_F(OptimalBSTTest, TestParallel) {
    vector<Rational> m = { Rational(1, 2), Rational(3, 4), Rational(5, 6) };
    optimalBST->testParallel(m, 2); // using 2 threads for parallel execution
    int optimal_cost = optimalBST->t[0][2];
    EXPECT_EQ(optimal_cost, 16); 
}

