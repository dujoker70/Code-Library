// https://codeforces.com/problemset/problem/600/E - Lomsat Gelral
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;

#define dbg(a) cout << "-> " << #a << " = " << a << endl

int c[MAX]; // color of each vertex
vector<int> G[MAX];

int ptr = 1;
int base[MAX], cnt[MAX], st[MAX], en[MAX], sz[MAX];
long long sum[MAX], mxCnt[MAX];

void dfs(int u, int p) {
    if (p != -1) {
        G[u].erase(find(G[u].begin(), G[u].end(), p));
    }
    base[ptr] = u;
    st[u] = ptr++;
    sz[u] = 1;
    for (int &v : G[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[G[u][0]]) {
                swap(v, G[u][0]);
            }
        }
    }
    en[u] = ptr;
}

void add(int u, int x) {
    ++cnt[x];
    if (cnt[x] == mxCnt[u]) {
        sum[u] += x;
    }
    else if (cnt[x] > mxCnt[u]) {
        mxCnt[u] = cnt[x];
        sum[u] = x;
    }
}

void dsu(int u, int keep) {
    for (int i = 1; i < (int) G[u].size(); i++) {
        dsu(G[u][i], 0);
    }
    if (!G[u].empty()) {
        dsu(G[u][0], 1);
    }
    add(u, c[u]);
    if (!G[u].empty()) {
        if (mxCnt[G[u][0]] == mxCnt[u]) {
            sum[u] += sum[G[u][0]];
        }
        else if(mxCnt[G[u][0]] > mxCnt[u]) {
            sum[u] = sum[G[u][0]];
            mxCnt[u] = mxCnt[G[u][0]];
        }
    }
    for (int i = 1; i < (int) G[u].size(); i++) {
        for (int j = st[G[u][i]]; j < en[G[u][i]]; j++) {
            add(u, c[base[j]]);
        }
    }
    if (keep == 0) {
        for (int i = st[u]; i < en[u]; i++) {
            --cnt[c[base[i]]];
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, -1);
    dsu(1, 0);
    for (int i = 1; i <= n; i++) {
        printf("%lld%c", sum[i], " \n"[i == n]);
    }
    return 0;
}

