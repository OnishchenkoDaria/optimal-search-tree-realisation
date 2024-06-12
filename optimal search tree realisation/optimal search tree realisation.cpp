#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// структура зберігає чисельник і знаменнник раціонального числа
struct Rational {
    int numerator;
    int denominator;
};

//максимальний розмір масиву
#define MAX 300
//ініціалізація нескінченності
#define INF numeric_limits<int>::max()

//пробна вибірка для тестування

int sum[MAX];
//t та root: Двовимірні вектори, які використовуються для зберігання 
// результатів обчислень та коренів оптимальних піддерев.
int t[MAX][MAX];
int root[MAX][MAX];

// обчислює вагу піддерева з вершинами в i та j
int weight(int i, int j, vector<Rational> m) {
    if (i > j) return 0;
    if (i > 0) {
        int total = 0;
        for (int k = i - 1; k <= j - 1; k++) {
            total += m[k].numerator * m[k].denominator;
        }
        return total;
    }
    else {
        return 0;
    }
}

//рекурсивно обходить всі можливі комбінації піддерев та зберігає результати в t та root
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

// виводить корінь(-ені) оптимального піддерева
void printOptimalBST(int i, int j, int parent, vector<Rational> m) {
    if (i <= j) {
        int k = root[i][j];
        cout << "Root: " << m[k - 1].numerator << endl;
    }
}

int main() {
    // Перша вибірка (Цілі числа)
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

    // визначаємо t масив
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            t[i][j] = INF;
        }
    }

    // визначаємо root масив
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            root[i][j] = -1;
        }
    }

    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        t[i][i] = 0;
        sum[i] = sum[i - 1] + m[i - 1].numerator * m[i - 1].denominator;
    }

    int optimal_cost = go(1, n, m);
    cout << "Optimal cost of BST: " << optimal_cost << endl;

    printOptimalBST(1, n, 0, m);

    // Друга вибірка (Раціоанльні)
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

    // визначаємо t масив
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            t[i][j] = INF;
        }
    }

    // визначаємо root масив
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            root[i][j] = -1;
        }
    }

    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        t[i][i] = 0;
        sum[i] = sum[i - 1] + m2[i - 1].numerator * m2[i - 1].denominator;
    }

    int optimal_cost2 = go(1, n, m2);
    cout << "Optimal cost of BST: " << optimal_cost2 << endl;

    printOptimalBST(1, n, 0, m2);
}