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
const double alpha=0.75;
std::vector<int> v;
struct node
{
	int l,r,val;// 左，右，值
	int size,fact;// 子树大小，实际子树大小
	bool exist; // 这个节点是否存在
}tzy[maxn];
int cnt,root;
inline void newnode(int &now,int val)
{
	now=++cnt;
	tzy[now].val=val;
	tzy[now].size=tzy[now].fact=1;
	tzy[now].exist=true;
}
inline bool imbalence(int now)
{
	if(max(tzy[tzy[now].l].size,tzy[tzy[now].r].size)>tzy[now].size*alpha||tzy[now].size-tzy[now].fact>tzy[now].size*0.3)
		return true;
	return false;
}
inline void ldr(int now)
{
	if(!now) return ;
	ldr(tzy[now].l);
	if(tzy[now].exist) v.emplace_back(now);
	ldr(tzy[now].r);
}
inline void lift(int l,int r,int &now)
{
	if(l==r)
	{
		now=v[l];
		tzy[now].l=tzy[now].r=0;
		tzy[now].size=tzy[now].fact=1;
		return ;
	}
	int m=(l+r)>>1;
	while(m&&l<m&&tzy[v[m]].val==tzy[v[m-1]].val) m--;
	now=v[m];
	if(l<m)lift(l,m-1,tzy[now].l);
	else tzy[now].l=0;
	lift(m+1,r,tzy[now].r);
	tzy[now].size=tzy[tzy[now].l].size+tzy[tzy[now].r].size+1;
	tzy[now].fact=tzy[tzy[now].l].fact+tzy[tzy[now].r].fact+1;
}
inline void rebuild(int &now)
{
	v.clear();
	ldr(now);
	if(v.empty())
	{
		now=0;
		return ;
	}
	lift(0,v.size()-1,now);
}
inline void update(int now,int end)
{
	if(!now) return ;
	if(tzy[end].val<tzy[now].val) update(tzy[now].l,end);
	else update(tzy[now].r,end);
	tzy[now].size=tzy[tzy[now].l].size+tzy[tzy[now].r].size+1;
}
inline void check(int &now,int end)
{
	if(now==end) return ;
	if(imbalence(now))
	{
		rebuild(now);
		update(root,now);
		return ;
	}
	if(tzy[end].val<tzy[now].val)
		check(tzy[now].l,end);
	else check(tzy[now].r,end);
}
inline void ins(int &now,int val)
{
	if(!now)
	{
		newnode(now,val);
		check(root,now);
		return ;
	}
	tzy[now].size++;
	tzy[now].fact++;
	if(val<tzy[now].val) ins(tzy[now].l,val);
	else ins(tzy[now].r,val);
}
inline void del(int now,int val)
{
	if(tzy[now].exist&&tzy[now].val==val)
	{
		tzy[now].exist=false;
		tzy[now].fact--;
		check(root,now);
		return ;
	}
	tzy[now].fact--;
	if(val<tzy[now].val) del(tzy[now].l,val);
	else del(tzy[now].r,val);
}
inline int getrank(int val)
{
	int now=root,rank=1;
	while(now)
	{
		if(val<=tzy[now].val)
			now=tzy[now].l;
		else
		{
			rank+=tzy[now].exist+tzy[tzy[now].l].fact;
			now=tzy[now].r;
		}
	}
	return rank;
}
inline int getnum(int rank)
{
	int now=root;
	while(now)
	{
		if(tzy[now].exist&&tzy[tzy[now].l].fact+tzy[now].exist==rank)
			break;
		else if(tzy[tzy[now].l].fact>=rank)
			now=tzy[now].l;
		else
		{
			rank-=tzy[tzy[now].l].fact+tzy[now].exist;
			now=tzy[now].r;
		}
	}
	return tzy[now].val;
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
			    ins(root,x);
			    break;
			case 2:
			    del(root,x);
			    break;
			case 3:
			    printf("%d\n",getrank(x));
			    break;
			case 4:
			    printf("%d\n",getnum(x));
			    break;
			case 5:
			    printf("%d\n",getnum(getrank(x)-1));
			    break;
			case 6:
			    printf("%d\n",getnum(getrank(x+1)));
			    break;
		}
	}
	return 0;
}