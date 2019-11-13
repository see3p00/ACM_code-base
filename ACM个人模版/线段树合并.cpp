//并查集+线段树启发式合并
//n个独立点有各不相同的权值
//开始合并m次，每次合并两个点所在集合
//两种操作
//Q x y 询问x所在集合的权值第y大的点的编号，不存在输出-1
//B x y 合并x、y的所在集合
#include<bits/stdc++.h>

const int maxn = 1e5 + 10 ;

int fa[maxn],root[maxn],a[maxn],id[maxn],n,m,q,tot;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
struct SegTree
{
    int sum[maxn*40],ls[maxn*40],rs[maxn*40];
    void update(int &o,int l,int r,int val)
    {
        if(!o)o=++tot;
        if(l==r)
        {
            sum[o]=1;return;
        }
        int m=(l+r)>>1;
        if(val<=m) update(ls[o],l,m,val);
        else update(rs[o],m+1,r,val);
        sum[o]=sum[ls[o]]+sum[rs[o]];
    }
    int query(int o,int l,int r,int pos)
    {
        if(l==r)return l;
        int m=(l+r)>>1;
        if(sum[ls[o]]>=pos) return query(ls[o],l,m,pos);
        else return query(rs[o],m+1,r,pos-sum[ls[o]]);
    }
    int merge(int x,int y)
    {
        if(!x)return y;
        if(!y)return x;
        ls[x]=merge(ls[x],ls[y]);
        rs[x]=merge(rs[x],rs[y]);
        sum[x]=sum[ls[x]]+sum[rs[x]];
        return x;
    }
}st;
char op[5];
int main()
{
#ifdef LOCAL
    freopen("input.txt","r",stdin);
#endif
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        int x,y;scanf("%d%d",&x,&y);
        fa[find(x)]=find(y);
    }
    for(int i=1;i<=n;i++)
    {
        st.update(root[find(i)],1,n,a[i]);
        id[a[i]]=i;
    }
    scanf("%d",&q);
    while(q--)
    {
        scanf("%s",op);
        int x,y;scanf("%d%d",&x,&y);
        if(op[0]=='Q')
        {
            if(st.sum[root[find(x)]]<y){puts("-1");continue;}
            printf("%d\n",id[st.query(root[find(x)],1,n,y)]);
        }
        else
        {
            x=find(x),y=find(y);
            if(x!=y)
            {
                fa[x]=y;
                root[y]=st.merge(root[x],root[y]);
            }
        }
    }
    return 0;
}
