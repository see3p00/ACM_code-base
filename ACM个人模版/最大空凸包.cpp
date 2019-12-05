// 最大空凸包 hdu 6219  O(n^3)
// /给一些点，求出一个最大的空凸包，这个凸包里没有任何给定点且要求这个凸包面积最大
#include <bits/stdc++.h>

const int maxn = 100 + 5 ;

typedef int db;

struct Point
{
    /*点类*/
    db x,y;
    Point(){}
    Point(db _x,db _y):x(_x),y(_y){}
    Point operator + (const Point &t)const
    {
        return Point(x+t.x,y+t.y);
    }
    Point operator - (const Point &t)const
    {
        return Point(x-t.x,y-t.y);
    }
    db operator * (const Point &t)const
    {
        return x*t.y-y*t.x;
    }
    db len()const
    {
        return x*x+y*y;
    }
    bool operator < (const Point &t) const
    {
        if((*this)*t!=0) return (*this)*t>0;
        return len()<t.len();
    }
}p[maxn+5],a[maxn+5];

int dp[maxn][maxn],sum[maxn][maxn],ans,n,m;

inline void work(int n)
{
	memset(dp,0,sizeof(dp));
    memset(sum,0,sizeof(sum));
    for(int i=2;i<=n;i++)
    {
        int j=i-1;
        while(j>=1&&a[i]*a[j]==0) --j;
        bool flag=0;
        if(j==i-1) flag=1;
        while(j>=1)
        {
            int k=j-1;
            int res=a[j]*a[i];
            while(k>=1&&(a[j]-a[i])*(a[k]-a[j])>0) --k;
            if(k) res+=sum[j][k];
            if(flag) dp[i][j]=res;
            ans=std::max(ans,res);
            j=k;
        }
        sum[i][1]=dp[i][1];
        for(int j=2;j<i;++j) sum[i][j]=std::max(dp[i][j],sum[i][j-1]);
    }
}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&p[i].x,&p[i].y);
		for(int i=1;i<=n;++i)
        {
            m=0;
            for(int j=1;j<=n;++j)
            	if(p[j].y>p[i].y||(p[i].y==p[j].y&&p[j].x>=p[i].x))
            		a[++m]=p[j]-p[i];
            std::sort(a+1,a+m+1);
            work(m);
        }
        printf("%.1f\n",1.0*ans/2);
	}
	return 0;
}