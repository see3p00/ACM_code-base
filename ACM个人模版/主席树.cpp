#include <bits/stdc++.h>

using namespace std;

const int maxn = 310000;

struct Seg {
    int l, r, sum;
} tr[maxn*40];

int cnt, n, m, root[maxn];

void update(int &x, int y, int l, int r, int pos, int val) {
    int pre = x;
    x = ++cnt; tr[x] = pre?tr[pre]:tr[y]; tr[x].sum += val;
    if(l == r) return ;
    int m = (l + r) >> 1;
    if(pos <= m) update(tr[x].l, tr[y].l, l, m, pos, val);
    else update(tr[x].r, tr[y].r, m+1, r, pos, val);
}

int ask(int x, int y, int l, int r, int k) {
    if(tr[y].sum - tr[x].sum <= k) return -1;
    int m = (l + r) >> 1;
    if(l == r) return l;
    int ans = ask(tr[x].l, tr[y].l, l, m, k);
    if(ans == -1) return ask(tr[x].r, tr[y].r, m+1, r, k);
    else return ans;
}

int main() {
    scanf("%d", &n);
    int q;
    scanf("%d", &q);
    for(int i = 1; i <= n; i++)
    {
        int v;
        scanf("%d", &v);
        update(root[i], root[i-1], 1, n, v, 1);
    }
    while(q--)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        int cnt = (r-l+1)/k;
        printf("%d\n", ask(root[l-1], root[r], 1, n, cnt));
    }
    return 0;
}
