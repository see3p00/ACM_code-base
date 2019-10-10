// read(n);read(m);read(r);
// 存边
// solve(r,n);
// 注意n和m的标号 是从0开始的还是从1开始的
// 注意初始化为0或者-1
int in[maxn];//in[i]记录i入边中最小的权值
int id[maxn];//id[i]记录节点i所在环的编号
int vis[maxn];//标记作用
int pre[maxn];//存储父节点
int n,m,r;
struct Edge
{
    int from,to,cost;
}edge[maxn];
inline int solve(int rt, int n)
{
    int res=0;
    while(true)
    {
        for(int i=1;i<=n;++i)
            in[i]=0x3f3f3f3f;//初始化,将每一个入度的权值清为INF
        //第一步,找到除了root以外,其他的点的权值最小的入边
        for(int i=1;i<=m;++i)
            if(edge[i].from!=edge[i].to&&in[edge[i].to]>edge[i].cost)//如果是一条边并且边权值小于入度的权值
            {
                pre[edge[i].to]=edge[i].from;//记录前驱
                in[edge[i].to]=edge[i].cost;    //更新
            }
        //第二步,判断是不是除了root以外还有其他孤立的点.
        for(int i=1;i<=n;++i)
        {
            if(i!=rt&&in[i]==0x3f3f3f3f)return -1;//如果除了root以外有其他孤立点 则不存在最小树形图,那肯定了,都不连通了..
        }
        //第三步,找到图中所有的环,对环进行缩点,重新编号
        int cnt=0;//记录当前查找中 环的总数
        in[rt]=0;
        memset(id,-1,sizeof(id));
        memset(vis,-1,sizeof(vis));
        for(int i=1,v;i<=n;++i)
        {
            res+=in[i];
            v=i;
            // 构造环
            while(v!=rt&&vis[v]!=i&&id[v]==-1)
            {
                vis[v]=i;
                v=pre[v];
            }
            /*判断是否存在环，如果存在环则进行缩点，环中每一个顶点对应同一个顶点cnt*/
            if(v!=rt&&id[v]==-1)
            {
                for(int cost=pre[v];cost!=v;cost=pre[cost])id[cost]=cnt;
                id[v]=cnt++;
            }
        }
        if(!cnt)break; /*如果不存在环，则当前树即为最小树形图*/
        /*对于其他不在环中的顶点进行编号*/
        for(int i=1;i<=n;++i)
            if(id[i]==-1)id[i]=cnt++;
        /*对相应的边进行修改*/
        for(int i=1,from,to;i<=m;++i)
        {
            from=edge[i].from,to=edge[i].to;
            edge[i].from=id[from],edge[i].to=id[to];
            if(id[from]^id[to])edge[i].cost-=in[to];
        }
        n=cnt-1;
        rt=id[rt];
    }
    return res;
}
