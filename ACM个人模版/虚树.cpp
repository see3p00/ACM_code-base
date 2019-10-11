//虚树
//给定一棵树，割断每一条边都有代价，
//每次询问会给定一些点，求用最少的代价使所有给定点都和1号节点不连通
#pragma GCC optimize(3, "Ofast", "inline")
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<ll>((x).size())
#define pii std::pair<ll,ll>
#define pll std::pair<ll,ll>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=250005;
const ll inf=0x3f3f3f3f3f3f3f3f;
int dep[maxn],Fa[maxn][21],dfn[maxn],tot,n,q;
std::vector<pair<int,ll>>G[maxn];
ll p[maxn];// i到根路径的最小值	
void dfs(int u,int fa,ll m)
{
	dep[u]=dep[fa]+1;
	Fa[u][0]=fa; dfn[u]=++tot;p[u]=m;
	for(int i=1;(1<<i)<=dep[u];i++)Fa[u][i]=Fa[Fa[u][i-1]][i-1];
	for(auto &it:G[u])
	{
		int v;ll w;tie(v,w)=it;
		if(v==fa)continue;
		dfs(v,u,min(m,w));
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--)if((1<<i)<=dep[x]-dep[y])x=Fa[x][i];
	if(x==y)return x;
    for(int i=20;i>=0;i--)if(Fa[x][i]!=Fa[y][i])x=Fa[x][i],y=Fa[y][i];
    return Fa[x][0];
}
std::vector<int> e[maxn];
int a[maxn],b[maxn],m;//待处理序列 是否为要求节点
int stk[maxn],top;
void Build()
{
	sort(a + 1, a + m + 1, [](int x, int y){return dfn[x] < dfn[y]; }); //按照dfs序从小到大处理
	stk[top = 1] = 1; //插入根节点
	for (int i = 1; i <= m; ++i)
	{
		int l = lca(a[i], stk[top]); //求与当前栈顶lca
		if (stk[top] == l) //lca就是栈顶 当前属于栈顶的子树
			stk[++top] = a[i]; //当前直接入栈
		else //原栈顶子树已经访问完毕
		{
			while (top > 1 && dfn[stk[top - 1]] >= dfn[l]) //说明栈的上一个元素和栈顶属于lca的同一个子树 或和lca是同一节点
				e[stk[top - 1]].emplace_back(stk[top]), --top; //构建栈顶子树的边 并只留这个子树一个节点或lca
			if (stk[top] != l) //此时原栈顶节点子树只剩下一个节点或lca
				e[l].emplace_back(stk[top]), stk[top] = l; // 若不为lca需要补上lca节点 将最后节点接上lca并插入lca
			stk[++top] = a[i]; //同stk[top]==l
		}
	}
	while (top > 1)
		e[stk[top - 1]].emplace_back(stk[top]), --top; //将最后节点连接
}
ll solve(int x, int f) //再新图上dp即可
{ 
	if (!SZ(e[x])) //叶子
		return b[x] = 0, p[x]; //清空标记
	ll s = 0;
	for (int y : e[x])
		if (y != f)
			s += solve(y, x); //剩下的叶子节点必为选定点
	e[x].clear(); //使用完毕清空边!!!
	if (b[x]) //当前为限制节点不受子树影响
		return b[x] = 0, p[x];
	return min(s, 1ll*p[x]); //切断所有子树或切断当前到根的最小代价
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w); //原图
	}
	dfs(1,0,inf);
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d",&m);
		for(int i=1;i<=m;i++)scanf("%d",&a[i]),b[a[i]]=1;
		Build();
		printf("%lld\n",solve(1,0));
	}
    return 0;
}