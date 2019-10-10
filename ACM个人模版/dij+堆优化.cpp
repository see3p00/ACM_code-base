#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
const int maxm=5e5+5;

struct edge
{
    int to,dis,next;
}e[maxm];
int head[maxn],dis[maxn],cnt;
bool vis[maxn];
int n,m,s;

inline void addedge(int u,int v,int w)
{
    cnt++;
    e[cnt].dis=w;
    e[cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}

struct node
{
    int dis;int pos;
    bool operator <(const node &x)const
    {
        return x.dis<dis;
    }
};

priority_queue <node> q;

inline void dijkstra()
{
    for(int i = 1; i <= n; ++i)dis[i] = 0x7fffffff;
    dis[s]=0;
    q.push((node){0,s});
    while(!q.empty())
    {
        node tmp=q.top();
        q.pop();
        int x = tmp.pos, d = tmp.dis;
        if( vis[x] )
            continue;
        vis[x] = 1;
        for( int i = head[x]; i; i = e[i].next )
        {
            int y = e[i].to;
            if( dis[y] > dis[x] + e[i].dis )
            {
                dis[y] = dis[x] + e[i].dis;
                if( !vis[y] )
                {
                    q.push( ( node ){dis[y], y} );
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    scanf("%d%d%d",&n,&m,&s);
    for( register int i = 0; i < m; ++i )
    {
        register int u, v, d;
        scanf( "%d%d%d", &u, &v, &d );
        addedge( u, v, d );
    }
    dijkstra();
    for( int i = 1; i <= n; i++ )
        printf( "%d ", dis[i] );
    return 0;
}
