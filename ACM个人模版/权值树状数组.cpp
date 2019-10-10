// 权值树状数组 +二分。   查询第k大
inline int lowbit(int x){return x&-x;}
inline void update(int i,int val){while(i<=maxn){c[i]+=val;i+=lowbit(i);}}
inline int query(int i){int res=0;while(i){res+=c[i];i-=lowbit(i);}return res;}
inline int solve(int a,int k)  //二分 
{
	int tmp=query(a)+k;int ans;
	int l=1,r=maxn-1;
	while(l<=r)
	{
		int m=(l+r)>>1;
		if(query(m)>=tmp) ans=m,r=m-1;
		else l=m+1;
	}
	return ans;
}
int find_kth(int k)  
{
	int ans=0,sum=0,i;
	for(int i=20;i>=0;i--)
	{
		ans+=(1<<i);
		if(ans>=maxn||sum+c[ans]>=k)
			ans-=(1<<i);
		else
			sum+=c[ans];
	}
	return ans+1;
}