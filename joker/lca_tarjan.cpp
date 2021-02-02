// https://codeforces.com/problemset/problem/191/C

#include <bits/stdc++.h>
using namespace std;
 
#define dbg(v) cout << __LINE__ << ": " << #v << " = " << v << endl
 
const int N = 1e5 + 5;
 
struct DSU {
    int n;
    vector <int> parent;
    DSU (int nn) : n(nn) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    int find (int u) {
        return (parent[u] == u) ? u : (parent[u] = find(parent[u]));
    }
    void add (int u, int v) {
        u = find(u), v = find(v);
        parent[u] = v;
    }
};
 
int main() {
    int n;
    scanf("%d", &n);
    vector <vector <pair <int, int>>> a(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u, --v;
        a[u].emplace_back(v, i);
        a[v].emplace_back(u, i);
    }
    int k;
    scanf("%d", &k);
    vector <vector <pair <int, int>>> query(n);
    vector <pair <int, int>> q(k);
    for (int i = 0; i < k; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u, --v;
        query[u].emplace_back(v, i);
        query[v].emplace_back(u, i);
        q[i] = {u, v};
    }
    DSU dsu(n);
    vector <int> lca(k), anc(n);
    vector <bool> vis(n);
    function <void(int)> dfs = [&] (int u) {
        vis[u] = true;
        anc[u] = u;
        for (auto [v, id] : a[u]) {
            if (!vis[v]) {
                dfs(v);
                dsu.add(u, v);
                anc[dsu.find(u)] = u;
            }
        }
        for (auto [v, id] : query[u]) {
            if (vis[v]) {
                lca[id] = anc[dsu.find(v)];
            }
        }
    };
    dfs(0);
    vector <int> val(n);
    for (int i = 0; i < k; i++) {
        auto [u, v] = q[i];
        int g = lca[i];
        ++val[u], ++val[v];
        val[g] -= 2;
    }
    vector <int> ans(n - 1);
    function <void(int, int)> dfs2 = [&] (int u, int p) {
        for (auto [v, id] : a[u]) {
            if (v != p) {
                dfs2(v, u);
                val[u] += val[v];
                ans[id] = val[v];
            }
        }
    };
    dfs2(0, -1);
    for (int v : ans) {
        printf("%d ", v);
    }
    puts("");
    return 0;
}
