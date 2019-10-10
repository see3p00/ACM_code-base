//  Author wzazzy ^_^
//  keep a good mental state and stick to it
//  The devil is in the details
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define ls(x) (x<<1)
#define rs(x) (ls(x)|1)
const int maxn=1e6+5;
struct seg
{
    int l,r;
    int op;
    int cl;
    bool rev;
    int mid(){return (l+r)>>1;}
    int len(){return r-l+1;}
}t[maxn<<2];
int n,m;
void pushup(int o)
{
    t[o].op=t[ls(o)].op+t[rs(o)].op;
    t[o].cl=t[ls(o)].cl+t[rs(o)].cl;
}
void build(int l=1,int r=n,int o=1)
{
    t[o].l=l;t[o].r=r;
    t[o].op=0;
    if(l==r)
    {
        t[o].cl=1;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,ls(o));
    build(mid+1,r,rs(o));
    pushup(o);
}
void pushdown(int o)
{
    if(t[o].rev)
    {
        for(int i=0;i<=1;++i)
        {
            t[ls(o)|i].rev^=1;
            swap(t[ls(o)|i].op,t[ls(o)|i].cl);
        }
        t[o].rev=0;
    }
}
void update(int l,int r,int o=1)
{
    if(l<=t[o].l&&t[o].r<=r)
    {
        t[o].rev^=1;
        swap(t[o].op,t[o].cl);
        return;
    }
    int m=t[o].mid();
    pushdown(o);
    if(l<=m)update(l,r,ls(o));
    if(r>m)update(l,r,rs(o));
    pushup(o);
}
int query(int l,int r,int o=1)
{
    if(l<=t[o].l&&t[o].r<=r)
        return t[o].op;
    int ans=0;
    int m=t[o].mid();
    pushdown(o);
    if(l<=m)ans+=query(l,r,ls(o));
    if(r>m)ans+=query(l,r,rs(o));
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("input.txt","r",stdin);
#endif
    int t;scanf("%d",&t);
    int cnt=1;
    while(t--)
    {
    	scanf("%d%d",&n,&m);
    	build();
    	while(m--)
    	{
    		int x,y;scanf("%d%d",&x,&y);
    		update(x,y);
    	}
    	printf("Case #%d: %d\n",cnt++,query(1,n));
    }
    return 0;
}
