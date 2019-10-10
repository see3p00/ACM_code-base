#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
const int maxn=101000;
using std::swap;
using std::min;
struct Edge
{
    int p;
    int w;
    int f;
    int nxt;
};
struct Data
{
    int p;
    int d;
    bool operator <(const Data &a)const
    {
        return d<a.d;
    }
};
int n,m,s,t;
int len;
Data base[maxn<<6];
Data top()
{
    return base[1];
}
void pop()
{
    swap(base[1],base[len--]);
    int pos=1;
    int nxt;
    while(true)
    {
        nxt=pos;
        if(base[pos<<1]<base[nxt]&&(pos<<1)<=len)
            nxt=pos<<1;
        if(base[pos<<1|1]<base[nxt]&&(pos<<1|1)<=len)
            nxt=pos<<1|1;
        if(pos==nxt)    break;
        swap(base[pos],base[nxt]);
        pos=nxt;
    }
}
void push(Data val)
{
    base[++len]=val;
    int pos=len;
    while((pos>>1)&&base[pos]<base[pos>>1])
    {
        swap(base[pos>>1],base[pos]);
        pos>>=1;
    }
    return ;
}
Edge line[maxn<<1];
int head[maxn],tail=-1;
void add(int a,int b,int c,int d)
{
    line[++tail].p=b;
    line[tail].w=c;
    line[tail].f=d;
    line[tail].nxt=head[a];
    head[a]=tail;
}
int h[maxn];
bool vis[maxn];
int dis[maxn];
int from[maxn];
int L[maxn];
int flow[maxn];
int Max_flow,Min_cost;
bool dijkstra(int begin,int end)
{
    len=0;
    for(int i=1;i<=n;i++)
    {
        dis[i]=0x7fffffff;
        flow[i]=0x7fffffff;
        from[i]=L[i]=vis[i]=0;
    }
    dis[begin]=0;
    Data pas;
    pas.p=begin;pas.d=0;
    push(pas);
    while(len)//手写堆怪我喽
    {
        pas=top();pop();
        while(vis[pas.p]&&len>=1)
        {
            pas=top();
            pop();
        }
        if(vis[pas.p]&&!len)    break;
        vis[pas.p]=true;
        dis[pas.p]=pas.d;
        for(int i=head[pas.p];i!=-1;i=line[i].nxt)
            if(line[i].f>0&&!vis[line[i].p]&&dis[line[i].p]>dis[pas.p]+line[i].w+h[pas.p]-h[line[i].p])//判断，带上势
            {
                dis[line[i].p]=dis[pas.p]+line[i].w+h[pas.p]-h[line[i].p];//跟spfa一样的套路，就是多了个势
                flow[line[i].p]=min(line[i].f,flow[pas.p]);
                from[line[i].p]=pas.p;
                L[line[i].p]=i;
                Data nxt;
                nxt.p=line[i].p;nxt.d=dis[line[i].p];
                push(nxt);
            }
    }
    return dis[end]!=0x7fffffff;
}
void MCMA(int begin,int end)
{
    while(dijkstra(begin,end))//差不多跟spfa一样的格式，就是加了个h数组
    {
        int max_flow=flow[end];
        Min_cost+=max_flow*(dis[end]-h[begin]+h[end]);
        Max_flow+=max_flow;
        for(int i=end;i!=begin;i=from[i])
        {
            line[L[i]].f-=max_flow;
            line[L[i]^1].f+=max_flow;
        }
        for(int i=1;i<=n;i++)
            h[i]+=dis[i];//累加，一定要累加，虽然不累加可能过几个点
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=n;i++)   head[i]=-1;
    for(int i=1;i<=m;i++)
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        add(a,b,d,c);add(b,a,-d,0);//建边
    }
    MCMA(s,t);//跑费用流
    printf("%d %d",Max_flow,Min_cost);//输出
    return 0;
}