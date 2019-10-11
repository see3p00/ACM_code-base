// kruskal重构树
// 给你 n 个点 m 条边的无向图，每条边的长度为 di。
// 现在有 k 个询问 每次询问 u,v 之间的所有路径中，最长边的最小值是多少？ 
#pragma GCC optimize(3, "Ofast", "inline")
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii std::pair<int,int>
#define pll std::pair<ll,ll>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1e5+5;
int dep[maxn],Fa[maxn][16],fa[maxn],val[maxn],n,m,q;
std::vector<int> G[maxn];
struct edge
{
	int u,v,w;
	bool operator<(const edge&oth)const
	{
		return w<oth.w;
	}
}e[maxn];
int find(int x){return fa[x]==x?fa[x]:fa[x]=find(fa[x]);}
void kruskal()
{
	sort(e+1,e+m+1);
	int lim=n+n;
	for(int i=1;i<=lim;i++)fa[i]=i;
	for(int idx=n,i=1;i<=m;i++)
	{
		int x=find(e[i].u),y=find(e[i].v);
		if(x==y)continue;
		fa[x]=fa[y]=++idx;val[idx]=e[i].w;
		G[idx].emplace_back(x);
		G[idx].emplace_back(y);
		if(idx==lim-1)break;
	}
}
void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1;
	Fa[u][0]=fa;
	for(int i=1;(1<<i)<=dep[u];i++)Fa[u][i]=Fa[Fa[u][i-1]][i-1];
	for(auto &v:G[u])
	{
		if(v==fa)continue;
		dfs(v,u);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i=15;i>=0;i--)if((1<<i)<=dep[x]-dep[y])x=Fa[x][i];
	if(x==y)swap(x,y);
	for(int i=15;i>=0;i--)if(Fa[x][i]!=Fa[y][i])x=Fa[x][i],y=Fa[y][i];
	return Fa[x][0];
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++)scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	kruskal();
	dfs(2*n-1,0);
	while(q--)
	{
		int x,y;scanf("%d%d",&x,&y);
		printf("%d\n",val[lca(x,y)]);
	}
    return 0;
}

// kruskal重构树
//  带权图，多组询问与一个点通过边权<=x的边连通的点中点权k大值
#pragma GCC optimize(3, "Ofast", "inline")
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii std::pair<int,int>
#define pll std::pair<ll,ll>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=5e5+5;
std::vector<int> V,G[maxn];
int getid(int x){return lower_bound(ALL(V),x)-V.begin();}
int root[maxn],fa[maxn],Fa[maxn][21],dep[maxn],val[maxn],cnt,last,tot,in[maxn],out[maxn],sz,n,m,q;
struct edge
{
    int u,v,w;
    bool operator<(const edge&oth)const
    {
        return w<oth.w;
    }
}e[maxn];
struct node{int l,r,sum;}T[maxn*40];
void update(int l,int r,int &x,int y,int pos)
{
    T[++cnt]=T[y];T[cnt].sum++;x=cnt;
    if(l==r)return ;
    int m=(l+r)>>1;
    if(m>=pos)update(l,m,T[x].l,T[y].l,pos);
    else update(m+1,r,T[x].r,T[y].r,pos);
}
int query(int l,int r,int x,int y,int k)
{
    if(l==r)return l;
    int m=(l+r)>>1;int sum=T[T[y].r].sum-T[T[x].r].sum;
    if(sum>=k) return query(m+1,r,T[x].r,T[y].r,k);
    else return query(l,m,T[x].l,T[y].l,k-sum);
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void kruskal()
{
    sort(e+1,e+m+1);
    int lim=n+n;
    for(int i=1;i<=lim;i++)fa[i]=i;
    for(int idx=n,i=1;i<=m;i++)
    {
        int x=find(e[i].u),y=find(e[i].v);
        if(x==y)continue;
        fa[x]=fa[y]=++idx;val[idx]=e[i].w;
        G[idx].emplace_back(x);
        G[idx].emplace_back(y);
        if(idx==lim-1)break;
    }
}
void dfs(int u,int fa)
{
    in[u]=++tot;
    dep[u]=dep[fa]+1;
    Fa[u][0]=fa;
    for(int i=1;(1<<i)<=dep[u];i++)Fa[u][i]=Fa[Fa[u][i-1]][i-1];
    if(u<=n) update(1,sz,root[in[u]],root[in[u]-1],val[u]);
    else root[tot]=root[tot-1];
    for(auto &v:G[u])
    {
        if(v==fa)continue;
        dfs(v,u);
    }
    out[u]=tot;
}
void pos(int &v,int lim)
{
    for(int i=17;~i;i--)
    {
        if(dep[v]<(1<<i))continue;
        if(val[Fa[v][i]]<=lim)v=Fa[v][i];
    }
    return;
}
int main()
{
#ifdef LOCAL
    freopen("input.txt","r",stdin);
#endif
    scanf("%d%d%d",&n,&m,&q);V.emplace_back(-0x3f3f3f3f);val[0]=0x3f3f3f3f;
    for(int i=1;i<=n;i++)scanf("%d",&val[i]),V.emplace_back(val[i]);
    sort(ALL(V)),V.erase(unique(ALL(V)),V.end()); sz=SZ(V);
    for(int i=1;i<=n;i++)val[i]=getid(val[i]);
    for(int i=1;i<=m;i++)scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    kruskal();
    for(int i=1;i<=n;i++)if(!in[i])dfs(find(i),fa[find(i)]);
    while(q--)
    {
        int v,x,k;scanf("%d%d%d",&v,&x,&k);
        pos(v,x);
        int l=in[v]-1,r=out[v];
        if(T[root[r]].sum-T[root[l]].sum<k)last=-1;
        else last=V[query(1,sz,root[l],root[r],k)];
        printf("%d\n",last);
    }
    return 0;
}
