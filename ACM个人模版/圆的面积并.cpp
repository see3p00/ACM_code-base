// 圆的面积并
// 自适应simpson积分
#include <bits/stdc++.h>

const int maxn = 1000 + 5 ;
const double eps = 1e-13;

int n;

struct node
{
    double x,y,r;
}b[maxn],a[maxn];int cnt;
bool cmp1(node aa,node bb)
{
    return aa.r<bb.r;    
}
bool v[maxn];
double dis(int x,int y)
{
    return sqrt((b[x].x-b[y].x)*(b[x].x-b[y].x)+(b[x].y-b[y].y)*(b[x].y-b[y].y));
}
double lmin,rmax;
std::pair<double,double>q[maxn];
double mx(double x,double y)
{
    return x<y?y:x;
}
double f(double x)
{
    int top=0;double len=0;
    for(int i=1;i<=cnt;i++)
    {
        double xx=fabs(a[i].x-x);
        if(fabs(xx)<=a[i].r)
        {
            double ww=sqrt(a[i].r*a[i].r-xx*xx);
            q[++top].first=a[i].y-ww;
            q[top].second=a[i].y+ww;
        }
    }
    sort(q+1,q+top+1);len+=q[1].second-q[1].first;
    double rs=q[1].second;
    for(int i=2;i<=top;i++)if(q[i].second>rs)len+=q[i].second-mx(q[i].first,rs),rs=q[i].second;
    return len;
}
double simpson(double l,double mid,double r,double A,double B,double C)
{
    double s=((r-l)/6)*(A+4*B+C),lf=f((l+mid)/2),rf=f((mid+r)/2);
    double ls=((mid-l)/6)*(A+B+4*lf),rs=((r-mid)/6)*(B+C+4*rf);
    if(fabs(s-ls-rs)<=eps)return s;
    return simpson(l,(l+mid)/2,mid,A,lf,B)+simpson(mid,(r+mid)/2,r,B,rf,C);
}
int main()
{
	scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf%lf",&b[i].x,&b[i].y,&b[i].r);
        lmin=std::min(lmin,b[i].x-b[i].r);rmax=std::max(rmax,b[i].x+b[i].r);
    }
    std::sort(b+1,b+n+1,cmp1);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<i;j++)
        {
            if(dis(i,j)<=b[i].r-b[j].r)v[j]=1;
        }
    }
    for(int i=1;i<=n;i++)if(!v[i])a[++cnt]=b[i];
    printf("%.3f\n",simpson(lmin,(lmin+rmax)/2,rmax,0,f((lmin+rmax)/2),0));
	return 0;
}