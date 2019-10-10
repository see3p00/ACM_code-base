#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=3e5+5;
int n,m;
ll d[maxn<<2],lazy[maxn<<2],in[maxn],sum[maxn],num[maxn],a[maxn],b[maxn],x[maxn],y[maxn],maxx,cnt,tot,cal,N=1;
std::vector<tuple<int,int,int,int,int> > q;
void pushup(int p)
{
	d[p]=d[p<<1]+d[p<<1|1];
}
void pushdown(int l,int r,int p)
{
	if(lazy[p])
	{
		int m=(l+r)>>1;
		lazy[p<<1]+=lazy[p];
		lazy[p<<1|1]+=lazy[p];
		d[p<<1]+=lazy[p]*(m-l+1);
		d[p<<1|1]+=lazy[p]*(r-m);
		lazy[p]=0;
	}
}
void build(int l,int r,int p)
{
	if(l==r)return ;
	int m=(l+r)>>1;
	build(l,m,p<<1);build(m+1,r,p<<1|1);
	pushup(p);
}
void update(int l,int r,int ql,int qr,int p)
{
	if(ql<=l&&r<=qr)
	{
		d[p]+=r-l+1;
		lazy[p]++;
		return ;
	}
	pushdown(l,r,p);
	int m=(l+r)>>1;
	if(ql<=m)update(l,m,ql,qr,p<<1);
	if(qr>m)update(m+1,r,ql,qr,p<<1|1);
	pushup(p);
}
int query(int l,int r,int pos,int p)
{
	if(l==r)return d[p];
	pushdown(l,r,p);
	int m=(l+r)>>1;
	if(pos<=m)return query(l,m,pos,p<<1);
	else return query(m+1,r,pos,p<<1|1);
}
void fwt(ll *a,int opt)
{
	for(int i=1;i<N;i<<=1)
		for(int p=i<<1,j=0;j<N;j+=p)
			for(int k=0;k<i;k++)
				if(opt==1)a[i+j+k]=(a[j+k]+a[i+j+k]);
			    else a[i+j+k]=(a[i+j+k]-a[j+k]);
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		ll x;scanf("%lld",&x);maxx=max(maxx,2*x);a[x]++;
	}
	for(int i=0;i<n;i++)
	{
		ll x;scanf("%lld",&x);maxx=max(maxx,2*x);b[x]++;
	}
	N=1;while(N<maxx)N*=2;
	fwt(a,1);fwt(b,1);
	for(int i=0;i<N;i++)a[i]*=b[i];
	fwt(a,-1);
    for(int i=1;i<=N;++i)
	{
		if(!a[i])continue;
		in[++cal]=i;
		sum[cal]=sum[cal-1]+a[i];
	}
	scanf("%d",&m);q.emplace_back(0,0,0,0,0);
	for(int i=1;i<=m;++i)
	{
		scanf("%lld%lld",&x[i],&y[i]);
		q.emplace_back(x[i],y[i],i,0,0);
		if(!x[i])num[++cnt]=y[i];
		else num[++cnt]=x[i],num[++cnt]=y[i];
	}
	sort(num+1,num+cnt+1);
	int tot=unique(num+1,num+cnt+1)-num;
	for(int i=1;i<=m;++i)
	{
		if(!get<0>(q[i]))get<4>(q[i])=lower_bound(num+1,num+tot+1,get<1>(q[i]))-num;
		else
		{
			get<3>(q[i])=lower_bound(num+1,num+tot+1,get<0>(q[i]))-num;
			get<4>(q[i])=lower_bound(num+1,num+tot+1,get<1>(q[i]))-num;
		}
	}
	for(int i=1;i<=m;++i)
	{
		if(!get<0>(q[i]))
		{
			ll tmp=in[lower_bound(sum,sum+cal,get<1>(q[i]))-sum];
			int ans=query(1,tot,get<4>(q[i]),1);
			if(ans>6){cout<<1<<endl;continue;}
			for(int j=1;j<=ans;j++)tmp=sqrt(tmp);
			printf("%lld\n",tmp);
		}
		else update(1,tot,get<3>(q[i]),get<4>(q[i]),1);
	}
	return 0;
}

/*
5
6 2 6 4 5
1 7 9 10 3
5
17 21
0 8
8 13
0 8 
0 20

7
2
3

*/