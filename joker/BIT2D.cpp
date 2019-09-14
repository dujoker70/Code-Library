#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;

#define dbg(a) cout << "-> " << #a << " = " << a << endl

template<typename T>
struct BIT2D {
    int n, m;
    vector<vector<T>> tree;

    BIT2D (int nn, int mm) {
        n = nn + 1, m = mm + 1;
        tree.resize(n + 1, vector<T>(m + 1, 0));
    }

    void upd (int x, int y, auto v) {
        ++x, ++y;
        while (x < n) {
            for (int yy = y; yy < m; yy += yy & -yy) {
                tree[x][yy] += v;
            }
            x += x & -x;
        }
    }

    T prefSum (int x, int y) {
        ++x, ++y;
        T ret = 0;
        while (x > 0) {
            for (int yy = y; yy > 0; yy -= yy & -yy) {
                ret += tree[x][yy];
            }
            x -= x & -x;
        }
        return ret;
    }

    T gridSum (int x1, int y1, int x2, int y2) {
        return prefSum(x2, y2) - prefSum(x1 - 1, y2) - prefSum(x2, y1 - 1) + prefSum(x1 - 1, y1 - 1);
    }
};

int main() {
    vector<vector<int>> v = {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5}
    };
    BIT2D<int> bit(4, 5);
    for (int i = 0; i < (int) v.size(); i++) {
        for (int j = 0; j < (int) v[i].size(); j++) {
            bit.upd(i, j, v[i][j]);
        }
    }
    cout << bit.prefSum(3, 4) << endl;
    return 0;
}

