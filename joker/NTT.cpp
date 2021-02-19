#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int G = 3;
const int M = 998244353;
const int N = (1 << 20) + 5; // greater than maximum possible degree of any polynomial

inline int add (int a, int b) {
    return (a + b < M) ? (a + b) : (a + b - M);
}

inline int sub (int a, int b) {
    return (a >= b) ? (a - b) : (a - b + M);
}

inline int mul (int a, int b) {
    return int((a * 1LL * b) % M);
}

inline int expo (int a, int b) {
    int ret = 1;
    b = (b == -1) ? (M - 2) : b;
    while (b != 0) {
        if (b & 1) {
            ret = mul(ret, a);
        }
        a = mul(a, a);
        b >>= 1;
    }
    return ret;
}

int rev[N], w[N], inv_n;

void prepare(int &n) {
    int sz = abs(31 - __builtin_clz(n));
    int r = expo(G, (M - 1) / n);
    inv_n = expo(n, -1), w[0] = w[n] = 1;
    for (int i = 1; i < n; ++i) w[i] = mul(w[i - 1], r);
    for (int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1));
}

void ntt (int *a, int n, int dir) {
    for (int i = 1; i < n - 1; ++i) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int m = 2; m <= n; m <<= 1) {
        for (int i = 0; i < n; i += m) {
            for (int j = 0; j < (m >> 1); ++j) {
                int &u = a[i + j], &v = a[i + j + (m >> 1)];
                int t = mul(v, w[dir ? n - n / m * j : n / m * j]);
                v = u - t < 0 ? u - t + M : u - t;
                u = u + t >= M ? u + t - M : u + t;
            }
        }
    }
    if (dir) for (int i = 0; i < n; ++i) a[i] = mul(a[i], inv_n);
}

int f_a[N], f_b[N];

vector <int> multiply (const vector <int> &a, const vector <int> &b) {
    int sz = 1, n = (int) a.size(), m = (int) b.size();
    while (sz < n + m - 1) sz <<= 1; prepare(sz);
    for (int i = 0; i < sz; ++i) f_a[i] = i < n ? a[i] : 0;
    for (int i = 0; i < sz; ++i) f_b[i] = i < m ? b[i] : 0;
    ntt(f_a, sz, 0); ntt(f_b, sz, 0);
    for (int i = 0; i < sz; ++i) f_a[i] = mul(f_a[i], f_b[i]);
    ntt(f_a, sz, 1); return vector <int> (f_a, f_a + n + m - 1);
}

// G = primitive_root(M)
int primitive_root (int p) {
    vector <int> factor;
    int tmp = p - 1;
    for (int i = 2; i * i <= tmp; ++i) {
        if (tmp % i == 0) {
            factor.emplace_back(i);
            while (tmp % i == 0) tmp /= i;
        }
    }
    if (tmp != 1) factor.emplace_back(tmp);
    for (int root = 1; ; ++root) {
        bool flag = true;
        for (int i = 0; i < (int) factor.size(); ++i) {
            if (expo(root, (p - 1) / factor[i]) == 1) {
                flag = false; break;
            }
        }
        if (flag) return root;
    }
}

int main() {
    // (x + 2)(x + 3) = x^2 + 5x + 6
    vector <int> a = {2, 1};
    vector <int> b = {3, 1};
    vector <int> c = multiply(a, b);
    for (int x : c) cout << x << " "; cout << endl;
    return 0;
}
