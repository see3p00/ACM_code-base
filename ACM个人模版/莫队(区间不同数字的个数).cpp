//  给你n个数，多次询问给定区间不同数字的个数
//  莫队
#pragma GCC optimize(3, "Ofast", "inline")
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii std::pair<int,int>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1e6+5;
inline void read(int &X)
{
    X=0;int w=0;char ch=0;
    while(!isdigit(ch))w|=ch=='-',ch=getchar();
    while( isdigit(ch))X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    X=w?-X:X;
}
int num[maxn],ans[maxn],a[maxn],sum,n,m,r,l=1,block;
struct node
{
	int l,r,id;
	bool operator<(const node &b)const
	{
		return (l/block)^(b.l/block)?l<b.l:(l/block)&1?r<b.r:r>b.r;
	}
}q[maxn];
inline void add(int x)
{
	num[x]++;if(num[x]==1)sum++;
}
inline void del(int x)
{
	num[x]--;if(num[x]==0)sum--;
}
int main()
{
#ifdef LOCAL
	freopen("input.txt","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	read(m);
    block=n/sqrt(m*2/3);
    for(int i=1;i<=m;i++)read(q[i].l),read(q[i].r),q[i].id=i;
    sort(q+1,q+1+m);
    for(int i=1;i<=m;i++)
    {
    	while(r<q[i].r)add(a[++r]);
    	while(r>q[i].r)del(a[r--]);
    	while(l<q[i].l)del(a[l++]);
    	while(l>q[i].l)add(a[--l]);
    	ans[q[i].id]=sum;
    }
    for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
    return 0;
}
