//给定n个点，以1号节点为根的树 有点权。
//m次询问 以x为根的子树内点权第k小的节点编号是多少。
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii pair<int,int>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1e5+10;
std::vector<int>G[maxn],v;
int a[maxn],in[maxn],out[maxn],root[maxn],tot,n,m,cnt;
struct node{int l,r,sum;}T[maxn*40];int rk[maxn*40];
inline int getid(int x){return lower_bound(v.begin(),v.end(),x)-v.begin();}
inline void update(int l,int r,int &x,int y,int pos,int id)
{
	T[++cnt]=T[y];T[cnt].sum++;x=cnt;
	if(l==r){rk[x]=id;return ;}
	int m=(l+r)>>1;
	if(m>=pos)update(l,m,T[x].l,T[y].l,pos,id);
	else update(m+1,r,T[x].r,T[y].r,pos,id);
}
inline int query(int l,int r,int x,int y,int k)
{
	if(l==r)return rk[y];
	int m=(l+r)>>1;int sum=T[T[y].l].sum-T[T[x].l].sum;
	if(sum>=k) return query(l,m,T[x].l,T[y].l,k);
	else return query(m+1,r,T[x].r,T[y].r,k-sum);
}
inline void dfs(int u,int fa)
{
	in[u]=++tot;
	update(0,maxn,root[in[u]],root[in[u]-1],getid(a[u]),u);
	for(auto &v:G[u])
	{
		if(v==fa)continue;
		dfs(v,u);
	}
	out[u]=tot;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),v.emplace_back(a[i]);
	sort(v.begin(),v.end());v.resize(distance(v.begin(),unique(v.begin(),v.end())));
    for(int i=1;i<n;i++)
    {
    	int u,v;scanf("%d%d",&u,&v);
    	G[u].emplace_back(v);
    	G[v].emplace_back(u);
    }
    dfs(1,0);
    scanf("%d",&m);
    while(m--)
    {
    	int x,k;scanf("%d%d",&x,&k);
    	printf("%d\n",query(0,maxn,root[in[x]-1],root[out[x]],k));
    }
	return 0;
}