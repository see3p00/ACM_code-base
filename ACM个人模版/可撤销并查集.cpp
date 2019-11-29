struct DSU
{
	int fa[maxn],sz[maxn];
	int find(int x){return x==fa[x]?x:find(fa[x]);}
	std::tuple<int,int,int,int> st[maxn];int top;
	inline void init(int n)
	{
		for(int i=0;i<=n;i++)fa[i]=i,sz[i]=0,top=0;
	}
	inline bool merge(int u,int v,bool flag)
	{
		u=find(u),v=find(v);
		if(u==v) return false;
		if(flag) st[++top]={u,v,sz[u],sz[v]};
		if(sz[u]>sz[v]) std::swap(u,v);fa[u]=v;
		if(sz[u]==sz[v]) ++sz[v];
		return true;
	}
	inline void undo()
	{
		std::tuple<int,int,int,int> cur=st[top--];
		sz[fa[std::get<0>(cur)]=std::get<0>(cur)]=std::get<2>(cur);
		sz[fa[std::get<1>(cur)]=std::get<1>(cur)]=std::get<3>(cur);
	}
}dsu;