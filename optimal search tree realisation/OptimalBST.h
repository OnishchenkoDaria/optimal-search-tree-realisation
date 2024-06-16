#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include "Rational.h"
using namespace std;

/// @file OptimalBST.h
/// @brief Defines the OptimalBST class with methods for constructing an optimal binary search tree.

/// @class OptimalBST
/// @brief Class representing an Optimal Binary Search Tree (BST).
///
/// The OptimalBST class includes methods for calculating and constructing an optimal BST
/// using both sequential and parallel approaches. It uses a Singleton pattern to ensure
/// a single instance of the class is created and provides thread-safe operations.
class OptimalBST
{
private:
    vector<vector<int>> root; ///< Matrix storing roots of subtrees
    vector<vector<int>> t;    ///< Matrix storing costs of subtrees
    vector<int> sum;          ///< Vector storing cumulative sums

    mutex mtx;                ///< Mutex for thread synchronization
    condition_variable cv;    ///< Condition variable for thread synchronization
    atomic<int> active_threads; ///< Counter for active threads
    const int max_threads;    ///< Maximum number of threads allowed

    /// @brief Singleton instance of OptimalBST.
    static OptimalBST* instance;

public:
    static mutex instance_mutex; ///< Mutex for thread-safe singleton access

    /// @brief Constructs an OptimalBST object.
    /// @param max_threads Maximum number of threads allowed for parallel operations.
    OptimalBST(int max_threads);

    static const int MAX = 300; ///< Maximum size of the matrices
    static const int INF = numeric_limits<int>::max(); ///< Infinity value for initialization

    /// @brief Calculates the weight of the subtree with vertices i and j.
    /// @param i Starting index of the subtree.
    /// @param j Ending index of the subtree.
    /// @param m Vector of Rational numbers.
    /// @return Weight of the subtree.
    int weight(int i, int j, const vector<Rational>& m);

    /// @brief Recursively calculates costs and roots for all possible subtrees.
    /// @param i Starting index of the subtree.
    /// @param j Ending index of the subtree.
    /// @param m Vector of Rational numbers.
    /// @return Cost of the subtree.
    int go(int i, int j, const vector<Rational>& m);

    /// @brief Prepares the Rational vector.
    /// @param m Vector of Rational numbers.
    void initialize(const vector<Rational>& m);

    /// @brief Returns the singleton instance of OptimalBST.
    /// @param max_threads Maximum number of threads allowed for parallel operations.
    /// @return Singleton instance of OptimalBST.
    static OptimalBST* getInstance(int max_threads);

    /// @brief Tests the sequential construction of the optimal BST.
    /// @param m Vector of Rational numbers.
    void testSequential(const vector<Rational>& m);

    /// @brief Parallel version of the go function.
    /// @param i Starting index of the subtree.
    /// @param j Ending index of the subtree.
    /// @param m Vector of Rational numbers.
    void parallelGo(int i, int j, const vector<Rational>& m);

    /// @brief Tests the parallel construction of the optimal BST.
    /// @param m Vector of Rational numbers.
    /// @param num_threads Number of threads to be used for parallel construction.
    void testParallel(const vector<Rational>& m, int num_threads);
};

// Initialization of static members
OptimalBST* OptimalBST::instance = nullptr;
mutex OptimalBST::instance_mutex;
