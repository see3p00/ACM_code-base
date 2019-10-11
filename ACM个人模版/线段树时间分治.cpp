//线段树时间分治——可撤销并查集
//给你一个图，每条边有一个l-r的属性，在l-r之间的属性才可以通过
//问你有多少个属性可以从1走到n
#include<bits/stdc++.h>
using namespace std;
const int maxn=8e5+5;
vector<int>e[maxn];
int sz[maxn],a[maxn],l[maxn],r[maxn],u[maxn],v[maxn],fa[maxn],ans,cnt,n,m;
int find(int x){return x==fa[x]?fa[x]:find(fa[x]);}
void up(int o,int l,int r,int ql,int qr,int x)
{
    if(l==ql&&r==qr)return (void)e[o].push_back(x);
    int mid=(l+r)>>1;
    if(qr<=mid)up(o<<1,l,mid,ql,qr,x);
    else if(ql>mid)up(o<<1|1,mid+1,r,ql,qr,x);
    else up(o<<1,l,mid,ql,mid,x),up(o<<1|1,mid+1,r,mid+1,qr,x);
}
void dfs(int o,int l,int r)
{
    vector<int>la;int m=e[o].size(),mid=(l+r)>>1;
    for(int i=0;i<m;i++)
    {
        int x=u[e[o][i]],y=v[e[o][i]];
        x=find(x),y=find(y);if(sz[x]>sz[y])swap(x,y);  //启发式合并
        la.push_back(x);fa[x]=y;sz[y]+=sz[x];
    }
    if(find(1)==find(n))ans+=a[r+1]-a[l];
    else if(l<r)dfs(o<<1,l,mid),dfs(o<<1|1,mid+1,r);m=la.size();
    for(int i=m-1;i>=0;i--)fa[la[i]]=la[i];la.clear();
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
    for(int i=1;i<=m;i++)scanf("%d%d%d%d",&u[i],&v[i],&l[i],&r[i]),a[++cnt]=l[i],a[++cnt]=r[i]+1;
    sort(a+1,a+1+cnt);cnt=unique(a+1,a+1+cnt)-a-1;
    for(int i=1;i<=m;i++)up(1,1,cnt-1,lower_bound(a+1,a+cnt+1,l[i])-a,lower_bound(a+1,a+cnt+1,r[i]+1)-a-1,i);
    dfs(1,1,cnt-1);printf("%d\n",ans);
    return 0;
}