#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using base = complex <ld>;

const ld PI = acos(-1);

void fft(vector<base> &a, bool inv = false) {
	int n = a.size();
	for(int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for( ; j >= bit; bit >>= 1) {
			j -= bit;
		}
		j += bit;
		if(i < j) {
			swap(a[i], a[j]);
		}
	}
	for(int len = 2; len <= n; len <<= 1) {
		ld ang = 2 * PI / len * (inv ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len) {
			base w(1);
			for(int j = 0; j < len / 2; j++, w *= wlen) {
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
			}
		}
	}
	if(inv) {
		for(auto &v : a) {
			v /= n;
		}
	}
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
	vector<int> res;
	vector<base> fa(a.begin(), a.end());
	vector<base> fb(b.begin(), b.end());
	size_t n = 1;
	while(n < max(a.size(), b.size())) {
		n <<= 1;
	}
	n <<= 1;
	fa.resize(n), fft(fa);
	fb.resize(n), fft(fb);
	for(size_t i = 0; i < n; i++) {
		fa[i] *= fb[i];
	}
	fft(fa, true);
	res.resize(n);
	for(size_t i = 0; i < n; i++) {
		res[i] = (int) (fa[i].real() + 0.5);
	}
	return res;
}

int main() {
	vector<int> res = multiply({3, 2, 1}, {3, 4});
	for(int v : res) {
		cout << v << " " << endl;
	}
	return 0;
}

