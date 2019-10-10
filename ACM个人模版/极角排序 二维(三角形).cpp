// 二维平面 给定n个点
// 有q次询问，每次询问给一个定点A，问有多少对B C 可以和A组成直角三角形
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii pair<int,int>
typedef long long ll; 
typedef unsigned long long ull;
const int maxn=2e3+10;
struct point
{
    ll x,y;
    point():x(0),y(0){}
    point(ll x,ll y):x(x),y(y){}
    point operator-(const point &b)const
    {
        return point(x-b.x,y-b.y);
    }
    point init()const
    {
        if(x<0||(x==0&&y<0)) return point(-x,-y);
        return *this;
    }
    bool operator<(const point &b)const
    {
        point p1=init(),p2=b.init();
        return p1.x*p2.y<p1.y*p2.x;
    }
}a[maxn],q[maxn];
int ans[maxn],n,m;
map<point,int>mp;
int main()
{
#ifdef LOCAL
    freopen("input.txt","r",stdin);
#endif
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=0;i<=m;i++)ans[i]=0;
        for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i].x,&a[i].y);
        for(int i=1;i<=m;i++)scanf("%lld%lld",&q[i].x,&q[i].y);
        for(int i=1;i<=m;i++)
        {
            mp.clear();
            for(int j=1;j<=n;j++)mp[a[j]-q[i]]++;
            for(int j=1;j<=n;j++)
            {
                point tmp=a[j]-q[i];tmp=point(-tmp.y,tmp.x);
                ans[i]+=mp[tmp];
            }
            ans[i]/=2;
        }
        for(int i=1;i<=n;i++)
        {
            mp.clear();
            for(int j=1;j<=n;j++) if(j!=i)mp[a[j]-a[i]]++;
            for(int j=1;j<=m;j++)
            {
                point tmp=q[j]-a[i];tmp=point(-tmp.y,tmp.x);
                ans[j]+=mp[tmp];
            }
        }
        for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
    }
    return 0;
}
