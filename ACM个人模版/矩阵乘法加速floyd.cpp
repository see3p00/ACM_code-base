//  从s-t恰好经过n条边的最短路
/* input:
2 6 6 4
11 4 6
4 4 8
8 4 9
6 6 8
2 6 9
3 8 9
output:10
*/  
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii std::pair<int,int>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1e5+5;
int n,m,s,t,mp[1000005],cnt;
struct floyd
{
    int d[505][505];
    floyd(){memset(d,0x3f,sizeof d);}
    floyd operator* (const floyd &a)const
    {
        floyd res;
        for(int k=1;k<=cnt;k++)
            for(int i=1;i<=cnt;i++)
                for(int j=1;j<=cnt;j++)
                    res.d[i][j]=min(res.d[i][j],d[i][k]+a.d[k][j]);
        return res;
    }
}ans;
inline floyd fpow(floyd a,int n)
{
    floyd res=a;
    while(n)
    {
        if(n&1)res=res*a;
        a=a*a;
        n>>=1;
    }
    return res;
}
int main()
{
#ifdef LOCAL
    freopen("input.txt","r",stdin);
#endif
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;scanf("%d%d%d",&w,&u,&v);
        if(!mp[u]) mp[u]=++cnt;
        if(!mp[v]) mp[v]=++cnt;
        ans.d[mp[u]][mp[v]]=ans.d[mp[v]][mp[u]]=w;
    }
    printf("%d\n",fpow(ans,n-1).d[mp[s]][mp[t]]);
    return 0;
}
