#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;

#define dbg(a) cout << "-> " << #a << " = " << a << endl

template <typename T, int N>
struct BIT {
    int tree[N];
    
	BIT () {
		memset(tree, 0, sizeof tree);
	}

    void upd (int i, T v) {
        ++i;
        while (i < N) {
            tree[i] += v;
            i += i & -i;
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
    BIT<int, 10> bit;
	for (int i = 0; i < (int) v.size(); i++) {
		bit.upd(i, v[i]);
	}
    cout << bit.rangeSum(1, 4) << endl;
	for (int i = 0; i < (int) v.size(); i++) {
		cout << bit.pos(i) << endl;
	}
    return 0;
}

