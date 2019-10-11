//  一棵具有N个节点的树
//  求从节点u到节点v的路径上的第k个最小权重
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii pair<int,int>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=2e5+10;
int dep[maxn],Fa[maxn][21],f[maxn],root[maxn],w[maxn],cnt,n,m,sz;
vector<int>G[maxn],v;
struct node{int l,r,sum;}T[maxn*50];
inline int getid(int x){return lower_bound(v.begin(),v.end(),x)-v.begin();}
inline void update(int l,int r,int &x,int y,int pos)
{
	T[++cnt]=T[y];T[cnt].sum++;x=cnt;
	if(l==r)return ;
	int m=(l+r)>>1;
	if(m>=pos) update(l,m,T[x].l,T[y].l,pos);
	else update(m+1,r,T[x].r,T[y].r,pos);
}
inline int query(int l,int r,int x,int y,int xx,int yy,int k)
{
	if(l==r)return l;
	int m=(l+r)>>1;int sum=T[T[y].l].sum+T[T[x].l].sum-T[T[xx].l].sum-T[T[yy].l].sum;
	if(sum>=k)return query(l,m,T[x].l,T[y].l,T[xx].l,T[yy].l,k);
	else return query(m+1,r,T[x].r,T[y].r,T[xx].r,T[yy].r,k-sum);
}
inline void dfs(int u,int fa) {
    dep[u]=dep[fa]+1;
    Fa[u][0]=fa;
    f[u]=fa;
    update(1,sz,root[u],root[fa],getid(w[u]));
    for(int i=1;(1<<i)<=dep[u];i++) Fa[u][i]=Fa[Fa[u][i-1]][i-1];
    for(auto &v:G[u])  {
        if(v==fa) continue;
        dfs(v,u);
    }
}
inline int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--) if((1<<i)<=dep[x]-dep[y]) x=Fa[x][i];
    if(x==y) return x;
    for(int i=20;i>=0;i--) if(Fa[x][i]!=Fa[y][i]) x=Fa[x][i],y=Fa[y][i];
    return Fa[x][0];
}
int main()
{
#ifdef LOCAL
	freopen("input.txt","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&w[i]),v.emplace_back(w[i]);
	v.emplace_back(-0x3f3f3f3f);
	sort(ALL(v));v.resize(distance(v.begin(),unique(ALL(v))));
    sz=SZ(v);
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(1,0);
	while(m--)
	{
		int x,y,k;scanf("%d%d%d",&x,&y,&k);
		printf("%d\n",v[query(1,sz,root[x],root[y],root[lca(x,y)],root[f[lca(x,y)]],k)]);
	}
	return 0;
}