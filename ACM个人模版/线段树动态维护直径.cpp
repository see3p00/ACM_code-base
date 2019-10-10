// 带权树，修改边权，维护直径
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
typedef long long ll;
typedef unsigned long long ull;
const int maxn =1e5+7;
struct edge
{
	int u,v,w;
}e[maxn];
std::vector<pair<int,int>>G[maxn];
int in[maxn],out[maxn],rid[maxn],tot,n,q;
namespace HLD
{
	struct BIT
	{
		ll c[maxn];
		inline int lowbit(int x){return x&-x;}
		inline void update(int i,int val)
		{
			while(i<=n)
			{
				c[i]+=val;
				i+=lowbit(i);
			}
		}
		inline void update(int l,int r,int val)
		{
			update(l,val);update(r+1,-val);
		}
		inline ll query(int i)
		{
			ll res=0;
			while(i)
			{
				res+=c[i];
				i-=lowbit(i);
			}
			return res;
		}
	}bit;
	int sz[maxn],dep[maxn],fa[maxn],son[maxn],top[maxn];
	inline void dfs1(int u,int f)
	{
		in[u]=++tot;rid[tot]=u;
		dep[u]=dep[f]+1;fa[u]=f;sz[u]=1;son[u]=0;
		int m=-1;
		for(auto &it:G[u])
		{
			int v,w;tie(v,w)=it;
			if(v==f)continue;
			dfs1(v,u);
			bit.update(in[v],out[v],w);
			sz[u]+=sz[v];
			if(sz[v]>m)son[u]=v,m=sz[v];
		}
		out[u]=tot;
	}
	inline void dfs2(int u,int f,int t)
	{
		top[u]=t;
		if(!son[u])return;
		dfs2(son[u],u,t);
		for(auto &it:G[u])
		{
			int v,w;tie(v,w)=it;
			if(v==f||v==son[u])continue;
			dfs2(v,u,v);
		}
	}
	inline void build(){dfs1(1,0);dfs2(1,0,1);}
	inline int lca(int u,int v)
	{
		while(top[u]!=top[v])
		{
			if(dep[top[u]]<dep[top[v]])swap(u,v);
			u=fa[top[u]];
		}
		return dep[u]<dep[v]?u:v;
	}
	inline ll dist(int u,int v)
	{
		return bit.query(in[u])+bit.query(in[v])-2ll*bit.query(in[lca(u,v)]);
	}
};
using HLD::dist;
struct node
{
	int u,v;ll w;
}a[maxn<<2];
inline void pushup(int o)
{
	if(a[o<<1].w>a[o<<1|1].w)a[o]=a[o<<1];
	else a[o]=a[o<<1|1];
	int x=a[o<<1].u,y=a[o<<1].v;
	int u=a[o<<1|1].u,v=a[o<<1|1].v;
	ll dis;
    if ((dis=dist(x,u))>a[o].w)a[o]={x,u,dis};
    if ((dis=dist(x,v))>a[o].w)a[o]={x,v,dis};
    if ((dis=dist(y,u))>a[o].w)a[o]={y,u,dis};
    if ((dis=dist(y,v))>a[o].w)a[o]={y,v,dis};
}
inline void build(int o,int l,int r)
{
	if(l==r)
	{
		a[o]={rid[l],rid[l],0};
		return ;
	}
	int m=(l+r)>>1;
	build(o<<1,l,m);build(o<<1|1,m+1,r);
	pushup(o);
}
inline void update(int o,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr)return ;
	int m=(l+r)>>1;
	if(ql<=m) update(o<<1,l,m,ql,qr);
	if(qr>m) update(o<<1|1,m+1,r,ql,qr);
	pushup(o);
}
int main()
{
#ifdef LOCAL
	freopen("input.txt","r",stdin);
#endif
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
		G[e[i].u].emplace_back(e[i].v,e[i].w);
		G[e[i].v].emplace_back(e[i].u,e[i].w);
	}
	HLD::build();build(1,1,n);
	scanf("%d",&q);char op[5];
	while(q--)
	{
		scanf("%s",op);
		if(op[0]=='C')
		{
			int x,y;scanf("%d%d",&x,&y);
			int u=e[x].u,v=e[x].v,w=e[x].w;
			if(HLD::fa[v]!=u) swap(u,v);
			HLD::bit.update(in[v],out[v],y-w);
			e[x].w=y;
			update(1,1,n,in[v],out[v]);
		}
		else
		{
			int x;scanf("%d",&x);
			printf("%lld\n",1ll*max(dist(x,a[1].u),dist(x,a[1].v)));
		}
	}
	return 0;
}
//////////////////////////////
struct node
{
    int fi,se;
}a[maxn<<2];
node Max(node a,node b)
{
    int t[4]={a.fi,a.se,b.fi,b.se},mx=0;
    node ret;
    for(int i=0;i<4;i++)
        for(int j=i+1;j<4;j++)
            if(dist(t[i],t[j])>mx)
                mx=dist(t[i],t[j]),ret.fi=t[i],ret.se=t[j];
    return ret;
}
void build(int o,int l,int r)
{
    if(l==r) return (void)(a[o]=(node){l,l});
    int m=(l+r)>>1;
    build(o<<1,l,m);build(o<<1|1,m+1,r);
    a[o]=Max(a[o<<1],a[o<<1|1]);
}
node query(int o,int l,int r,int ql,int qr)
{
    if(ql<=l&&qr>=r) return a[o];
    int m=(l+r)>>1;
    if(qr<=m) return query(o<<1,l,m,ql,qr);
    if(ql>m) return query(o<<1|1,m+1,r,ql,qr);
    return Max(query(o<<1,l,m,ql,qr),query(o<<1|1,m+1,r,ql,qr));
}
