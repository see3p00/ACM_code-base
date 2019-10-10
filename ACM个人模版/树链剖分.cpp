//单点更新，区间求和，区间最值
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=60000+5;
const int inf=2e9;
char op[10];
int head[maxn],w[maxn],siz[maxn],top[maxn],son[maxn],dep[maxn],fa[maxn],tid[maxn],rnk[maxn],tot,cnt,n,q;
struct edge{int to,next;}e[maxn];
inline void addedge(int u,int v)
{
    cnt++;e[cnt].next=head[u];head[u]=cnt;e[cnt].to=v;
}
struct segment
{
    int sum[maxn<<2],maxx[maxn<<2];
    inline void build(int o,int l,int r)
    {
        if(l==r){sum[o]=maxx[o]=w[rnk[l]];return ;}
        int m=(l+r)>>1;
        build(o<<1,l,m);build(o<<1|1,m+1,r);
        sum[o]=sum[o<<1]+sum[o<<1|1];
        maxx[o]=max(maxx[o<<1],maxx[o<<1|1]);
    }
    inline int query1(int o,int l,int r,int ql,int qr)// max
    {
        if(l>qr||r<ql) return -inf;
        if(ql<=l&&r<=qr) return maxx[o];
        int m=(l+r)>>1;
        return max(query1(o<<1,l,m,ql,qr),query1(o<<1|1,m+1,r,ql,qr));
    }
    inline int query2(int o,int l,int r,int ql,int qr)// sum
    {
        if(l>qr||r<ql) return 0;
        if(ql<=l&&r<=qr)return sum[o];
        int m=(l+r)>>1;
        return query2(o<<1,l,m,ql,qr)+query2(o<<1|1,m+1,r,ql,qr);
    }
    inline void update(int o,int l,int r,int x,int t)
    {
        if(l==r){maxx[o]=sum[o]=t;return ;}
        int m=(l+r)>>1;
        if(x<=m)update(o<<1,l,m,x,t);
        else update(o<<1|1,m+1,r,x,t);
        sum[o]=sum[o<<1]+sum[o<<1|1];
        maxx[o]=max(maxx[o<<1],maxx[o<<1|1]);
    }
}st;
inline void dfs1(int u,int fat)
{
    son[u]=-1;siz[u]=1;
    for(int i=head[u];i;i=e[i].next)
    {
        if(!dep[e[i].to])
        {
            dep[e[i].to]=dep[u]+1;
            fa[e[i].to]=u;dfs1(e[i].to,u);
            siz[u]+=siz[e[i].to];
            if(son[u]==-1||siz[e[i].to]>siz[son[u]])son[u]=e[i].to;
        }
    }
}
inline void dfs2(int u,int t)
{
    top[u]=t;tot++;
    tid[u]=tot;rnk[tot]=u;
    if(son[u]==-1)return;
    dfs2(son[u],t);
    for(int i=head[u];i;i=e[i].next)
        if(e[i].to!=son[u]&&e[i].to!=fa[u])dfs2(e[i].to,e[i].to);
}
inline int querymax(int x,int y)
{
    int res=-inf,fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(dep[fx]>=dep[fy]) res=max(res,st.query1(1,1,n,tid[fx],tid[x])),x=fa[fx];
        else res=max(res,st.query1(1,1,n,tid[fy],tid[y])),y=fa[fy];
        fx=top[x];fy=top[y];
    }
    if(x!=y)
    {
        if(tid[x]<tid[y])res=max(res,st.query1(1,1,n,tid[x],tid[y]));
        else res=max(res,st.query1(1,1,n,tid[y],tid[x]));
    } else res=max(res,st.query1(1,1,n,tid[x],tid[y]));
    return res;
}
inline int querysum(int x,int y)
{
    int res=0,fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(dep[fx]>=dep[fy])res+=st.query2(1,1,n,tid[fx],tid[x]),x=fa[fx];
        else res+=st.query2(1,1,n,tid[fy],tid[y]),y=fa[fy];
        fx=top[x];fy=top[y];
    }
    if(x!=y)
    {
        if(tid[x]<tid[y]) res+=st.query2(1,1,n,tid[x],tid[y]);
        else res+=st.query2(1,1,n,tid[y],tid[x]);
    } else res+=st.query2(1,1,n,tid[x],tid[y]);
    return res;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;scanf("%d%d",&u,&v); addedge(u,v);addedge(v,u);
    }
    for(int i=1;i<=n;i++)scanf("%d",&w[i]);
    dep[1]=1;dfs1(1,-1);dfs2(1,1);st.build(1,1,n);
    scanf("%d",&q);
    while(q--)
    {
        int u,v;scanf("%s%d%d",op,&u,&v);
        if(op[0]=='C')st.update(1,1,n,tid[u],v);
        if(op[0]=='Q'&&op[1]=='M')printf("%d\n",querymax(u,v));
        if(op[0]=='Q'&&op[1]=='S')printf("%d\n",querysum(u,v));
    }
    return 0;
}

