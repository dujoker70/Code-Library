#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;

#define dbg(a) cout << "-> " << #a << " = " << a << endl

template<typename T>
struct BIT {
    vector<T> tree;
    
    void upd (int i, auto v) {
        ++i;
        while (i < (int) tree.size()) {
            tree[i] += v;
            i += i & -i;
        }
    }

    BIT (int n) {
        tree.resize(n + 1, 0);
    }

    BIT (const vector<auto> &a) {
        tree.resize(a.size() + 1, 0);
        for (int i = 0; i < (int) a.size(); i++) {
            upd(i, a[i]);
        }
    }

    BIT (const auto *a, int n) {
        tree.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            upd(i, a[i]);
        }
    }

    void push (const vector<auto> &a) {
        tree.resize(a.size() + 1, 0);
        for (int i = 0; i < (int) a.size(); i++) {
            upd(i, a[i]);
        }
    }

    void push (const auto *a, int n) {
        tree.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            upd(i, a[i]);
        }
    }

    T prefSum (int i) {
        ++i;
        T ret = 0;
        while (i > 0) {
            ret += tree[i];
            i -= i & -i;
        }
        return ret;
    }

    T rangeSum (int l, int r) {
        return prefSum(r) - prefSum(l - 1);
    }

    T pos (int i) {
        return rangeSum(i, i);
    }

    void change (int i, int v) {
        upd(i, v - pos(i));
    }
};

int main() {
    vector<int> v = {2, 1, 4, 5, 6};
    BIT<int> bit(v);
    cout << bit.rangeSum(1, 4) << endl;
    return 0;
}

