#include "OptimalBST.h"

// Initialization of static members
OptimalBST* OptimalBST::instance = nullptr;
mutex OptimalBST::instance_mutex /*= nullptr*/;

/// @brief Calculates the weight of the subtree with vertices i and j.
/// @param i Starting index of the subtree.
/// @param j Ending index of the subtree.
/// @param m Vector of Rational numbers.
/// @return Weight of the subtree.
int OptimalBST::weight(int i, int j, const vector<Rational>& m) {
    if (i > j) return 0;
    int total = 0;
    for (int k = i; k <= j; k++) {
        total += m[k].getNumer() * m[k].getDenom();
    }
    return total;
}

/// @brief Recursively calculates costs and roots for all possible subtrees.
/// @param i Starting index of the subtree.
/// @param j Ending index of the subtree.
/// @param m Vector of Rational numbers.
/// @return Cost of the subtree.
int OptimalBST::go(int i, int j, const vector<Rational>& m) {
    if (i > j) return 0;
    if (t[i][j] == INF) {
        for (int k = i; k <= j; k++) {
            int temp = go(i, k - 1, m) + go(k + 1, j, m) + weight(i, k - 1, m) + weight(k + 1, j, m);
            if (temp < t[i][j]) {
                t[i][j] = temp;
                root[i][j] = k;
            }
        }
    }
    return t[i][j];
}

/// @brief Prepares the Rational vector and initializes the matrices.
/// @param m Vector of Rational numbers.
void OptimalBST::initialize(const vector<Rational>& m) {
    int n = m.size();
    for (int i = 0; i < n; i++) {
        fill(t[i].begin(), t[i].end(), INF);
        fill(root[i].begin(), root[i].end(), -1);
    }
    sum[0] = 0;
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + m[i].getNumer() * m[i].getDenom();
        t[i][i] = 0;
    }
}

/// @brief Returns the singleton instance of OptimalBST.
/// @param max_threads Maximum number of threads allowed for parallel operations.
/// @return Singleton instance of OptimalBST.
OptimalBST* OptimalBST::getInstance(int max_threads) {
    lock_guard<mutex> lock(instance_mutex);
    if (instance == nullptr) {
        instance = new OptimalBST(max_threads);
    }
    return instance;
}

/// @brief Tests the sequential construction of the optimal BST.
/// @param m Vector of Rational numbers.
void OptimalBST::testSequential(const vector<Rational>& m) {
    initialize(m);
    int n = m.size() - 1;

    //fixation of time and summoning the algorithm in sequential workflow
    int optimal_cost = go(0, n, m);

    //time print
    {
        lock_guard<mutex> lock(mtx);
        cout << "Sequential optimal cost of bst: " << optimal_cost << endl;
        cout << "(Thread: " << this_thread::get_id() << ")" << endl;
    }
}

/// @brief Parallel version of the go function.
/// @param i Starting index of the subtree.
/// @param j Ending index of the subtree.
/// @param m Vector of Rational numbers.
void OptimalBST::parallelGo(int i, int j, const vector<Rational>& m) {
    int start = i;
    int end = j;

    auto lambda = [&]() {
        for (int k = start; k <= end; ++k) {
            int temp = go(start, k - 1, m) + go(k + 1, end, m) + weight(start, k - 1, m) + weight(k + 1, end, m);
            {
                lock_guard<mutex> lock(mtx);
                if (temp < t[start][end]) {
                    t[start][end] = temp;
                    root[start][end] = k;
                }
            }
        }
        };

    lambda();
}

/// @brief Tests the parallel construction of the optimal BST.
/// @param m Vector of Rational numbers.
/// @param num_threads Number of threads to be used for parallel construction.
void OptimalBST::testParallel(const vector<Rational>& m, int num_threads) {
    initialize(m);
    int n = m.size() - 1;

    parallelGo(0, n, m);

    int optimal_cost = t[0][n];
    {
        lock_guard<mutex> lock(mtx);
        cout << "Parallel optimal cost of bst: " << optimal_cost << endl;
        cout << "(Thread: " << this_thread::get_id() << ")" << endl;
    }
}