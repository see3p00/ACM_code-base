//Author wzazzy  ^_^
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+100;
ll dp[32][2][2][2][2],a,b,c;
ll dfs(int pos,int la,int lb,int And,int Xor) //pos位，la是否达到a的上限，lb是否达到b的上限
{
	if(pos<0)return 1;
	if(dp[pos][la][lb][And][Xor]!=-1)return dp[pos][la][lb][And][Xor];
    int na=1,nb=1,nand=1,nxor=0;ll res=0;
    if(la) na=(a>>pos&1);if(lb) nb=(b>>pos&1);
    if(And) nand=(c>>pos&1);if(Xor) nxor=(c>>pos&1);
    for(int i=0;i<=na;i++)
        for(int j=0;j<=nb;j++)
        {
            if((i&j)>nand) continue; if((i^j)<nxor) continue;
            res+=dfs(pos-1,la&&(i==na),lb&&(j==nb),And&&((i&j)==nand),Xor&&((i^j)==nxor));
        }
    return dp[pos][la][lb][And][Xor]=res;
}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		memset(dp,-1,sizeof dp);
		scanf("%lld%lld%lld",&a,&b,&c);
		ll ans=dfs(30,1,1,1,1)-max(0ll,a-c+1)-max(0ll,b-c+1);
		printf("%lld\n",1LL*a*b-ans);
	}
    return 0;
}