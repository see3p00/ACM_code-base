// LCT维护最大生成树
//n个点，标号1~n，现在要生成一棵树，使树的总权值最大
//相邻两个点若连了边，那么其权值就是两个节点的最大公约数
#include<bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) static_cast<int>((x).size())
#define pii std::pair<int,int>
#define pll std::pair<ll,ll>
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1e5+10;
const int inf=0x3f3f3f3f;
struct edge { int cost, u, v, edge_id; };
edge min_edge(edge e1, edge e2) {
    int c1 = e1.cost, c2 = e2.cost;
    if(c1 >= c2) return e2;
    else return e1;
}
int res_node[maxn * 4], stk = 0;
struct Link_Cut {
    struct Node {
        int rev, fa, ch[2];
        edge anse, own;
    } node[maxn * 4];
    int q[maxn], loc[maxn], cnt;
    bool isroot(int x) { return node[node[x].fa].ch[1] != x && node[node[x].fa].ch[0] != x; }
    void update(int x) {
        edge el = node[node[x].ch[0]].anse;
        edge er = node[node[x].ch[1]].anse;
        node[x].anse = min_edge(node[x].own, min_edge(el, er));
    }
    bool get(int x) { return node[node[x].fa].ch[1] == x; }
    void push_down(int x) {
        if(!node[x].rev) return ;
        node[x].rev = 0; swap(node[x].ch[0], node[x].ch[1]);
        node[node[x].ch[0]].rev ^= 1;
        node[node[x].ch[1]].rev ^= 1;
    }
    void __rotate(int x) {
        int old = node[x].fa, oldf = node[old].fa, op = get(x);
        if(!isroot(old)) node[oldf].ch[node[oldf].ch[1] == old] = x;
        node[old].ch[op] = node[x].ch[op ^ 1];
        int rt = node[x].ch[op ^ 1]; node[rt].fa = old;
        node[x].ch[op ^ 1] = old; node[old].fa = x; node[x].fa = oldf;
        update(old); update(x);
    }
    void splay(int x) {
        int tp = 1; q[1] = x;
        for(int i = x; !isroot(i); i = node[i].fa) q[++tp] = node[i].fa;
        for(int i = tp; i; i--) push_down(q[i]);
        for(int u; !isroot(x); __rotate(x)) {
            u = node[x].fa;
            if(!isroot(u)) __rotate(get(x) == get(u) ? u : x);
        }
    }
    ///连接至根节点
    void access(int x) { int t = 0; while(x) { splay(x); node[x].ch[1] = t; update(x); t = x; x = node[x].fa; } }
    ///x成为根节点
    void makeroot(int x) { access(x); splay(x); node[x].rev ^= 1; }
    void link(int x, int y) { makeroot(x); node[x].fa = y; }
    void cut(int x, int y) { makeroot(x); access(y); splay(y); if(node[y].ch[0] == x) node[x].fa = node[y].ch[0] = 0; }
    int find_root(int x) { access(x); splay(x); while(node[x].ch[0]) x = node[x].ch[0]; return x; }
    void create_node(int x, int from, int to, int v) {
        cnt = res_node[stk];
        if(x < 1e5 + 1) loc[x] = cnt;
        node[cnt].rev = 0;
        node[cnt].ch[0] = node[cnt].ch[1] = node[cnt].fa = 0;
        node[cnt].anse.cost = node[cnt].own.cost = v;
        node[cnt].anse.u = node[cnt].own.u = from;
        node[cnt].anse.v = node[cnt].own.v = to;
        node[cnt].anse.edge_id = node[cnt].own.edge_id = cnt;
    }
    void add(int x, int y, int v) {
        int nd = res_node[stk - 1]; stk--; ///点代替边权
        create_node(maxn, x, y, v);
        link(loc[x], nd);
        link(nd, loc[y]);
    }
    void init() {
        node[0].anse.cost = inf; node[0].fa = 0;
        node[0].ch[0] = node[0].ch[1] = 0;
        node[0].rev = 0; node[0].own.cost = inf;
    }
    int solve(int x, vector<int> vec, int as) {
        stk--; create_node(x, 0, 0, inf);
        if(!vec.size()) { add(x, 1, 1); return as + 1; }
        int sz = vec.size(); add(x, vec[sz - 1], vec[sz - 1]); as += vec[sz - 1];
        if(vec.size() == 1) return as;
        for(int i = sz - 2; i >= 0; i--) {
            int v = vec[i];
            makeroot(loc[v]); access(loc[x]); splay(loc[x]);
            edge now = node[loc[x]].anse;
            if(now.cost >= v) continue ;
            int cx = loc[now.u], cy = loc[now.v], mid = now.edge_id;
            cut(cx, mid); cut(mid, cy); res_node[stk++] = mid;
            add(x, v, v); as += v - now.cost;
        }
        return as;
    }
 
}tree;
std::vector<int> G[maxn];
int ans[maxn],n;
void init()
{
	for(int i=2;i<maxn;i++)
	{
		for(int j=2;j*j<=i;j++)
		{
			if(i%j)continue;
			G[i].emplace_back(j);
			if(j!=i/j)G[i].emplace_back(i/j);
		}
		sort(ALL(G[i]));
	}
	for(int i=maxn*4-2;i>=1;i--) res_node[stk++]=i;
	ans[1]=0;stk--;tree.init();
    tree.create_node(1,0,0,inf);
    for(int i=2;i<=1e5+1;i++)ans[i]=tree.solve(i,G[i],ans[i-1]);
}
int main()
{
	init();
	while(scanf("%d",&n)!=EOF) printf("%d\n",ans[n]);
    return 0;
}