//树上操作  单点更新 子树更新 到根求和
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=2e5+5;
const int inf=2e9;
int head[maxn],w[maxn],siz[maxn],mx[maxn],top[maxn],son[maxn],dep[maxn],fa[maxn],tid[maxn],rnk[maxn],tot,cnt,n,q;
struct edge{int to,next;}e[maxn];
inline void addedge(int u,int v)
{
    cnt++;e[cnt].next=head[u];head[u]=cnt;e[cnt].to=v;
}
struct segment
{
    ll sum[maxn<<2],add[maxn<<2];
    inline void pushdown(int o,int m)
    {
        if(add[o])
        {
            add[o<<1]+=add[o];add[o<<1|1]+=add[o];
            sum[o<<1]+=add[o]*(m-(m>>1));
            sum[o<<1|1]+=add[o]*(m>>1);
            add[o]=0;
        }
    }
    inline void build(int o,int l,int r)
    {
        add[o]=0;
        if(l==r){sum[o]=w[rnk[l]];return ;}
        int m=(l+r)>>1;
        build(o<<1,l,m);build(o<<1|1,m+1,r);
        sum[o]=sum[o<<1]+sum[o<<1|1];
    }
    inline ll query2(int o,int l,int r,int ql,int qr)// sum
    {
        if(l>qr||r<ql) return 0;
        if(ql<=l&&r<=qr)return sum[o];
        pushdown(o,r-l+1);
        int m=(l+r)>>1;ll res=0;
        if(ql<=m)res+=query2(o<<1,l,m,ql,qr);
        if(m<qr)res+=query2(o<<1|1,m+1,r,ql,qr);
        return res;
    }
    inline void update(int o,int l,int r,int ql,int qr,ll c)
    {
        if(ql<=l&&r<=qr){add[o]+=c;sum[o]+=1LL*c*(r-l+1);return;}
        pushdown(o,r-l+1);
        int m=(l+r)>>1;
        if(ql<=m)update(o<<1,l,m,ql,qr,c);
        if(m<qr) update(o<<1|1,m+1,r,ql,qr,c);
        sum[o]=sum[o<<1]+sum[o<<1|1];
    }
}st;
inline void dfs1(int u,int fat)
{
    son[u]=-1;siz[u]=1;
    for(int i=head[u];i;i=e[i].next)
    {
        if(!dep[e[i].to])
        {
            dep[e[i].to]=dep[u]+1;
            fa[e[i].to]=u;dfs1(e[i].to,u);
            siz[u]+=siz[e[i].to];
            if(son[u]==-1||siz[e[i].to]>siz[son[u]])son[u]=e[i].to;
        }
    }
}
inline void dfs2(int u,int t)
{
    top[u]=t;tot++;
    tid[u]=mx[u]=tot;rnk[tot]=u;
    if(son[u]==-1)return;
    dfs2(son[u],t);mx[u]=max(mx[u],mx[son[u]]);
    for(int i=head[u];i;i=e[i].next)
        if(e[i].to!=son[u]&&e[i].to!=fa[u])dfs2(e[i].to,e[i].to),mx[u]=max(mx[u],mx[e[i].to]);
}
inline ll querysum(int x,int y)
{
    ll res=0,fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(dep[fx]>=dep[fy])res+=st.query2(1,1,n,tid[fx],tid[x]),x=fa[fx];
        else res+=st.query2(1,1,n,tid[fy],tid[y]),y=fa[fy];
        fx=top[x];fy=top[y];
    }
    if(x!=y)
    {
        if(tid[x]<tid[y]) res+=st.query2(1,1,n,tid[x],tid[y]);
        else res+=st.query2(1,1,n,tid[y],tid[x]);
    } else res+=st.query2(1,1,n,tid[x],tid[y]);
    return res;
}
int main()
{
    scanf("%d%d",&n,&q);for(int i=1;i<=n;i++)scanf("%d",&w[i]);
    for(int i=1;i<n;i++)
    {
        int u,v;scanf("%d%d",&u,&v); addedge(u,v);addedge(v,u);
    }
    dep[1]=1;dfs1(1,-1);dfs2(1,1);st.build(1,1,n);
    while(q--)
    {
        int op;scanf("%d",&op);
        if(op==1){int x;ll a;scanf("%d%lld",&x,&a);st.update(1,1,n,tid[x],tid[x],a);}
        if(op==2){int x;ll a;scanf("%d%lld",&x,&a);st.update(1,1,n,tid[x],mx[x],a);}
        if(op==3){int x;scanf("%d",&x);printf("%lld\n",querysum(1,x));}
    }
    return 0;
}
