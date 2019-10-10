//区间第k大
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5+10;
int n,m,cnt,root[maxn],a[maxn];
std::vector<int> v;
struct node{int l,r,sum;}T[maxn*40];
int getid(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
void update(int l,int r,int &x,int y,int pos)
{
	T[++cnt]=T[y];T[cnt].sum++;x=cnt;
	if(l==r) return ;
	int m=(l+r)>>1;
	if(m>=pos)update(l,m,T[x].l,T[y].l,pos);
	else update(m+1,r,T[x].r,T[y].r,pos);
}
int query(int l,int r,int x,int y,int k)
{
	if(l==r) return l;
	int m=(l+r)>>1;int sum=T[T[y].l].sum-T[T[x].l].sum;
	if(sum>=k) return query(l,m,T[x].l,T[y].l,k);
	else return query(m+1,r,T[x].r,T[y].r,k-sum);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),v.push_back(a[i]);
	sort(v.begin(),v.end()),v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=1;i<=n;i++)update(1,n,root[i],root[i-1],getid(a[i]));
    while(m--)
    {
    	int x,y,k;scanf("%d%d%d",&x,&y,&k);
    	printf("%d\n",v[query(1,n,root[x-1],root[y],k)-1]);
    }
	return 0;
}
// 整体二分
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+5;
const int inf=1e9;
int a[maxn],c[maxn],ans[maxn],cnt,n,m;
struct node
{
    int l,r,k,op,id;
}q[maxn<<1],q1[maxn<<1],q2[maxn<<1];
// q 为所有操作
// 二分过程中，分到左边的操作存到q1中，分到右边的操作存到q2中
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return (f==1)?x:-x;
}
inline int lowbit(int x){return x&-x;}
inline void update(int i,int val)
{
    while(i<=n)
    {
        c[i]+=val;
        i+=lowbit(i);
    }
}
inline int query(int i)
{
    int res=0;
    while(i)
    {
        res+=c[i];
        i-=lowbit(i);
    }
    return res;
}
void solve(int l,int r,int L,int R)
{//当前值域范围为[l,r]，处理的操作的区间为[L,R]
    if(L>R)return ;
    if(l==r)
    {
        for(int i=L;i<=R;i++)if(q[i].op==2)ans[q[i].id]=l;
        return ;
    }
    int m=(l+r)>>1,cnt1=0,cnt2=0;
    //cnt1,cnt2  分别为分到左边，分到右边的操作数
    for(int i=L;i<=R;i++)
    {
        if(q[i].op==1)
        {  //是修改。更新树状数组 分类
            if(q[i].l<=m)q1[++cnt1]=q[i],update(q[i].id,q[i].r);
            else q2[++cnt2]=q[i];
        }
        else
        {   //是询问 进行分类
            int x=query(q[i].r)-query(q[i].l-1);
            if(q[i].k<=x)q1[++cnt1]=q[i];
            else q[i].k-=x,q2[++cnt2]=q[i];
        }
    }
    for(int i=1;i<=cnt1;i++)if(q1[i].op==1) update(q1[i].id,-q1[i].r); //清空树状数组
    for(int i=1;i<=cnt1;i++)q[L+i-1]=q1[i];
    for(int i=1;i<=cnt2;i++)q[L+i+cnt1-1]=q2[i];
    //将临时数组中的元素合并回原数组
    solve(l,m,L,L+cnt1-1);
    solve(m+1,r,L+cnt1,R);
}
int main()
{
#ifdef LOCAL
    freopen("input.txt","r",stdin);
#endif
    n=read();m=read();int l,r,k;
    for(int i=1;i<=n;i++)a[i]=read(),q[++cnt]=(node){a[i],1,0,1,i};
    for(int i=1;i<=m;i++)l=read(),r=read(),k=read(),q[++cnt]=(node){l,r,k,2,i};
    solve(-inf,inf,1,cnt);
    for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
    return 0;
}
//多次查询区间[l,r]内小于等于h的数的个数。
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii pair<int,int>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1e5+10;
std::vector<int> v;
int root[maxn],cnt,a[maxn],n,m;
struct node{int l,r,sum;}T[maxn*40];
inline int getid(int x){return lower_bound(ALL(v),x)-v.begin();}
inline void update(int l,int r,int &x,int y,int pos)
{
    T[++cnt]=T[y];T[cnt].sum++;x=cnt;
    if(l==r)return ;
    int m=(l+r)>>1;
    if(m>=pos) update(l,m,T[x].l,T[y].l,pos);
    else update(m+1,r,T[x].r,T[y].r,pos);
}
inline int query(int l,int r,int x,int y,int k)
{
    if(r<=k) return T[y].sum-T[x].sum;
    int m=(l+r)>>1;
    if(m>=k)return query(l,m,T[x].l,T[y].l,k);
    else return T[T[y].l].sum-T[T[x].l].sum+query(m+1,r,T[x].r,T[y].r,k);
}
int main()
{
#ifdef LOCAL
    freopen("input.txt","r",stdin);
#endif
    int t;scanf("%d",&t);
    for(int cc=1;cc<=t;cc++)
    {
        printf("Case %d:\n",cc);
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n+5;i++)root[i]=0;cnt=0;v.clear();
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),v.emplace_back(a[i]);
        v.emplace_back(-0x3f3f3f3f);
        sort(ALL(v));v.resize(distance(v.begin(),unique(ALL(v))));
        int sz=SZ(v);
        for(int i=1;i<=n;i++)update(1,sz-1,root[i],root[i-1],getid(a[i]));
        while(m--)
        {
            int l,r,k;scanf("%d%d%d",&l,&r,&k);l++,r++;
            int ans=upper_bound(ALL(v),k)-v.begin()-1;
            if(ans)printf("%d\n",query(1,sz-1,root[l-1],root[r],ans));
            else printf("0\n");
        }
    }
    return 0;
}

