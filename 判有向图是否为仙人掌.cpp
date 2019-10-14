// 判断一个图是否为仙人掌
#pragma GCC optimize(3, "Ofast", "inline")
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<ll>((x).size())
#define pii std::pair<ll,ll>
#define pll std::pair<ll,ll>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=2e5;
int fa[maxn],cnt[maxn],low[maxn],dfn[maxn],st[maxn],belong[maxn],deep,n,sum,top,flag;
bool vis[maxn];
std::vector<int>G[maxn];
inline void tarjan(int u)
{
    low[u]=dfn[u]=++deep;//时间戳
    st[++top]=u;//入栈
    vis[u]=1;
    for(auto &v:G[u])
    {
        if(!dfn[v])//是否已经访问
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v])//已经访问过并且在栈里
        {
            low[u]=min(low[u],dfn[v]);
            if(low[u]!=dfn[v])
            {
                flag=1;
            }
        }
    }
    int v;
    if(low[u]==dfn[u])
    {
        sum++;//强连通
        do{
            v=st[top--];//出栈
            vis[v]=0;//v出栈后
            belong[v]=sum;//v属于哪个强连通1-sum
        }while(u!=v);
    }
}
int main()
{
#ifdef LOCAL
    freopen("input.txt","r",stdin);
#endif
    int t;scanf("%d",&t);
    while(t--)
    {
        flag=deep=sum=0;
        
        scanf("%d",&n);int u,v;
        for(int i=0;i<=n+5;i++)G[i].clear(),belong[i]=dfn[i]=low[i]=cnt[i]=0;
        while(scanf("%d%d",&u,&v)!=EOF&&u+v)
        {
            u++,v++;
            G[u].emplace_back(v);
        }
        for(int i=1;i<=n;i++)
            if(!dfn[i])tarjan(i);
        if(flag||sum!=1) puts("NO");
        else puts("YES");
    }
    return 0;
}
