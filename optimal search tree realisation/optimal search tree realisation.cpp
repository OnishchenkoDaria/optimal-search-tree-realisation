#include <iostream>
#include <vector>
#include <limits>
using namespace std;

//rebuilt rational digit struct as a class
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

//setting static values and algorithms as a separate class
class OptimalBST {
private:
    vector<vector<int>> t;
    vector<vector<int>> root;
    vector<int> sum;

public:
    static const int MAX = 300;
    static const int INF = numeric_limits<int>::max();

    OptimalBST() : t(MAX, vector<int>(MAX, INF)), root(MAX, vector<int>(MAX, -1)), sum(MAX, 0) {}

    //calculates the weight of the subtree with vertices i & j
    int weight(int i, int j, const vector<Rational>& m) {
        if (i > j) return 0;
        int total = 0;
        for (int k = i; k <= j; k++) {
            total += m[k].getNumer() * m[k].getDenom();
        }
        return total;
    }

    //recursively goes through all possible combinations of subtrees and saves results at t and root
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

    //print the structure of the optimal BST
    void printOptimalBST(int i, int j, const vector<Rational>& m) {
        if (i <= j) {
            int k = root[i][j];
            cout << "Root: " << m[k].getNumer() << endl;
        }
    }

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

    void test(const vector<Rational>& m, int num_threads) {
        initialize(m);
        int n = m.size() - 1;

        int optimal_cost = go(0, n, m);
        cout << "Optimal cost of BST: " << optimal_cost << endl;
        printOptimalBST(0, n, m);
    }
};

void runTests() {
    OptimalBST bst;

    vector<Rational> m1 = {
        {4, 1},
        {10, 1},
        {6, 1},
        {2, 1},
        {3, 1},
        {5, 1},
        {7, 1}
    };

    vector<Rational> m2 = {
        {4, 1},
        {10, 1},
        {6, 1},
        {2, 6},
        {3, 1},
        {5, 3},
        {7, 5}
    };

    bst.test(m1, 4);
    bst.test(m2, 4);
}

int main() {
    runTests();
}
