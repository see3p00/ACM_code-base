struct Edge
{
    int from;
    int to;
    ll dist;
};
struct BellmanFord
{
    int n,m;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool inq[maxn]; //是否在队列中
    ll d[maxn]; //s到各个点的距离
    ll p[maxn]; //最短路中的上一条弧
    int cnt[maxn]; //进队次数
    void init(int n)
    {
        this->n = n;
        for(int i=0;i<n;i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from,int to,ll dist)
    {
        edges.push_back((Edge) {from,to,dist});
        m = edges.size();
        G[from].push_back(m-1);
    }
    void popback(int s,int t)
    {
    	edges.pop_back();
    	G[s].pop_back();
    }
    bool negetiveCycle()
    {
        queue<int> Q;
        memset(inq,0,sizeof(inq));
        memset(cnt,0,sizeof(cnt));
        for(int i=0;i<n;i++) {d[i] = 0;inq[0] = true;Q.push(i);}
        while(!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            inq[u] = false;
            for(int i=0;i<G[u].size();i++)
            {
                Edge& e = edges[G[u][i]];
                if(d[e.to] > d[u] + e.dist)
                {
                    d[e.to] = d[u] + e.dist;
                    p[e.to] = G[u][i];
                    if(!inq[e.to]) {Q.push(e.to);inq[e.to] = true;if(++cnt[e.to] > n) return true;}
                }
            }
        }
        return false;
    }
}G;
        G.init(n);
		for(int i=1;i<=m;i++)
		{
			int u,v;ll w;scanf("%d%d%lld",&u,&v,&w);
			G.AddEdge(u,v,w);
		}