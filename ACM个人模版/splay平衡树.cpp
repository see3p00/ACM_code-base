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
struct Node
{
    int fa,ch[2],val,cnt,size;
}spl[maxn];
int cnt,root;
inline void update(int x)
{
    spl[x].size=spl[spl[x].ch[0]].size+spl[spl[x].ch[1]].size+spl[x].cnt;
}
inline void rotate(int x)
{
    int f=spl[x].fa,ff=spl[f].fa;
    spl[ff].ch[spl[ff].ch[1]==f]=x;
    spl[x].fa=ff;
    int k=spl[f].ch[1]==x;
    spl[f].ch[k]=spl[x].ch[k^1];
    spl[spl[x].ch[k^1]].fa=f;
    spl[x].ch[k^1]=f;
    spl[f].fa=x;
    update(f);
}
inline void splaying(int x,int top)
{
    while(spl[x].fa!=top)
    {
        int f=spl[x].fa,ff=spl[f].fa;
        if(ff!=top) (spl[ff].ch[0]==f)^(spl[f].ch[0]==x)?rotate(x):rotate(f);
        rotate(x);
    }
    if(!top) root=x;
}
inline void newnode(int &now,int fa,int val)
{
    spl[now=++cnt].val=val;
    spl[now].fa=fa;
    spl[now].size=spl[now].cnt=1;
}
inline void ins(int val,int &now=root,int fa=0)
{
    if(!now)
    {
        newnode(now,fa,val);
        splaying(now,0);
    }
    else if(val<spl[now].val) ins(val,spl[now].ch[0],now);
    else if(val>spl[now].val) ins(val,spl[now].ch[1],now);
    else spl[now].cnt++,splaying(now,0);
}
inline void delnode(int x)
{
    splaying(x,0);
    if(spl[x].cnt>1) spl[x].cnt--;
    else if(spl[x].ch[1])
    {
        int p = spl[x].ch[1];
        while(spl[p].ch[0]) p=spl[p].ch[0];
        splaying(p,x);
        spl[p].fa=0;
        spl[p].ch[0]=spl[x].ch[0];
        spl[spl[x].ch[0]].fa=p;
        root=p;
        update(root);
    }
    else root=spl[x].ch[0],spl[spl[x].ch[0]].fa=0;
}
inline void del(int val,int now=root)
{
    if(val==spl[now].val) delnode(now);
    else if(val<spl[now].val) del(val,spl[now].ch[0]);
    else del(val,spl[now].ch[1]);
}
inline int getrank(int val)
{
    int now = root, rank = 1;
    while(now)
    {
        if(spl[now].val==val)
        {
            rank+=spl[spl[now].ch[0]].size;
            splaying(now,0);
            break;
        }
        if(val<=spl[now].val)
            now=spl[now].ch[0];
        else 
        {
            rank+=spl[spl[now].ch[0]].size+spl[now].cnt;
            now=spl[now].ch[1];
        }
    }
    return rank;
}
inline int getnum(int rank)
{
    int now = root;
    while(now)
    {
        int lsize = spl[spl[now].ch[0]].size;
        if(lsize+1<=rank&&rank<=lsize+spl[now].cnt)
        {
            splaying(now,0);
            break;
        }
        else if(lsize>=rank)
            now=spl[now].ch[0];
        else 
        {
            rank-=lsize+spl[now].cnt;
            now=spl[now].ch[1];
        }
    }
    return spl[now].val;
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