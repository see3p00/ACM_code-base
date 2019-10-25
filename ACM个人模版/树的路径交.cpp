// 树的路径交
//给定一棵n个点的树，以及m条路径
//每次询问第L条到第R条路径的交集部分的长度（如果一条边同时出现在2条路径上，那么它属于路径的交集。
#include <bits/stdc++.h>

const int maxn = 5e5 + 5;

std::vector<std::pair<int,int>> G[maxn];
int dep[maxn],Fa[maxn][21],x[maxn],y[maxn],n,m,q;
long long dis[maxn];
void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1;
	Fa[u][0]=fa;
	for(int i=1;i<21;i++) Fa[u][i]=Fa[Fa[u][i-1]][i-1];
	for(auto &it:G[u])
	{
		int v,w;std::tie(v,w)=it;
		if(v==fa)continue;
		dis[v]=dis[u]+w;
		dfs(v,u);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) std::swap(x,y);
	for(int i=20;i>=0;i--)if((1<<i)<=dep[x]-dep[y]) x=Fa[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)if(Fa[x][i]!=Fa[y][i]) x=Fa[x][i],y=Fa[y][i];
	return Fa[x][0];
}
long long dist(int x,int y){return dis[x]+dis[y]-2ll*dis[lca(x,y)];}

struct SegTree
{
	std::pair<int,int> sum[maxn<<2];
	inline std::pair<int,int> merge(std::pair<int,int>x,std::pair<int,int>y)
	{
		int d[]={lca(x.first,y.first),lca(x.first,y.second),lca(x.second,y.first),lca(x.second,y.second)};
		std::sort(d,d+4,[&](int x,int y){return dep[x]>dep[y];});
		return std::pair<int,int>(d[0],d[1]);
	}
	inline void pushup(int o)
	{
		sum[o]=merge(sum[o<<1],sum[o<<1|1]);
	}
	inline void build(int o,int l,int r)
	{
		if(l==r){sum[o].first=x[l],sum[o].second=y[l];return ;}
		int m=(l+r)>>1;
		build(o<<1,l,m);build(o<<1|1,m+1,r);
		pushup(o);
	}
	inline std::pair<int,int> query(int o,int l,int r,int ql,int qr)
	{
		if(ql<=l&&r<=qr)return sum[o];
		int m=(l+r)>>1; std::pair<int,int>ans;bool f=0;
		if(ql<=m) ans=query(o<<1,l,m,ql,qr),f=1;
		if(qr>m) f?ans=merge(query(o<<1|1,m+1,r,ql,qr),ans):ans=query(o<<1|1,m+1,r,ql,qr);
		return ans;
	}
}st;
int main()
{
#ifdef LOCAL
    freopen("input.txt","r",stdin);
#endif
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
    	int u,v,w;scanf("%d%d%d",&u,&v,&w);
    	G[u].emplace_back(v,w);
    	G[v].emplace_back(u,w);
    }
    dfs(1,0);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)scanf("%d%d",&x[i],&y[i]);
    st.build(1,1,m);
    scanf("%d",&q);
    while(q--)
    {
    	int l,r;scanf("%d%d",&l,&r);
    	std::pair<int,int> tmp=st.query(1,1,m,l,r);
    	int u=tmp.first,v=tmp.second;
    	printf("%lld\n",dist(u,v));
    }
    return 0;
}