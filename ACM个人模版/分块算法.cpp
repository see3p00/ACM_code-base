#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5e5+5;
ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,blo;
int v[500005],bl[500005],atag[500005];
void add(int a,int b,int c)
{
    for(int i=a;i<=min(bl[a]*blo,b);i++)
        v[i]+=c;
    if(bl[a]!=bl[b])
        for(int i=(bl[b]-1)*blo+1;i<=b;i++)
            v[i]+=c;
    for(int i=bl[a]+1;i<=bl[b]-1;i++)
        atag[i]+=c;
}
int main()
{
    n=read();int m=read();blo=sqrt(n);
    for(int i=1;i<=n;i++)v[i]=read();
    for(int i=1;i<=n;i++)bl[i]=(i-1)/blo+1;

    //for(int i=1;i<=n;i++)    cout<<bl[i]<<endl;
    while(m--)
    {
        int f=read();
        if(f==1)
        {
        	int a,b,c;
        	a=read();b=read();c=read();
            add(a,b,c);
        }
        if(f==2)
        {
        	int b;
        	b=read();
            printf("%d\n",v[b]+atag[bl[b]]);
        }
    }
    return 0;
}