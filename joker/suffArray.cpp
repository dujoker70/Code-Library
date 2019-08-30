#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e3 + 5;
const int MOD = 1e9 + 7;
const int LOGN = 13;
#define dbg(x) cout << "-> " << #x << " = " << x << endl

struct Node {
    int a, b;
    int ind;
    Node() {}
    bool operator < (const Node &p) const {
        return (a == p.a) ? b < p.b : a < p.a;
    }
};

vector<int> suf, lcp;
int P[LOGN][MAX], lg;

int getLcp(int i, int j) {
    int ret = 0;
    for(int k = lg; k >= 0; k--) {
        if(P[k][i] == P[k][j]) {
            ret += 1 << k;
            i += 1 << k;
            j += 1 << k;
        }
    }
    return ret;
}

void buildSuff(char *str, int n) {
    memset(P, -1, sizeof P);
    vector<Node> ara(n);
    suf.resize(n);
    lcp.resize(n);
    if(n == 1) {
        suf[0] = 0;
        return ;
    }
    for(int i = 0; i < n; i++) {
        P[0][i] = str[i] - 'a';
    }
    lg = 1;
    for(int k = 1; k < n; k *= 2, lg++) {
        for(int i = 0; i < n; i++) {
            ara[i].ind = i;
            ara[i].a = P[lg - 1][i];
            ara[i].b = (i + k < n) ? P[lg - 1][i + k] : -1;
        }
        sort(ara.begin(), ara.end());
        for(int i = 0; i < n; i++) {
            P[lg][ara[i].ind] = (i > 0 and ara[i].a == ara[i - 1].a and ara[i].b == ara[i - 1].b) ? P[lg][ara[i - 1].ind] : i;
        }
    }
    --lg;
    for(int i = 0; i < n; i++) {
        suf[P[lg][i]] = i;
    }
}

int main() {
	char str[MAX];
    scanf("%s", str);

    int n = strlen(str);
    buildSuff(str, n);
    
    lcp[0] = 0;
    for(int i = 1; i < n; i++) {
        lcp[i] = getLcp(suf[i], suf[i - 1]);
    }

    int ans = 0;
    for(int i = 0; i < n; i++) {
        ans += n - suf[i] - lcp[i];
    }
    printf("%d\n", ans);
	return 0;
}

