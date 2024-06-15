#include "OptimalBST.h"

int OptimalBST::weight(int i, int j, const vector<Rational>& m) {
    if (i > j) return 0;
    int total = 0;
    for (int k = i; k <= j; k++) {
        total += m[k].getNumer() * m[k].getDenom();
    }
    return total;
}

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

OptimalBST* OptimalBST::getInstance(int max_threads) {
    lock_guard<mutex> lock(instance_mutex);
    if (instance == nullptr) {
        instance = new OptimalBST(max_threads);
    }
    return instance;
}

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