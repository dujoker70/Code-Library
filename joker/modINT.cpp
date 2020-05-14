#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;

#define dbg(a) cout << "-> " << __LINE__ << ": " << #a << " = " << a << endl

inline int add (int a, int b) {
	return (a + b < MOD) ? (a + b) : (a + b - MOD);
}

inline int sub (int a, int b) {
	return (a >= b) ? (a - b) : (a - b + MOD);
}

inline int mul (int a, int b) {
	return int((a * 1LL * b) % MOD);
}

inline int expo (int a, int b) {
	int ret = 1;
	b = (b == -1) ? (MOD - 2) : b;
	while (b != 0) {
		if (b & 1) {
			ret = mul(ret, a);
		}
		a = mul(a, a);
		b >>= 1;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	for (int i = 0; i < 100; i++) {
		cout << i << " = " << expo(2, i) << '\n';
	}
	return 0;
}

