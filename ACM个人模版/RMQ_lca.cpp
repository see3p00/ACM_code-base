struct Lca 
{
	int pos[maxn], dep[maxn], dis[maxn], idx; 
	int lg2[maxn * 2], tb[20][maxn * 2]; 
	void Init(int n, int rt = 1)
	{
		dep[rt] = idx = 0, DFS(rt, 0);
		lg2[0] = -1, n *= 2;
		for (int i = 1; i <= n; ++i)
			lg2[i] = lg2[i >> 1] + 1;
		for (int i = 1; i <= lg2[n]; ++i)
			for (int j = 1; j + (1 << i) - 1 <= n; ++j)
				if (dep[tb[i - 1][j]] < dep[tb[i - 1][j + (1 << (i - 1))]]) 
					tb[i][j] = tb[i - 1][j];
				else
					tb[i][j] = tb[i - 1][j + (1 << (i - 1))];
	}
	void DFS(int x, int fz)
	{
		pos[x] = ++idx, dep[x] = dep[fz] + 1, tb[0][idx] = x; 
		for (auto it : G[x])
		{
			int y = it.first, w = it.second;
			if (y != fz)
				dis[y] = dis[x] + w, DFS(y, x), tb[0][++idx] = x; 
		}
	}
	int LCA(int x, int y)
	{
		x = pos[x], y = pos[y]; 
		if (x > y)
			swap(x, y); 
		int w = lg2[y - x + 1];
		if (dep[tb[w][x]] < dep[tb[w][y - (1 << w) + 1]]) 
			return tb[w][x]; 
		return tb[w][y - (1 << w) + 1];
	}
	int Dis(int x, int y)
	{
		return dis[x] + dis[y] - dis[LCA(x, y)] * 2;
	}
}lca;