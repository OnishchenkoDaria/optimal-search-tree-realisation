#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <mutex>
#include <chrono>
#include <thread>
#include <atomic>
#include <queue>
#include <future>
#include <condition_variable>
//optimalBST class with static values and algorithms
#include "OptimalBST.h"
//rational number class
#include "Rational.h"
//staring sequential and parallel test at the same time
#include "runTests.h"
using namespace std;

/// @file main.cpp
/// @brief The main file to run the tests on OptimalBST.
///
/// This file includes necessary standard libraries and custom headers required
/// for testing the Optimal Binary Search Tree implementation. The main function
/// calls the runTests function with the specified input file.

/// @brief The main method where the tests are summoned.
/// 
/// The main function initializes the testing process by calling the `runTests`
/// function with the input file `index.txt`.
///
/// @return Returns 0 upon successful execution.

int main() {
    runTests("index.txt");
    return 0;
}
