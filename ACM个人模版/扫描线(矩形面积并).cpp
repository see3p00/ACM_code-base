//扫描线: 求 n 个矩形的面积并。
#pragma GCC optimize(3, "Ofast", "inline")
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii std::pair<int,int>
#define pll std::pair<ll,ll>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=2e5+5;  //因为一个矩形有两边所以数据范围要乘2
int v[maxn],n;//存放所有横边的y坐标
struct L
{
	int x;//竖边的x坐标
	int y1,y2;//竖边的y坐标，y1较小
	int state;//是左边还是右边
	bool operator<(const L &oth)const //排序时使用x坐标排序
	{
		return x<oth.x;
	}
}line[maxn];
struct Node         //线段树
{
    int l,r;        //结点区间左右
    int cover;      //被覆盖次数
    long long len;  //区间真实长度
}sgt[maxn<<3];      //注意这个大小
inline int ls(int k) { return k<<1; }   //取左儿子
inline int rs(int k) { return k<<1|1; } //取右儿子
inline void pushup(int k)       //与普通线段树的区别
{
    if(sgt[k].cover) sgt[k].len=sgt[k].r-sgt[k].l;
    else sgt[k].len=sgt[ls(k)].len+sgt[rs(k)].len;
}
void build(int l,int r,int k=1)
{
    sgt[k].l=v[l],sgt[k].r=v[r];//与普通线段树的区别
    if(r-l<=1) return;          //与普通线段树的区别
    int m = (l+r)>>1;
    build(l,m,ls(k));
    build(m,r,rs(k));
}
void update(int x,int y,int z,int k=1)
{
    int l=sgt[k].l,r=sgt[k].r;
    if(x<=l&&y>=r)
    {
        sgt[k].cover+=z;
        pushup(k);              //与普通线段树的区别
        return;
    }
    if(x<sgt[ls(k)].r) update(x,y,z,ls(k)); //与普通线段树的区别
    if(y>sgt[rs(k)].l) update(x,y,z,rs(k)); //与普通线段树的区别
    pushup(k);
}
int main()
{
#ifdef LOCAL
	freopen("input.txt","r",stdin);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)  //读入数据，位置无所谓，待会要排序
	{
		int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
		v[i]=b,v[n+i]=d;
		line[i]={a,b,d,1},line[n+i]={c,b,d,-1};
	}
	sort(v+1,v+1+(n<<1));
	sort(line+1,line+1+(n<<1));
	build(1,n<<1);
	ll ans=0;
	for(int i=1;i<=(n<<1);i++)
	{
		ans+=sgt[1].len*(line[i].x-line[i-1].x);//注意两语句顺序
		update(line[i].y1,line[i].y2,line[i].state);
	}
	printf("%lld\n",ans);
    return 0;
}