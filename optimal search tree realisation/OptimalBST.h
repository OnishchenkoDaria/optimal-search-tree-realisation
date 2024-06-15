#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include "Rational.h"
using namespace std; 

class OptimalBST
{
private:
    vector<vector<int>> t;
    vector<vector<int>> root;
    vector<int> sum;

    mutex mtx;
    condition_variable cv;
    atomic<int> active_threads;
    const int max_threads;

    //singleton instance
    static OptimalBST* instance;
    static mutex instance_mutex;

    OptimalBST(int max_threads) : t(MAX, vector<int>(MAX, INF)), root(MAX, vector<int>(MAX, -1)), sum(MAX, 0), max_threads(max_threads), active_threads(0) {}

    //calculates the weight of the subtree with vertices i & j
    int weight(int i, int j, const vector<Rational>& m);

    //recursively goes through all possible combinations of subtrees and saves results in t and root
    int go(int i, int j, const vector<Rational>& m);

    //preparing the rational vector
    void initialize(const vector<Rational>& m);

public:
    static const int MAX = 300;
    static const int INF = numeric_limits<int>::max();

    //thread-safe Singleton getter
    static OptimalBST* getInstance(int max_threads);

    void testSequential(const vector<Rational>& m); 

    void parallelGo(int i, int j, const vector<Rational>& m);

    void testParallel(const vector<Rational>& m, int num_threads);
};

