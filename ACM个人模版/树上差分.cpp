#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=5e4+5;
std::vector<int> G[maxn];
int dep[maxn],Fa[maxn][20],power[maxn],ans,n,m;
inline void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1;Fa[u][0]=fa;
	for(int i=1;(1<<i)<=dep[u];i++)Fa[u][i]=Fa[Fa[u][i-1]][i-1];
	for(auto &v:G[u]){if(v==fa)continue;dfs(v,u);}
}
inline int lca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if((1<<i)<=dep[x]-dep[y])x=Fa[x][i];
	if(x==y)return x;
    for(int i=19;i>=0;i--)if(Fa[x][i]!=Fa[y][i])x=Fa[x][i],y=Fa[y][i];
    return Fa[x][0];
}
inline void solve(int u,int fa)
{
	for(auto &v:G[u])
	{
		if(v==fa)continue;
		solve(v,u);
		power[u]+=power[v];
	}
	ans=max(ans,power[u]);
}
inline int dis(int x,int y){return dep[x]+dep[y]-dep[lca(x,y)];}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(1,0);
	while(m--)
	{
		int x,y;scanf("%d%d",&x,&y);
		power[x]++;power[y]++;power[lca(x,y)]--;power[Fa[lca(x,y)][0]]--;
	}
	solve(1,0);
	printf("%d\n", ans);
	return 0;
}