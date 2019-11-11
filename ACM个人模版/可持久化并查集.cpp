//n个集合 m个操作
//1 a b 合并a,b所在集合
//2 k 回到第k次操作之后的状态(查询算作操作)
//3 a b 询问a,b是否属于同一集合，是则输出1否则输出0
#include<bits/stdc++.h>
 
const int maxn=2e5+5;
int n,m;
struct node
{
	int l,r,val;
}T[maxn*40];
int cnt,rootfa[maxn],rootdep[maxn],tot;
void build(int l,int r,int &now)
{
	now=++cnt;
	if(l==r){T[now].val=++tot;return;}
	int m=(l+r)>>1;
	build(l,m,T[now].l);build(m+1,r,T[now].r);
}
void update(int l,int r,int ver,int &now,int pos,int val)
{
	T[now=++cnt]=T[ver];
	if(l==r)
	{
		T[now].val=val;
		return ;
	}
	int m=(l+r)>>1;
	if(pos<=m) update(l,m,T[ver].l,T[now].l,pos,val);
	else update(m+1,r,T[ver].r,T[now].r,pos,val);
}
int query(int l,int r,int now,int pos)
{
	if(l==r)return T[now].val;
	int m=(l+r)>>1;
	if(pos<=m) return query(l,m,T[now].l,pos);
	else return query(m+1,r,T[now].r,pos);
}
int find(int ver,int x)
{
	int fx=query(1,n,rootfa[ver],x);
	return fx==x?x:find(ver,fx);
}
void merge(int ver,int x,int y)
{
	x=find(ver-1,x);
	y=find(ver-1,y);
	if(x==y)
    {
        rootfa[ver]=rootfa[ver-1];
        rootdep[ver]=rootdep[ver-1];
    }
    else
    {
        int depx=query(1,n,rootdep[ver-1],x);
        int depy=query(1,n,rootdep[ver-1],y);
        if(depx<depy)
        {
            update(1,n,rootfa[ver-1],rootfa[ver],x,y);
            rootdep[ver]=rootdep[ver-1];
        }
        else if(depx>depy)
        {
            update(1,n,rootfa[ver-1],rootfa[ver],y,x);
            rootdep[ver]=rootdep[ver-1];
        }
        else
        {
            update(1,n,rootfa[ver-1],rootfa[ver],x,y);
            update(1,n,rootdep[ver-1],rootdep[ver],y,depy+1);
        }
    }
}

int main()
{
#ifdef LOCAL
	freopen("input.txt","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	build(1,n,rootfa[0]);
	for(int ver=1;ver<=m;ver++)
	{
		int op;scanf("%d",&op);
		if(op==1)
		{
			int x,y;scanf("%d%d",&x,&y);
			merge(ver,x,y);
		}
		if(op==2)
		{
			int x;scanf("%d",&x);
			rootfa[ver]=rootfa[x];
			rootdep[ver]=rootdep[x];
		}
		if(op==3)
		{
			int x,y;scanf("%d%d",&x,&y);
			rootfa[ver]=rootfa[ver-1];
            rootdep[ver]=rootdep[ver-1];
            int fx=find(ver,x);
            int fy=find(ver,y);
            printf("%d\n",fx==fy?1:0);
		}
	}
	return 0;
}