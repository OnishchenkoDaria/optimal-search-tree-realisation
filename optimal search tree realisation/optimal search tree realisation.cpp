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

using namespace std;

//rational number class
class Rational {
private:
    int numerator;
    int denominator;

public:
    Rational(int num1, int num2) {
        this->setNumer(num1);
        this->setDenom(num2);
    }

    void setNumer(int num) {
        this->numerator = num;
    }

    void setDenom(int num) {
        this->denominator = num;
    }

    int getNumer() const {
        return this->numerator;
    }

    int getDenom() const {
        return this->denominator;
    }
};

//optimalBST class with static values and algorithms
class OptimalBST {
private:
    vector<vector<int>> t;
    vector<vector<int>> root;
    vector<int> sum;

    mutex mtx;
    condition_variable cv;
    atomic<int> active_threads;
    const int max_threads;

    //calculates the weight of the subtree with vertices i & j
    int weight(int i, int j, const vector<Rational>& m) {
        if (i > j) return 0;
        int total = 0;
        for (int k = i; k <= j; k++) {
            total += m[k].getNumer() * m[k].getDenom();
        }
        return total;
    }

    //recursively goes through all possible combinations of subtrees and saves results in t and root
    int go(int i, int j, const vector<Rational>& m) {
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

    //preparing the rational vector
    void initialize(const vector<Rational>& m) {
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

public:
    static const int MAX = 300;
    static const int INF = numeric_limits<int>::max();

    OptimalBST(int max_threads) : t(MAX, vector<int>(MAX, INF)), root(MAX, vector<int>(MAX, -1)), sum(MAX, 0), max_threads(max_threads), active_threads(0) {}

    void testSequential(const vector<Rational>& m) {
        initialize(m);
        int n = m.size() - 1;

        //fixation of time and summoning the algorithm in sequential workflow
        int optimal_cost = go(0, n, m);

        //time print
        {
            lock_guard<mutex> lock(mtx);
            cout << "sequential optimal cost of bst: " << optimal_cost << endl;
            cout << "(Thread: " << this_thread::get_id() << ")" << endl;
        }
    }

    void parallelGo(int i, int j, const vector<Rational>& m) {
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



    void testParallel(const vector<Rational>& m, int num_threads) {
        initialize(m);
        int n = m.size() - 1;

        parallelGo(0, n, m);
        
        int optimal_cost = t[0][n];
        {
            lock_guard<mutex> lock(mtx);
            cout << "parallel optimal cost of bst: " << optimal_cost << endl;
            cout << "(Thread: " << this_thread::get_id() << ")" << endl;
        }
    }
};

void runTests(const string& filename) {
    OptimalBST bst(4);
    ifstream infile(filename);
    string line;

    //for the read dataset
    vector<vector<Rational>> testCases;
    vector<string> indices;

    //reading the file content and storing it in memory to avoid reading issues during multithreading
    while (getline(infile, line)) {
        stringstream ss(line);
        string index;
        getline(ss, index, ':');
        vector<Rational> m;
        string rational;
        while (getline(ss, rational, ';')) {
            int num, denom;
            stringstream rs(rational);
            rs >> num >> denom;
            m.emplace_back(num, denom);
        }
        indices.push_back(index);
        testCases.push_back(m);
    }

    cout << "Executing Sequential Tests:" << endl;
    auto sequential_start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < testCases.size(); ++i) {
        cout << "testing set " << indices[i] << endl;
        bst.testSequential(testCases[i]);
    }
    auto sequential_finish = chrono::high_resolution_clock::now();
    chrono::duration<double> sequential_worktime = sequential_finish - sequential_start;
    auto sequential_microtime = chrono::duration_cast<chrono::milliseconds>(sequential_worktime);
    cout << "TOTAL DURATION OF SEQUENTIAL TESTS : " << sequential_microtime.count() << " ms" << endl;

    cout << "\nExecuting Parallel Tests:" << endl;

    //determine the number of threads to use
    int num_threads = 4;
    size_t data_size = testCases.size();
    size_t chunk_size = (data_size + num_threads - 1) / num_threads;

    //vector to hold the thread objects
    vector<thread> threads;

    auto parallel_start = chrono::high_resolution_clock::now();

    //launch threads to process parts of data
    for (int t = 0; t < num_threads; ++t) {
        threads.emplace_back([&bst, &testCases, t, chunk_size, data_size, &indices]() {
            size_t start_idx = t * chunk_size;
            size_t end_idx = min(start_idx + chunk_size, data_size);

            for (size_t i = start_idx; i < end_idx; ++i) {
                cout << "testing set " << indices[i] << endl;
                bst.testParallel(testCases[i], 4);
            }
            });
    }

    //wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    auto parallel_finish = chrono::high_resolution_clock::now();
    chrono::duration<double> parallel_worktime = parallel_finish - parallel_start;
    auto parallel_microtime = chrono::duration_cast<chrono::milliseconds>(parallel_worktime);
    cout << "TOTAL DURATION OF PARALLEL TESTS: " << parallel_microtime.count() << " ms" << endl;
}

int main() {
    runTests("index.txt");
    return 0;
}
