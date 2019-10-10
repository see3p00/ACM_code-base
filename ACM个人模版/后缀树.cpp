#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAX = 3000000 + 10;
const int ALPHA = 30;

int n;
char str[MAX];
int pt[1 << 15];

struct Node;

struct Edge
{
	int l, r;
	Node *t;
	Edge() { t = 0; }

	void modify(int ll, int rr, Node *next)
	{
		l = ll;
		r = rr;
		t = next;
	}
} eg[MAX];
int tote;

struct Node
{
	Edge *e[ALPHA];
	Node *slink;
	int dep, exi, time;
	Node()
	{
		slink = 0;
		memset(e, 0, sizeof e);
		dep = exi = 0;
	}

	void add(int num, int l, int r, Node *next)
	{
		e[num] = eg + (tote++);
		e[num]->modify(l, r, next);
		exi |= (1 << num);
	}

	void modify(int num, int l, int r, Node *next)
	{
		e[num]->modify(l, r, next);
	}
} * Root, *Seed, p[MAX];
int tot;

void PreSuffixTree()
{
	tot = 0;
	Seed = p + (tot++);
	Root = p + (tot++);
	Root->slink = Seed;
	for (int i = 0; i <= 26; ++i)
		Seed->add(i, 0, 0, Root);
}

Edge *q[MAX];
int numq;

int getnum(int u)
{
	if (u > (1 << 14))
		return pt[u >> 14] + 14;
	else
		return pt[u];
}

void show(Node *u)
{
	int tot = 0, j = u->exi, i = getnum(j & (-j));
	for (j = u->exi; j; j -= (j & (-j)))
	{
		i = getnum(j & (-j));
		if (u->e[i])
		{
			++tot;
			q[++numq] = u->e[i];
			show(u->e[i]->t);
			--numq;
		}
	}
	if (!tot)
	{
		int i;
		for (i = 1; i <= numq; ++i)
			printf("%d %d ", q[i]->l, q[i]->r);
		printf("\n");
	}
}

void BuildSuffixTree(char *str, int n)
{
	PreSuffixTree();
	int i, k = 1, id, tnum;
	Node *now = Root;
	for (i = 0; i <= 14; ++i)
		pt[1 << i] = i;
	for (i = 1; i <= n; ++i)
	{
		id = str[i];
		Node *old = Root, *np;
		while (1)
		{
			while (k < i)
			{
				tnum = str[k];
				Edge *ep = now->e[tnum];
				if (k + ep->r - ep->l + 1 <= i)
				{
					k += ep->r - ep->l + 1;
					now = ep->t;
				}
				else
					break;
			}
			if (k < i)
			{
				tnum = str[k];
				Edge *ep = now->e[tnum];
				if (str[i - k + ep->l] == id)
					break;
				else
				{
					np = p + (tot++);
					np->dep = i - 1 - (k - 1) + now->dep;
					np->add(str[i - k + ep->l], i - k + ep->l, ep->r, ep->t);
					now->modify(tnum, ep->l, i - k - 1 + ep->l, np);
				}
			}
			else if (now->e[id] != NULL)
				break;
			else
				np = now;

			Node *nl = p + (tot++);
			np->add(id, i, n, nl);
			nl->dep = np->dep + n - i + 1;

			if (old != Root)
				old->slink = np;
			old = np;
			now = now->slink;
		}
		if (old != Root)
			old->slink = now;
	}
}

int f[MAX], g[MAX], first, last;
Node *que[MAX];

void calc()
{
	int i, j, k;
	Node *u;
	que[first = last = 1] = Root;
	++last;
	while (first < last)
	{
		u = que[first++];
		for (j = u->exi, i = getnum(j & (-j)); j; j -= (j & (-j)), i = getnum(j & (-j)))
			que[last++] = u->e[i]->t;
	}
	for (k = last - 1; k >= 2; --k)
	{
		u = que[k];
		if (u->exi == 0)
			u->time++;
		for (j = u->exi, i = getnum(j & (-j)); j; j -= (j & (-j)), i = getnum(j & (-j)))
			u->time += u->e[i]->t->time;
		f[u->dep] = max(f[u->dep], u->time);
	}
	g[n] = n;
	for (i = n - 1; i >= 1; --i)
	{
		f[i] = max(f[i], f[i + 1]);
		if (f[i] == f[i + 1])
			g[i] = g[i + 1];
		else
			g[i] = i;
	}
}

int main()
{
#ifdef LOCAL
	//freopen("/Users/apple/desktop/input.txt","r",stdin);
#endif
	int i, Q;
	scanf("%d%d", &n, &Q);
	scanf("%s", str + 1);
	str[n + 1] = 'z' + 1;
	++n;
	for (i = 1; i <= n; ++i)
		str[i] -= 'a';
	BuildSuffixTree(str, n);
	calc();
	for (i = 1; i <= Q; ++i)
	{
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d %d\n", f[l], min(g[l], r));
	}
	return 0;
}