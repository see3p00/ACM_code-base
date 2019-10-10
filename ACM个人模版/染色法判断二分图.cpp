//题意：n个人，给出每个人认识的人的信息。问能否将这些人分成两组，保证每组至少1个人，并且两两互相认识。
//思路：首先是反向建图。由于要求同组内两个人互相认识，那么两个人u,v，只要u不认识v或者v不认识有一个满足，就连接双向边u,v，表示u,v不能分到同一组。
//  染色法判断二分图
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1e3+10;
int mp[maxn][maxn],col[maxn],n;
std::vector<int>G[maxn];
bool dfs(int u,int c)
{
	col[u]=c;
	for(auto &v:G[u])
	{
		if(col[v])
		{
			if(col[v]==c)return 0;
			continue;
		}
		if(!dfs(v,1-c)) return 0;
	}
	return 1;
}
int main()
{
#ifdef LOCAL
	freopen("/Users/apple/desktop/input.txt","r",stdin);
#endif
	while(scanf("%d",&n)!=EOF)
	{
		for(int i=0;i<=n;i++)G[i].clear();
		memset(col,0,sizeof col);
	    memset(mp,0,sizeof mp);
	    for(int i=1;i<=n;i++)
	    {
	    	int t=1;
	    	while(1)
	    	{
	    		scanf("%d",&t);
	    		if(!t)break;
	    		mp[i][t]=1;
	    	}
	    }
	    for(int i=1;i<=n;i++)
	    	for(int j=i+1;j<=n;j++)
	    		if(!mp[i][j]||!mp[j][i]) G[i].emplace_back(j),G[j].emplace_back(i);
	    bool f=1;
	    for(int i=1;i<=n;i++)
	    	if(!col[i]&&!dfs(i,0))
	    	{
	    		f=0;break;
	    	}
	    if(f)puts("YES");
	    else puts("NO");
	}
	return 0;
}