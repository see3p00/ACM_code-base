#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
const int inf=0x3f3f3f3f;
int n;ll ans;
struct node
{
	int id,val,par,ch[2];    //id表示原数组下标，val表示权值
	friend bool operator<(node a,node b)
	{
		return a.id<b.id;
	}
	void init(int _id,int _val,int _par)
	{
		id=_id,val=_val,par=_par,ch[0]=ch[1]=0;
	}
}tree[maxn];
inline int cartesian_build(int n)
{
	for(int i=1;i<=n;i++)
	{
		int k=i-1;
		while(tree[k].val>tree[i].val) k=tree[k].par;
		tree[i].ch[0]=tree[k].ch[1];
		tree[k].ch[1]=i;
		tree[i].par=k;
		tree[tree[i].ch[0]].par=i;
	}
	return tree[0].ch[1];
}	
inline int dfs(int x)
{
	if(!x) return 0;
	int sz=dfs(tree[x].ch[0]);
	sz+=dfs(tree[x].ch[1]);
	ans=max(ans,(ll)(sz+1)*tree[x].val);
	return sz+1;
}
int main()
{
	while(scanf("%d",&n),n)
	{
		ans=0;tree[0].init(0,0,0);
		for(int i=1;i<=n;i++)
		{
			int x;scanf("%d",&x);
			tree[i].init(i,x,0);
		}
		int root=cartesian_build(n);
		dfs(root);
		printf("%lld\n",ans);
	}
	return 0;
}