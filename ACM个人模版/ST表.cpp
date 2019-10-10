/* 一维 ST表
*/
int st1[maxn][25],st2[maxn][25];
int RMQ1(int l,int r)
{
    int k=0;
    while((1<<(k+1))<=r-l+1) k++;
    return min(st1[l][k],st1[r-(1<<k)+1][k]);
}

int RMQ2(int l,int r)
{
    int k=0;
    while((1<<(k+1))<=r-l+1) k++;
    return max(st2[l][k],st2[r-(1<<k)+1][k]);
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&st1[i][0]);
        st2[i][0]=st1[i][0];
    }
    for(int j=1;(1<<j)<=n;j++)
    {
        for(int i=1;i+(1<<j)-1<=n;i++)
        {
            st1[i][j]=min(st1[i][j-1],st1[i+(1<<(j-1))][j-1]);
            st2[i][j]=max(st2[i][j-1],st2[i+(1<<(j-1))][j-1]);
        }
    }
    while(q--)
    {
        int l,r;scanf("%d%d",&l,&r);
        printf("%d\n",RMQ2(l,r)-RMQ1(l,r));
    }
    return 0;
}
// 二维RMQ /st表
// 初始化 mx[][][0]=mi[][][0]=矩阵
int mymax(int a,int b,int c,int d){return max(max(max(a,b),c),d);}
int mymin(int a,int b,int c,int d){return min(min(min(a,b),c),d);}
int mx[maxn][maxn][11],mn[maxn][maxn][11];
int Log[maxn];
inline void RMQ()
{
    for(int k=1;k<=Log[min(a,b)];k++)
        for(int i=1;i+(1<<k)-1<=a;i++)
            for(int j=1;j+(1<<k)-1<=b;j++)
            {
                mx[i][j][k]=mymax(mx[i][j][k-1],mx[i+(1<<(k-1))][j][k-1],mx[i][j+(1<<(k-1))][k-1],mx[i+(1<<(k-1))][j+(1<<(k-1))][k-1]);
                mn[i][j][k]=mymin(mn[i][j][k-1],mn[i+(1<<(k-1))][j][k-1],mn[i][j+(1<<(k-1))][k-1],mn[i+(1<<(k-1))][j+(1<<(k-1))][k-1]);
            }
}
inline int querymax(int x1,int y1,int x2,int y2)
{
    int k=Log[n];
    return mymax(mx[x1][y1][k],mx[x2-(1<<k)+1][y1][k],mx[x1][y2-(1<<k)+1][k],mx[x2-(1<<k)+1][y2-(1<<k)+1][k]);
}
inline int querymin(int x1,int y1,int x2,int y2)
{
    int k=Log[n];
    return mymin(mn[x1][y1][k],mn[x2-(1<<k)+1][y1][k],mn[x1][y2-(1<<k)+1][k],mn[x2-(1<<k)+1][y2-(1<<k)+1][k]);
}
Log[1]=0;for(int i=2;i<=max(a,b);i++)Log[i]=Log[i/2]+1;
