//插入x数
//删除x数(若有多个相同的数，因只删除一个)
//查询x数的排名(排名定义为比当前数小的数的个数+1.若有多个相同的数，因输出最小的排名)
//查询排名为x的数
//求x的前驱(前驱定义为小于x，且最大的数)
//求x的后继(后继定义为大于x，且最小的数)
#pragma GCC optimize(3, "Ofast", "inline")
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii std::pair<int,int>
#define pll std::pair<ll,ll>
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 1e5+5;
struct Node
{
    int l,r;
    int val;
    int height,size;
}avl[maxn];         //内存池，老生常谈
int cnt,root;
inline void newnode(int &now,int val)   //新建结点，老生常谈
{
    avl[now=++cnt].val=val;
    avl[cnt].size=1;
}
inline void update(int now)     //更新节点信息
{
    avl[now].size=avl[avl[now].l].size+avl[avl[now].r].size+1;
    avl[now].height=std::max(avl[avl[now].l].height,avl[avl[now].r].height)+1;
}
inline int factor(int now)      //获取BF
{
    return avl[avl[now].l].height-avl[avl[now].r].height;
}
inline void lrotate(int &now)   //左旋
{
    int r = avl[now].r;
    avl[now].r = avl[r].l;
    avl[r].l = now;
    now = r;
    update(avl[now].l),update(now);
}
inline void rrotate(int &now)   //右旋
{
    int l = avl[now].l;
    avl[now].l = avl[l].r;
    avl[l].r = now;
    now = l;
    update(avl[now].r),update(now);
}
inline void check(int &now)//检查是否需要旋转，并且更新节点信息
{
    int nf = factor(now);
    if(nf>1)
    {
        int lf = factor(avl[now].l);
        if(lf>0) rrotate(now);                      //LL
        else lrotate(avl[now].l),rrotate(now);      //LR
    }
    else if(nf<-1)
    {
        int rf = factor(avl[now].r);
        if(rf<0) lrotate(now);                      //RR
        else rrotate(avl[now].r),lrotate(now);      //RL
    }
    else if(now) update(now);//如果平衡并且非空，那就直接更新
}
void ins(int &now,int val)
{
    if(!now) newnode(now,val);      //到了一个不存在的点，新建它
    else if(val<avl[now].val) ins(avl[now].l,val);  //小的往左
    else ins(avl[now].r,val);                       //大的往右
    check(now);                     //递归回溯检查平衡
}
int find(int &now,int fa)
{
    int ret;
    if(!avl[now].l)     //找到了要的后继
    {
        ret = now;      //返回值就是你了
        avl[fa].l=avl[now].r;//父亲的左儿改成该点的右儿
    }
    else                //没找到
    {
        ret = find(avl[now].l,now); //返回值是继续找
        check(now);     //递归回溯过程中检查是否需要调整
    }
    return ret;         //把找到的结点编号返回
}
void del(int &now,int val)
{
    if(val==avl[now].val)   //要删除的结点
    {
        int l = avl[now].l,r = avl[now].r;  //temp
        if(!l||!r) now=l+r;  //如果无儿或单儿，很简单
        else 
        {
            now = find(r,r);    //找后继，替换当前
            if(now!=r)          //如果后继不是原来的右儿
                avl[now].r=r;   //右儿改成原来的右儿
            avl[now].l=l;       //左儿连上
        }
    }
    else if(val<avl[now].val) del(avl[now].l,val);
    else del(avl[now].r,val);
    check(now);                 //递归回溯检查
}
void ldr(int now)               //调试用的中序遍历
{
    if(!now) return;
    ldr(avl[now].l);
    printf("%d\n",avl[now].val);
    ldr(avl[now].r);
}
int getrank(int val)            //以下与替罪羊树同
{
    int now=root,rank=1;
    while(now)
    {
        if(val<=avl[now].val)
            now=avl[now].l;
        else
        {
            rank+=avl[avl[now].l].size+1;
            now=avl[now].r;
        }
    }
    return rank;
}
int getnum(int rank)
{
    int now=root;
    while(now)
    {
        if(avl[avl[now].l].size+1==rank)
            break;
        else if(avl[avl[now].l].size>=rank)
            now=avl[now].l;
        else 
        {
            rank-=avl[avl[now].l].size+1;
            now=avl[now].r;
        }
    }
    return avl[now].val;
}
int main()
{
#ifdef LOCAL
	//freopen("input.txt","r",stdin);
#endif
	int t;scanf("%d",&t);
	while(t--)
	{
		int op,x;scanf("%d%d",&op,&x);
		switch(op)
        {
        case 1:
            ins(root,x);
            break;
        case 2:
            del(root,x);
            break;
        case 3:
            printf("%d\n",getrank(x));
            break;
        case 4:
            printf("%d\n",getnum(x));
            break;
        case 5:
            printf("%d\n",getnum(getrank(x)-1));
            break;
        case 6:
            printf("%d\n",getnum(getrank(x+1)));
            break;
        }
	}
    return 0;
}