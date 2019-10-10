int fa[maxn];

int find(int x)
{
    if(x!=fa[x]) fa[x]=find(fa[x]);
    return fa[x];
}
void Union(int x,int y)
{
  x=find(x);
  y=find(y);
  if(x==y) return ;
  fa[x]=y;
}