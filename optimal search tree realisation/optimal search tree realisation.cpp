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

//initialize the Singleton instance and mutex
OptimalBST* OptimalBST::instance = nullptr;
mutex OptimalBST::instance_mutex;

int main() {
    runTests("index.txt");
    return 0;
}
