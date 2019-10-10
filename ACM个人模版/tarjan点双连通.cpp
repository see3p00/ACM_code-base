// 点双联通分量
struct Edge
{
    int u,v;
};
int iscut[maxn],dfn[maxn],bccno[maxn],dfs_clock,bcc_cnt,bridge,n,m;
vector<int>G[maxn],bcc[maxn];
stack<Edge>S;
int dfs(int u,int fa)
{
    int lowu=dfn[u]=++dfs_clock;
    int child=0;
    for(auto &v:G[u])
    {
        Edge e=(Edge){u,v};
        if(!dfn[v])//没有访问过v
        {
            S.push(e);child++;
            int lowv=dfs(v,u);
            lowu=min(lowv,lowu); //用后代的low函数更新自己
            if(lowv>=dfn[u])
            {
                if(lowv>dfn[u])
                    ++bridge;          //判断是否是桥
                iscut[u]=1;
                bcc_cnt++;
                bcc[bcc_cnt].clear();//注意bcc从1开始编号
                int add =0;     //add含义：当前BCC中的边数；
                while(1)
                {
                    Edge x=S.top(); S.pop();
                    ++add;       //去一条边，add就加一；
                    if(bccno[x.u]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u]=bcc_cnt;
                    }
                    if(bccno[x.v]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v]=bcc_cnt;
                    }
                    if(x.u==u&&x.v==v) break;
                }
            }
        }
        else if(dfn[v]<dfn[u]&&v!=fa)
        {
            S.push(e);
            lowu=min(lowu,dfn[v]);//用反向边更新自己
        }
    }
    if(fa<0&&child==1) iscut[u]=0;
    return lowu;
}
void solve(int n)
{
    memset(dfn,0,sizeof dfn);
    memset(bccno,0,sizeof bccno);
    memset(iscut,0,sizeof iscut);
    while(!S.empty()) S.pop();
    dfs_clock=bcc_cnt=0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i,-1);
}
