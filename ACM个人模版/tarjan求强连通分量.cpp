/*
 dfn[] 当前节点在dfs时是被第几个搜到的  即dfs序
 low[] 当前节点能访问到的点中dfn最小值
 vis[] 标记是否访问过
 belong[] 属于哪个强连通分量
 */
std::vector<int> G[maxn];
int dfn[maxn],low[maxn],vis[maxn],belong[maxn],st[maxn],cnt[maxn],top,sum,deep;

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
            id[sum].emplace_back(v);//当前强连通的子集
        }while(u!=v);
    }
}

for (int i = 1 ;i <= n ; i ++)
{
    if (!dfn[i]) tarjan(i);
}
