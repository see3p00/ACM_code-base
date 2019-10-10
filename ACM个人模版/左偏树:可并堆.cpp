/* 左偏树 可并堆
一开始有N个小根堆，每个堆包含且仅包含一个数。接下来需要支持两种操作：

操作1： 1 x y 将第x个数和第y个数所在的小根堆合并（若第x或第y个数已经被删除或第x和第y个数在用一个堆内，则无视此操作）

操作2： 2 x 输出第x个数所在的堆最小数，并将其删除（若第x个数已经被删除，则输出-1并无视删除操作）


*/
#define ls s[x].son[0]
#define rs s[x].son[1]
const int maxn=1e5+5;
int n,m;
struct tree
{
	int dis,val,son[2],rt;
}s[maxn];
inline int get(int x)
{
	return s[x].rt==x?x:s[x].rt=get(s[x].rt);
}
inline int merge(int x,int y)
{
	if(!x||!y) return x+y;if(s[x].val>s[y].val||(s[x].val==s[y].val&&x>y))swap(x,y);
	rs=merge(rs,y);if(s[ls].dis<s[rs].dis)swap(ls,rs);s[ls].rt=s[rs].rt=s[x].rt=x,s[x].dis=s[rs].dis+1;return x;
}
inline void pop(int x)
{
	s[x].val=-1,s[ls].rt=ls,s[rs].rt=rs,s[x].rt=merge(ls,rs);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)s[i].rt=i,scanf("%d",&s[i].val);
	while(m--)
	{
		int op;scanf("%d",&op);
		if(op==1)
		{
			int x,y;scanf("%d%d",&x,&y);
			if(s[x].val==-1||s[y].val==-1)continue;
			if(get(x)!=get(y))s[get(x)].rt=s[get(y)].rt=merge(get(x),get(y));
		}
		else
		{
			int x;scanf("%d",&x);
			if(s[x].val==-1)printf("-1\n");
			else printf("%d\n",s[get(x)].val),pop(get(x));
		}
	}
	return 0;
}
