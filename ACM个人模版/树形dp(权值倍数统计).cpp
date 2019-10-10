//  树上路径统计
//  统计 u-v路径权值和为xxxx的倍数
//  输出数量
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii pair<int,int>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=2e4+100;
std::vector<pii>G[maxn];int n;
ll dp[maxn][2019],ans;
inline void dfs(int u,int fa)
{
	dp[u][0]=1;
    for(auto &it:G[u])
    {
    	int v,w;tie(v,w)=it;
        if(v==fa)continue;dfs(v,u);
        for(int j=0;j<2019;j++) ans+=dp[v][j]*dp[u][(2019-(j+w)%2019)%2019];
        for(int j=0;j<2019;j++) dp[u][(j+w)%2019]+=dp[v][j];
    }
}
int main()
{
#ifdef LOCAL
	freopen("input.txt","r",stdin);
#endif
	while(scanf("%d",&n)!=EOF)
	{
		for(int i=0;i<=n+10;i++)for(int j=0;j<2019;j++)dp[i][j]=0;
		for(int i=0;i<=n+10;i++)G[i].clear();ans=0;
		for(int i=1;i<n;i++)
		{
			int u,v,w;scanf("%d%d%d",&u,&v,&w);
			G[u].emplace_back(v,w);
			G[v].emplace_back(u,w);
		}
		dfs(1,0);
		printf("%lld\n",ans);
	}
	return 0;
}