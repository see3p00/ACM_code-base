//插入x数
//删除x数(若有多个相同的数，因只删除一个)
//查询x数的排名(排名定义为比当前数小的数的个数+1.若有多个相同的数，因输出最小的排名)
//查询排名为x的数
//求x的前驱(前驱定义为小于x，且最大的数)
//求x的后继(后继定义为大于x，且最小的数)
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii pair<int,int>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1e5+10;
std::mt19937 rnd(233);
struct node
{
	int l,r;//左右
	int val,key;//值，索引
	int size;//子树大小
}fhq[maxn];
int cnt,root;
inline int newnode(int val)
{
	fhq[++cnt].val=val;
	fhq[cnt].key=rnd();
	fhq[cnt].size=1;
	return cnt;
}
inline void update(int now)
{
	fhq[now].size=fhq[fhq[now].l].size+fhq[fhq[now].r].size+1;
}
inline void split(int now,int val,int &x,int &y)
{
	if(!now)x=y=0;
	else
	{
		if(fhq[now].val<=val)
		{
			x=now;
			split(fhq[now].r,val,fhq[now].r,y);
		}
		else
		{
			y=now;
			split(fhq[now].l,val,x,fhq[now].l);
		}
		update(now);
	}
}
inline int merge(int x,int y)
{
	if(!x||!y)return x+y;
	if(fhq[x].key>fhq[y].key)
	{
		fhq[x].r=merge(fhq[x].r,y);
		update(x);
		return x;
	}
	else
	{
		fhq[y].l=merge(x,fhq[y].l);
		update(y);
		return y;
	}
}
int x,y,z;
inline void ins(int val)
{
	split(root,val,x,y);
	root=merge(merge(x,newnode(val)),y);
}
inline void del(int val)
{
	split(root,val,x,z);
	split(x,val-1,x,y);
	y=merge(fhq[y].l,fhq[y].r);
	root=merge(merge(x,y),z);
}
inline void getrank(int val)
{
	split(root,val-1,x,y);
	printf("%d\n",fhq[x].size+1);
	root=merge(x,y);
}
inline void getnum(int rank)
{
	int now=root;
	while(now)
	{
		if(fhq[fhq[now].l].size+1==rank) break;
		else if(fhq[fhq[now].l].size>=rank) now=fhq[now].l;
		else
		{
			rank-=fhq[fhq[now].l].size+1;
			now=fhq[now].r;
		}
	}
	printf("%d\n",fhq[now].val);
}
inline void pre(int val)
{
	split(root,val-1,x,y);
	int now=x;
	while(fhq[now].r) now=fhq[now].r;
	printf("%d\n",fhq[now].val);
	root=merge(x,y);
}
inline void nxt(int val)
{
	split(root,val,x,y);
	int now=y;
	while(fhq[now].l) now=fhq[now].l;
	printf("%d\n",fhq[now].val);
	root=merge(x,y);
}
int main()
{
#ifdef LOCAL
	freopen("input.txt","r",stdin);
#endif
	int t;scanf("%d",&t);
	while(t--)
	{
		int op,x;scanf("%d%d",&op,&x);
		switch(op)
		{
			case 1:
			    ins(x);
			    break;
			case 2:
			    del(x);
			    break;
			case 3:
			    getrank(x);
			    break;
			case 4:
			    getnum(x);
			    break;
			case 5:
			    pre(x);
			    break;
			case 6:
			    nxt(x);
			    break;
		}
	}
	return 0;
}