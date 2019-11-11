std::vector<int>G[maxn],pbc[maxn];
int dfn[maxn],low[maxn],st[maxn],deep,top,pbccnt;
void dfs(int u,int fa)
{
	dfn[u]=low[u]=++deep;
	st[top++]=u;
	for(int i=0;i<G[u].size();i++)
	{
		int v=G[u][i];
		if(!dfn[v])
		{
			dfs(v,u);
			low[u]=std::min(low[u],low[v]);
			if(low[v]>=dfn[u])
			{
				pbccnt++;
				while(top>0)
				{
					pbc[pbccnt].push_back(st[--top]);
					if(st[top]==v) break;
				}
				pbc[pbccnt].push_back(u);
			}
		}
		else if(v!=fa) low[u]=std::min(low[u],dfn[v]);
	}
}
int main()
{
	// 读入图
	for(int i=1;i<=n;i++)
		if(!dfn[i]) dfs(i,0); // 缩点
	for(int i=0;i<=n+2;i++)G[i].clear();  //清空图
	for(int i=1;i<=pbccnt;i++)   //重新建圆方树
		for(int j=0;j<pbc[i].size();j++)
			G[n+i].push_back(pbc[i][j]),
			G[pbc[i][j]].push_back(n+i);
}