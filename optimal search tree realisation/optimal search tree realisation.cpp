#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// rebuilt rational digit struct as a class
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

    void setDenom(int num)
    {
        this->denominator = num;
    }

    int getNumer() {
        return this->numerator;
    }

    int getDenom() {
        return this->denominator;
    }
};

//setting static values and algorythms as a separate class
class OptimalBST {
private:
    static const int MAX = 300;
    static const int INF = numeric_limits<int>::max();

};

//max range of  the array
#define MAX 300
//initialization of the infinity
#define INF numeric_limits<int>::max()

//пробна вибірка для тестування

int sum[MAX];
//t & root: 2-dimensional vectors used for storing 
//results of the calculations and roots of optimal subtree
int t[MAX][MAX];
int root[MAX][MAX];

//calculates the weight of the subtree with vertexes i & j
int weight(int i, int j, vector<Rational> m) {
    if (i > j) return 0;
    if (i > 0) {
        int total = 0;
        for (int k = i - 1; k <= j - 1; k++) {
            total += m[k].getNumer() * m[k].getDenom();
        }
        return total;
    }
    else {
        return 0;
    }
}

//recursively gose through al possible combinations of subtrees and saves results at and root
int go(int i, int j, vector<Rational> m) {
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

//prints root/-s of optimal subtree
void printOptimalBST(int i, int j, int parent, vector<Rational> m) {
    if (i <= j) {
        int k = root[i][j];
        cout << "Root: " << m[k - 1].getNumer() << endl;
    }
}

int main() {
    //first selection
    vector<Rational> m = {
    {4, 1},
    {10, 1},
    {6, 1},
    {2, 1},
    {3, 1},
    {5, 1},
    {7, 1}
    };

    int n = m.size();

    //initiallize t array
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            t[i][j] = INF;
        }
    }

    //initiallize root array
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            root[i][j] = -1;
        }
    }

    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        t[i][i] = 0;
        sum[i] = sum[i - 1] + m[i - 1].getNumer() * m[i - 1].getDenom();
    }

    int optimal_cost = go(1, n, m);
    cout << "Optimal cost of BST: " << optimal_cost << endl;

    printOptimalBST(1, n, 0, m);

    //second selection
    vector<Rational> m2 = {
        {4, 1},
        {10, 1},
        {6, 1},
        {2, 6},
        {3, 1},
        {5, 3},
        {7, 5}
    };

    n = m2.size();

    //initiallize t array
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            t[i][j] = INF;
        }
    }

    //initiallize root array
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            root[i][j] = -1;
        }
    }

    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        t[i][i] = 0;
        sum[i] = sum[i - 1] + m2[i - 1].getNumer() * m2[i - 1].getDenom();
    }

    int optimal_cost2 = go(1, n, m2);
    cout << "Optimal cost of BST: " << optimal_cost2 << endl;

    printOptimalBST(1, n, 0, m2);
}