//  带修改莫队。
//  单点修改+区间不同数字出现的个数
//  
#include<bits/stdc++.h>
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii std::pair<int,int>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1e5+5;
char s[maxn];
int sz,cnt[1000010],a[maxn],Ans,ans[maxn],n,m;
struct Change
{
    int p,col;
}c[maxn];
struct Query
{
    int l,r,t,id;
    bool operator<(const Query&b)const
    {
        return l/sz==b.l/sz?(r/sz==b.r/sz?t<b.t:r<b.r):l<b.l;
        //return (l/sz)^(b.l/sz)?l<b.l:(l/sz)&1?r<b.r:r>b.r;
    }
}q[maxn];
void add(int x)
{
	cnt[x]++;
    if (cnt[x]==1)++Ans;
}
void del(int x)
{
	cnt[x]--;
    if(cnt[x]==0)--Ans;
}
void modify(int x,int ti)
{
    if(c[ti].p>=q[x].l&&c[ti].p<=q[x].r)
    {
        del(a[c[ti].p]);
        add(c[ti].col);
    }
    std::swap(a[c[ti].p],c[ti].col); 
}
int main()
{
#ifdef LOCAL
	freopen("input.txt","r",stdin);
#endif
	scanf("%s",s+1);n=strlen(s+1);sz=pow(n,0.66666);
	for(int i=1;s[i];i++)a[i]=s[i]-'0';
	scanf("%d",&m);
    int ccnt=0,qcnt=0;
    for(int i=1;i<=m;++i)
    {
    	int op,x;scanf("%d%d ",&op,&x);
        if(op==2)
        {
            ++qcnt;scanf("%d",&q[qcnt].r);q[qcnt].l=x;
            q[qcnt].t=ccnt;q[qcnt].id=qcnt;
        }
        else
        {
            ++ccnt;char tmp;scanf("%c",&tmp);
            c[ccnt].p=x;c[ccnt].col=tmp-'0';
        }
    }
    std::sort(q+1,q+qcnt+1);int l=1,r=0,now=0;Ans=0;
    for(int i=1;i<=qcnt;++i)
    {
        while(r<q[i].r)add(a[++r]);
        while(l>q[i].l)add(a[--l]);
        while(l<q[i].l)del(a[l++]);
        while(r>q[i].r)del(a[r--]);
        while(now<q[i].t)modify(i,++now);
        while(now>q[i].t)modify(i,now--);
        ans[q[i].id]=Ans;
    }
    for(int i=1;i<=qcnt;++i)printf("%d\n",ans[i]);
    return 0;
}