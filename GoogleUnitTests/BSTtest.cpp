#include "gtest/gtest.h"
#include "C:\Users\User\Desktop\optimal tree\optimal search tree realisation\optimal search tree realisation\OptimalBST.h"
#include "C:\Users\User\Desktop\optimal tree\optimal search tree realisation\optimal search tree realisation\OptimalBST.cpp"
#include "C:\Users\User\Desktop\optimal tree\optimal search tree realisation\optimal search tree realisation\Rational.cpp"



using namespace std;


TEST(OptimalBSTTest, WeightTest) {
    OptimalBST optimalBST(1);
    vector<Rational> m = { Rational(1, 2), Rational(3, 4), Rational(5, 6) };
    int weight = optimalBST.weight(0, 2, m);
    EXPECT_EQ(weight, 44); //expected result based on getNumer()*getDenom()
}

TEST(OptimalBSTTest, GoTest) {
    OptimalBST optimalBST(1);
    vector<Rational> m = { Rational(1, 2), Rational(3, 4), Rational(5, 6) };
    optimalBST.initialize(m);
    int cost = optimalBST.go(0, 2, m);
    EXPECT_EQ(cost, 16); 
}

TEST(OptimalBSTTest, InitializeTest) {
    OptimalBST optimalBST(1);

    vector<Rational> m = { Rational(1, 2), Rational(3, 4), Rational(5, 6) };
    optimalBST.initialize(m);
    //EXPECT_EQ(optimalBSTt[.0][0], 0);
    EXPECT_EQ(optimalBST.sum[3], 44); 
}

TEST(OptimalBSTTest, TestSequential) {
    OptimalBST optimalBST(1);

    vector<Rational> m = { Rational(1, 2), Rational(3, 4), Rational(5, 6) };
    optimalBST.testSequential(m);
    int optimal_cost = optimalBST.t[0][2];
    EXPECT_EQ(optimal_cost, 16); }

TEST(OptimalBSTTest, TestParallel) {
    OptimalBST optimalBST(1);

    vector<Rational> m = { Rational(1, 2), Rational(3, 4), Rational(5, 6) };
    optimalBST.testParallel(m, 2); // using 2 threads for parallel execution
    int optimal_cost = optimalBST.t[0][2];
    EXPECT_EQ(optimal_cost, 16); 
}


