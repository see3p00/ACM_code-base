// 倍增 LCA

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int dep[maxn],Fa[maxn][22],n,q;
vector<int>G[maxn];
void dfs(int u,int fa) {
    dep[u]=dep[fa]+1;
    Fa[u][0]=fa;
    for(int i=1;(1<<i)<=dep[u];i++) Fa[u][i]=Fa[Fa[u][i-1]][i-1];
    for(auto &v:G[u])  {
        if(v==fa) continue;
        dfs(v,u);
    }
}
int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--) if((1<<i)<=dep[x]-dep[y]) x=Fa[x][i];
    if(x==y) return x;
    for(int i=20;i>=0;i--) if(Fa[x][i]!=Fa[y][i]) x=Fa[x][i],y=Fa[y][i];
    return Fa[x][0];
}
int dis(int x,int y) { return dep[x]+dep[y]-2*dep[lca(x,y)]; }
int main(int argc, char const *argv[])
{
	scanf("%d",&n);
	for(int i=0;i<n-1;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(1,0);
	scanf("%d",&q);
	while(q--)
	{
		int a,b;scanf("%d%d",&a,&b);
		cout<<lca(a,b)<<endl;
	}
	return 0;
}
