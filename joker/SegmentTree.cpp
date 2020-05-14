#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;

#define dbg(a) cout << "-> " << #a << " = " << a << endl

template<typename T, int N>
struct SegmentTree {
	int len;
	T tree[4 * N], lazy[4 * N];
	T notFound = 0;

	SegmentTree () {
		len = N;
		memset(tree, 0, sizeof tree);
		memset(lazy, 0, sizeof lazy);
	}

	T merge (T a, T b) {
		return a + b;
	}

	void __build (int ind, int l, int r, const int *a) {
		if (l == r) {
			tree[ind] = a[l];
			return ;
		}
		int mid = (l + r) / 2;
		__build(ind << 1, l, mid, a);
		__build(ind << 1 | 1, mid + 1, r, a);
		tree[ind] = merge(tree[ind << 1], tree[ind << 1 | 1]);
	}

	void __build (int ind, int l, int r, const vector<int> &a) {
		if (l == r) {
			tree[ind] = a[l];
			return ;
		}
		int mid = (l + r) / 2;
		__build(ind << 1, l, mid, a);
		__build(ind << 1 | 1, mid + 1, r, a);
		tree[ind] = merge(tree[ind << 1], tree[ind << 1 | 1]);
	}

	void __lazyUpdate (int ind, int l, int r) {
		tree[ind] = merge(tree[ind], (r - l + 1) * lazy[ind]);
		if (l != r) {
			lazy[ind << 1] = merge(lazy[ind << 1], lazy[ind]);
			lazy[ind << 1 | 1] = merge(lazy[ind << 1 | 1], lazy[ind]);
		}
		lazy[ind] = notFound;
	}

	T __query (int ind, int l, int r, int a, int b) {
		__lazyUpdate(ind, l, r);
		if (a <= l and r <= b) {
			return tree[ind];
		}
		if (r < a or b < l) {
			return notFound;
		}
		int mid = (l + r) / 2;
		return merge(__query(ind << 1, l, mid, a, b), __query(ind << 1 | 1, mid + 1, r, a, b));
	}

	void __update (int ind, int l, int r, int i, T v) {
		__lazyUpdate(ind, l, r);
		if (l == r) {
			tree[ind] = merge(tree[ind], v);
			return ;
		}
		int mid = (l + r) / 2;
		if (i <= mid) {
			__update(ind << 1, l, mid, i, v);
		}
		else {
			__update(ind << 1 | 1, mid + 1, r, i, v);
		}
		tree[ind] = merge(tree[ind << 1], tree[ind << 1 | 1]);
	}

	void __update (int ind, int l, int r, int a, int b, T v) {
		__lazyUpdate(ind, l, r);
		if (r < a or b < l) {
			return ;
		}
		if (a <= l and r <= b) {
			lazy[ind] = v;
			__lazyUpdate(ind, l, r);
			return ;
		}
		int mid = (l + r) / 2;
		__update(ind << 1, l, mid, a, b, v);
		__update(ind << 1 | 1, mid + 1, r, a, b, v);
		tree[ind] = merge(tree[ind << 1], tree[ind << 1 | 1]);
	}

	void build (const T *a, int n) {
		len = n;
		__build(1, 0, len - 1, a);
	}

	void build (const vector<T> &a) {
		len = (int) a.size();
		__build(1, 0, len - 1, a);
	}

	T query (int l, int r) {
		return __query(1, 0, len - 1, l, r);
	}

	T pos (int i) {
		return query(i, i);
	}

	void upd (int i, T v) {
		__update(1, 0, len - 1, i, v);
	}

	void upd (int l, int r, T v) {
		__update(1, 0, len - 1, l, r, v);
	}
};

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		int n, q;
		scanf("%d %d", &n, &q);
		SegmentTree<long long, MAX> tree;
		printf("Case %d:\n", t + 1);
		for (int qq = 0; qq < q; qq++) {
			int typ;
			scanf("%d", &typ);
			if (typ == 0) {
				int x, y, v;
				scanf("%d %d %d", &x, &y, &v);
				tree.upd(x, y, v);
			}
			else {
				int x, y;
				scanf("%d %d", &x, &y);
				printf("%lld\n", tree.query(x, y));
			}
		}
	}
	return 0;
}

