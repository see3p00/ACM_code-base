#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int maxn=1e3+4;
std::vector<int> G[maxn];
int dep[maxn];
queue<int>q;
inline void topo()
{
	while(!q.empty())
	{
		int u=q.front();q.pop();
		printf("%d ",u);
		for(int i=0;i<G[u].size();i++)
		{
			int v=G[u][i];
			dep[v]--;
			if(!dep[v])q.push(v);
		}
	}
}
int main()
{
#ifdef LOCAL
	freopen("/Users/apple/desktop/input.txt","r",stdin);
#endif
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int y;
		while(scanf("%d",&y),y)
		{
			G[i].push_back(y);
			dep[y]++;
		}
	}
	for(int i=1;i<=n;i++)
		if(!dep[i])q.push(i);
	topo();
	return 0;
}