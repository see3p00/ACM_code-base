#pragma GCC optimize(2)
#include<cstdio>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
stack<int>s;
ll a[maxn];int n;
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		if(n==0)break;
		int cur;ll ans=0,tmp=0;
		while(!s.empty())s.pop();
		for(int i=0;i<n;i++)scanf("%lld",&a[i]);a[n]=-1;
		for(int i=0;i<=n;i++)
		{
			if(s.empty()||a[s.top()]<=a[i])s.push(i);
			else 
			{
				while(!s.empty()&&a[s.top()]>a[i])
				{
					tmp=(i-s.top())*a[s.top()];
					ans=max(ans,tmp);
					cur=s.top();
					s.pop();
				}
				a[cur]=a[i];
				s.push(cur);
			}
		}
		printf("%lld\n",ans);
	}
    return 0;
}