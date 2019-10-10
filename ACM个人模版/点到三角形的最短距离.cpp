#include <bits/stdc++.h>
using namespace std;
#define eps 1e-8
inline double max(double a,double b)
{
    return a > b ? a : b;
}
inline double min(double a,double b)
{
    return a > b ? b : a;
}
struct point
{
    double x,y,z;
    point(){}
    point(double _x,double _y,double _z)
    {
        x=_x;
        y=_y;
        z=_z;
    }
};
double dist(point p1,point p2)
{
    double ans=sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z));
    return ans;
}
double point_line(point p,point a,point b)
{
    double t=((a.x-p.x)*(a.x-b.x)+(a.y-p.y)*(a.y-b.y)+(a.z-p.z)*(a.z-b.z))/((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
    point q;
    q.x=a.x+t*(b.x-a.x);
    q.y=a.y+t*(b.y-a.y);
    q.z=a.z+t*(b.z-a.z);
    if(t>=0&&t<=1)
        return dist(p,q);
    else if(t<0)
        return dist(p,a);
    else
        return dist(p,b);
}
void solve(double R,point l,point r,point m,point p)
{
    double A=(r.y-l.y)*(m.z-l.z)-(r.z-l.z)*(m.y-l.y);
    double B=(m.x-l.x)*(r.z-l.z)-(r.x-l.x)*(m.z-l.z);
    double C=(r.x-l.x)*(m.y-l.y)-(m.x-l.x)*(r.y-l.y);
    double t=(A*(l.x-p.x)+B*(l.y-p.y)+C*(l.z-p.z))/(A*A+B*B+C*C);
    point Q;
    Q.x=p.x+t*A;
    Q.y=p.y+t*B;
    Q.z=p.z+t*C;
    double dis1=Q.x*(r.y-m.y)-Q.y*(r.x-m.x)+(r.x*m.y-r.y*m.x);
    double dis2=l.x*(Q.y-m.y)-l.y*(Q.x-m.x)+(Q.x*m.y-Q.y*m.x);
    double dis3=l.x*(r.y-Q.y)-l.y*(r.x-Q.x)+(r.x*Q.y-Q.x*r.y);
    if((fabs((fabs(dis1)+fabs(dis2)+fabs(dis3))-fabs(A))<eps)||(fabs((fabs(dis1)+fabs(dis2)+fabs(dis3))-fabs(B))<eps)||(fabs((fabs(dis1)+fabs(dis2)+fabs(dis3))-fabs(C))<eps))
    {
        double ans1=dist(Q,p);
        printf("%.6lf\n",max(0,(ans1-R)));
        return ;
    }
    double ans1=(point_line(p,l,r)-R);
    double ans2=(point_line(p,l,m)-R);
    double ans3=(point_line(p,r,m)-R);
    double out=min(ans1,min(ans2,ans3));
    printf("%.6f\n",max(0,out));
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        point p,l,r,m;double R;
        scanf("%lf%lf%lf",&l.x,&l.y,&l.z);
        scanf("%lf%lf%lf",&r.x,&r.y,&r.z);
        scanf("%lf%lf%lf",&m.x,&m.y,&m.z);
        scanf("%lf%lf%lf",&p.x,&p.y,&p.z);
        scanf("%lf",&R);
        solve(R, l, r, m, p);
    }
    return 0;
}
