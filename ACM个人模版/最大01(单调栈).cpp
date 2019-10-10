#pragma GCC optimize(2)
#include<cstdio>
#include<iostream>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int maxn=2e3+5;
int mp[maxn][maxn],n,m;
int h[maxn][maxn];
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		int ans=0,tmp=0;int cur;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				scanf("%d",&mp[i][j]);
				if(mp[i][j]&&i!=0)
				mp[i][j]+=mp[i-1][j];
			}
		}
		for(int i=0;i<n;i++)
		{
			stack<int>s;mp[i][m]=-1;
			for(int j=0;j<=m;j++)
			{
				if(s.empty()||mp[i][s.top()]<=mp[i][j])s.push(j);
				else
				{
					while(!s.empty()&&mp[i][s.top()]>mp[i][j])
					{
						tmp=(j-s.top())*mp[i][s.top()];
						ans=max(ans,tmp);
						cur=s.top();
						s.pop();
					}
					mp[i][cur]=mp[i][j];
					s.push(cur);
				}
			}
		}
		printf("%d\n",ans);
	}
    return 0;
}