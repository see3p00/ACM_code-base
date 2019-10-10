/*
    第 k 短路的 A* 搜索算法，估价函数 f = g + h
    其中 ：
        g = 起始点 到 当前点 的距离，也即是当前的距离，可以在 BFS 的时候直接求出
        h = 当前点 到 终点 的最短距离（这样才满足 A* 的条件）
    对于无向图，我们直接对原图跑一遍 dijstra 就可以求出终点到其他各个点的最短距离
    对于有向图，我们反向建边一次，在新建的图中跑一遍 dijstra 也可以求出来终点到各个点的最短距离
    
*/
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <stack>
 
#define INT_INF 0x3fffffff
#define LL_INF 0x3fffffffffffffff
#define EPS 1e-12
#define MOD 1000000007
#define PI 3.141592653579798
#define N 300
 
using namespace std;
 
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
 
struct data
{
    int st,en,val,next;
} edge[100005],e[100005];
 
int head[1005],h[1005],tot,tot2;
 
bool vs[1005];
int dis[1005];
 
struct node
{
    int id,len,h;
    bool operator <(const node &a) const
    {
        if(a.len+a.h==len+h) return a.len<len;
        else return a.len+a.h<len+h;
    }
};
 
void add_edge(int st,int en,int val)
{
    edge[tot].st=st;
    edge[tot].en=en;
    edge[tot].val=val;
    edge[tot].next=head[st];
    head[st]=tot++;
}
 
void add_e(int st,int en,int val)
{
    e[tot2].st=st;
    e[tot2].en=en;
    e[tot2].val=val;
    e[tot2].next=h[st];
    h[st]=tot2++;
}
 
/*对反向边求一次 dijstra ，求得各个点到终点的最短距离，也就是我们 A* 的估价函数中的 h 函数*/
void dijstra(int st,int n)
{
    memset(vs,0,sizeof(vs));
    for(int i=1;i<=n;i++)
        dis[i]=INT_INF;
    for(int i=h[st];i!=-1;i=e[i].next)
    {
        dis[e[i].en]=e[i].val;
    }
    dis[st]=0;
    while(1)
    {
        int k=-1 , Min=INT_INF;
        for(int i=1;i<=n;i++)
            if(!vs[i] && dis[i]<Min)
            {
                k=i;
                Min=dis[i];
            }
        if(k==-1) break;
        vs[k]=1;
        for(int i=h[k];i!=-1;i=e[i].next)
            if(!vs[e[i].en] && dis[e[i].en]>dis[k]+e[i].val)
                dis[e[i].en]=dis[k]+e[i].val;
    }
}
 
/*对起点 s 终点 t 求第 k 短路，如果找不到，返回 -1*/
int kth_path(int s,int t,int k)
{
    if(dis[s]==INT_INF) return -1;
    if(s==t) k++;
    priority_queue<node> q;
    node now;
    now.id=s; now.len=0; now.h=dis[s];
    q.push(now);
    int cnt=0;
    while(!q.empty())
    {
        node now=q.top(); q.pop();
        if(now.id==t) cnt++;
        if(cnt==k) return now.len;
        for(int i=head[now.id];i!=-1;i=edge[i].next)
        {
            node new_v;
            new_v.id=edge[i].en; new_v.len=now.len+edge[i].val; new_v.h=dis[edge[i].en];
            q.push(new_v);
        }
    }
    return -1;
}
 
int main()
{
    int n,m,a,b,t,s,k;
    scanf("%d%d",&n,&m);  //n 个点 m 条边 (边是有向边)
    memset(head,-1,sizeof(head));
    memset(h,-1,sizeof(h));
    tot=tot2=0;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&t);
        add_edge(a,b,t);
        add_e(b,a,t);
    }
    scanf("%d%d%d",&s,&t,&k);  //读入起点 s 终点 t 以及要求的第 k 短路中的 k
    dijstra(t,n);
    int ans=kth_path(s,t,k);
    printf("%d\n",ans);
    return 0;
}