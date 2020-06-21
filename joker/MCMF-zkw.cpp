/***
    * 1 based node indexing
    * call init at the start of every test case
    * works well on dense graphs
***/

namespace mcmf{
    using T = long long;
    const T INF = 200000000000000LL; /// 0x3f3f3f3f or 0x3f3f3f3f3f3f3f3fLL
    const int MAX = 4410; /// maximum number of nodes

	int n, src, snk, net[MAX], cur[MAX];
	bool vis[MAX];
	T F, C;
	T dis[MAX];

	struct Edge{
		int to;
		T cap, cost, nxt;
	};

	vector <Edge> ed;

	void init(int _n, int _src, int _snk) {
		n = _n, src = _src, snk = _snk;
		memset(net,-1,(n+1) * sizeof(int));
		ed.clear();
	}

	void addEdge(int u, int v, T cap, T cost) {
		ed.pb({v, cap, cost, net[u]});
		net[u] = ed.size() - 1;
		ed.pb({u, 0, -cost, net[v]});
		net[v] = ed.size() - 1;
	}

	bool modell() {
        int v;
		T mn = INF;

		for(int i=1;i<=n;i++) {
			if(!vis[i]) continue;
			for(int j=net[i]; (j!=-1) and  (v=ed[j].to) ; j = ed[j].nxt) {
				if(ed[j].cap){
					if( !vis[v] and  mn > ( dis[v] - dis[i] + ed[j].cost ) ) {
						mn = dis[v] - dis[i] + ed[j].cost;
					}
				}
			}
		}
		if(mn==INF) return false;

		for(int i=1; i<=n; i++) {
			if(vis[i]){
				cur[i] = net[i], vis[i] = false, dis[i] += mn;
			}
		}

		return true;
	}

	T augment(int u, T flow) {
		if(u == snk){
			C += dis[src]*flow;
			F += flow;
			return flow;
		}
		vis[u] = true;
		for(int j=cur[u], v; (j!=-1 and (v=ed[j].to)); j=ed[j].nxt){
			if(!ed[j].cap) continue;
			if(vis[v] or (dis[v]+ed[j].cost)!=dis[u]){
				continue;
			}
			T delta = augment(v, min(flow, ed[j].cap));
			if(delta){
				ed[j].cap -= delta;
				ed[j^1].cap += delta;
				cur[u]=j;
				return delta;
			}
		}
		return 0;
	}

    queue <int> q;
	void spfa() {
		int u, v;

		for(int i=1; i<=n; i++) vis[i] = false , dis[i]=INF;

		dis[src]=0;
		q.push(src);
		vis[src] = true;
		while(!q.empty()) {
			u = q.front(), q.pop();
			vis[u]=false;
			for(int i=net[u]; (i!=-1 && (v=ed[i].to)); i=ed[i].nxt){
				if( !ed[i].cap or dis[v] <= (dis[u]+ed[i].cost) ) continue;
				dis[v] = dis[u] + ed[i].cost;

				if(!vis[v]){
					vis[v]=true, q.push(v);
				}
			}
		}
		for(int i=1; i<=n; i++) dis[i] = dis[snk] - dis[i];
	}

	pair <T,T> solve() {
		spfa();
		C = F = 0;
		memset(vis,0,(n+1) * sizeof(bool));
        memcpy(cur, net, (n + 1) * sizeof(int));
		do{
			while(augment(src, INF)) memset(vis,0,(n+1) * sizeof(bool));
		} while(modell());

		return {F, C};
	}
}
