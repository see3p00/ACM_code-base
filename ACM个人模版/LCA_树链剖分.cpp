// 最近公共祖先   树链剖分

#include<cstdio>
#include<iostream>
using namespace std;
struct edge{
    int to,ne;
}e[1000005];
int n,m,s,ecnt,head[500005],dep[500005],siz[500005],son[500005],top[500005],f[500005];
void add(int x,int y)
{
    e[++ecnt].to=y;
    e[ecnt].ne=head[x];
    head[x]=ecnt;
}
void dfs1(int x)
{
    siz[x]=1;
    dep[x]=dep[f[x]]+1;
    for(int i=head[x];i;i=e[i].ne)
    {
        int dd=e[i].to;
        if(dd==f[x])continue;
        f[dd]=x;
        dfs1(dd);
        siz[x]+=siz[dd];
        if(!son[x]||siz[son[x]]<siz[dd])
            son[x]=dd;
    }
}
void dfs2(int x,int tv)
{
    top[x]=tv;
    if(son[x])dfs2(son[x],tv);
    for(int i=head[x];i;i=e[i].ne)
    {
        int dd=e[i].to;
        if(dd==f[x]||dd==son[x])continue;
        dfs2(dd,dd);
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    dfs1(s);
    dfs2(s,s);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        while(top[x]!=top[y])
        {
            if(dep[top[x]]>=dep[top[y]])x=f[top[x]];
            else y=f[top[y]];
        }
        printf("%d\n",dep[x]<dep[y]?x:y);
    }
}
