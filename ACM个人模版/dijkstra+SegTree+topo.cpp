//  给定一个DAG图，同时给定起点S和终点T，
// 每次询问删掉某个点和所有与它相连的边之后S到T的最短路，询问之间互相独立
// 不存在输出-1
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii pair<int,int>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=2e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;
int n,m,s,t;
std::vector<pii>G1[maxn],G2[maxn];
ll dis1[maxn],dis2[maxn];int du[maxn],a[maxn],cnt;
struct SegTree
{
	ll sum[maxn];
	inline void build(int o,int l,int r)
	{
		sum[o]=inf;
		if(l==r) return ;
		int m=(l+r)>>1;
		build(o<<1,l,m);build(o<<1|1,m+1,r);
	}
	inline void update(int o,int l,int r,int ql,int qr,ll val)
	{
		if(l==r){sum[o]=min(sum[o],val);return;}
		int m=(l+r)>>1;
		if(ql<=m) update(o<<1,l,m,ql,qr,val);
		if(qr>m)  update(o<<1|1,m+1,r,ql,qr,val);
		sum[o]=min(sum[o<<1],sum[o<<1|1]);
	}
    inline ll query(int o,int l,int r,int x)
    {
    	if(l==r)return sum[o];
    	int m=(l+r)>>1;
    	ll ans=inf;
    	if(x<=m) ans=min(ans,query(o<<1,l,m,x));
    	else  ans=min(ans,query(o<<1|1,m+1,r,x));
    	return ans;
    }
}st;
struct node
{
    ll dis;int pos;
    bool operator <(const node &x)const
    {
        return x.dis<dis;
    }
};
inline void dijkstra(int s,std::vector<pii>G[maxn],ll *dis)
{
	priority_queue<node>q;int vis[maxn];
    for(int i=0;i<=n+10;++i)dis[i]=inf,vis[i]=0;
    dis[s]=0;
    q.push((node){0,s});
    while(!q.empty())
    {
        node tmp=q.top();
        q.pop();
        int x=tmp.pos,d=tmp.dis;
        if(vis[x])continue;
        vis[x]=1;
        for(auto &it:G[x])
        {
        	int y,w;tie(y,w)=it;
            if(dis[y]>dis[x]+w)
            {
                dis[y]=dis[x]+w;
                if(!vis[y])q.push((node){dis[y],y} );
            }
        }
    }
}
inline void topo()
{
	queue<int>q;
	for(int i=1;i<=n;i++)if(!du[i])q.emplace(i);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		a[u]=++cnt;
		for(auto &it:G1[u])
		{
			du[it.first]--;
			if(!du[it.first])q.emplace(it.first);
		}
	}
}
int main()
{
#ifdef LOCAL
	freopen("input.txt","r",stdin);
#endif
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		du[v]++;
		G1[u].emplace_back(v,w);
		G2[v].emplace_back(u,w);
	}
	dijkstra(s,G1,dis1);dijkstra(t,G2,dis2);
	topo();
	st.build(1,1,n);
	for(int u=1;u<=n;u++)
		for(auto &it:G1[u])
		{
			int v,w;tie(v,w)=it;
			if(a[u]+1<a[v]&&dis1[u]!=inf&&dis2[v]!=inf)
				st.update(1,1,n,a[u]+1,a[v]-1,dis1[u]+dis2[v]+w);
		}
	scanf("%d",&m);
	while(m--)
	{
		int x;scanf("%d",&x);
		if(dis1[x]==inf||dis2[x]==inf){printf("%lld\n",dis1[t]);continue;}
		ll ans=st.query(1,1,n,a[x]);
		printf("%lld\n",ans==inf?-1:ans);
	}
	return 0;
}