//区间最值 RMQ

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), _##i##_ = (r); i < _##i##_; ++i)
#define rof(i, l, r) for (int i = (l)-1, _##i##_ = (r); i >= _##i##_; --i)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) static_cast<int>((x).size())
typedef long long ll;
typedef std::pair<int, int> pii;
template <typename T>
inline bool chkMin(T &a, const T &b) {
  return a > b ? a = b, 1 : 0;
}
template <typename T>
inline bool chkMax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

const int MAXN = 1e5 + 5;

struct PlusMinusOneRMQ {
  const static int M = 8;
  int blocklen, block, Minv[MAXN], F[MAXN / M * 2 + 5][M << 1], T[MAXN],
      f[1 << M][M][M], S[MAXN];
  void init(int n) {
    blocklen = std::max(1, (int)(log(n * 1.0) / log(2.0)) / 2);
    block = n / blocklen + (n % blocklen > 0);
    int total = 1 << (blocklen - 1);
    for (int i = 0; i < total; i++) {
      for (int l = 0; l < blocklen; l++) {
        f[i][l][l] = l;
        int now = 0, minv = 0;
        for (int r = l + 1; r < blocklen; r++) {
          f[i][l][r] = f[i][l][r - 1];
          if ((1 << (r - 1)) & i) {
            now++;
          } else {
            now--;
            if (now < minv) {
              minv = now;
              f[i][l][r] = r;
            }
          }
        }
      }
    }
    T[1] = 0;
    for (int i = 2; i < MAXN; i++) {
      T[i] = T[i - 1];
      if (!(i & (i - 1))) {
        T[i]++;
      }
    }
  }
  void initmin(int a[], int n) {
    for (int i = 0; i < n; i++) {
      if (i % blocklen == 0) {
        Minv[i / blocklen] = i;
        S[i / blocklen] = 0;
      } else {
        if (a[i] < a[Minv[i / blocklen]]) {
          Minv[i / blocklen] = i;
        }
        if (a[i] > a[i - 1]) {
          S[i / blocklen] |= 1 << (i % blocklen - 1);
        }
      }
    }
    for (int i = 0; i < block; i++) {
      F[i][0] = Minv[i];
    }
    for (int j = 1; (1 << j) <= block; j++) {
      for (int i = 0; i + (1 << j) - 1 < block; i++) {
        int b1 = F[i][j - 1], b2 = F[i + (1 << (j - 1))][j - 1];
        F[i][j] = a[b1] < a[b2] ? b1 : b2;
      }
    }
  }
  int querymin(int a[], int L, int R) {
    int idl = L / blocklen, idr = R / blocklen;
    if (idl == idr)
      return idl * blocklen + f[S[idl]][L % blocklen][R % blocklen];
    else {
      int b1 = idl * blocklen + f[S[idl]][L % blocklen][blocklen - 1];
      int b2 = idr * blocklen + f[S[idr]][0][R % blocklen];
      int buf = a[b1] < a[b2] ? b1 : b2;
      int c = T[idr - idl - 1];
      if (idr - idl - 1) {
        int b1 = F[idl + 1][c];
        int b2 = F[idr - 1 - (1 << c) + 1][c];
        int b = a[b1] < a[b2] ? b1 : b2;
        return a[buf] < a[b] ? buf : b;
      }
      return buf;
    }
  }
};
struct CartesianTree {
 private:
  struct Node {
    int key, value, l, r;
    Node(int key, int value) {
      this->key = key;
      this->value = value;
      l = r = 0;
    }
    Node() {}
  };
  Node tree[MAXN];
  int sz;
  int S[MAXN], top;

 public:
  void build(int a[], int n) {
    top = 0;
    tree[0] = Node(-1, INT_MAX);
    S[top++] = 0;
    sz = 0;
    for (int i = 0; i < n; i++) {
      tree[++sz] = Node(i, a[i]);
      int last = 0;
      while (tree[S[top - 1]].value <= tree[sz].value) {
        last = S[top - 1];
        top--;
      }
      tree[sz].l = last;
      tree[S[top - 1]].r = sz;
      S[top++] = sz;
    }
  }
  Node &operator[](const int x) { return tree[x]; }
};

class stdRMQ {
 public:
  void work(int a[], int n) {
    ct.build(a, n);
    dfs_clock = 0;
    dfs(0, 0);
    rmq.init(dfs_clock);
    rmq.initmin(depseq, dfs_clock);
  }
  int query(int L, int R) {
    int cl = clk[L], cr = clk[R];
    if (cl > cr) {
      std::swap(cl, cr);
    }
    return Val[rmq.querymin(depseq, cl, cr)];
  }

 private:
  CartesianTree ct;
  PlusMinusOneRMQ rmq;
  int dfs_clock, clk[MAXN], Val[MAXN << 1], depseq[MAXN << 1];
  void dfs(int rt, int d) {
    clk[ct[rt].key] = dfs_clock;
    depseq[dfs_clock] = d;
    Val[dfs_clock++] = ct[rt].value;
    if (ct[rt].l) {
      dfs(ct[rt].l, d + 1);
      depseq[dfs_clock] = d;
      Val[dfs_clock++] = ct[rt].value;
    }
    if (ct[rt].r) {
      dfs(ct[rt].r, d + 1);
      depseq[dfs_clock] = d;
      Val[dfs_clock++] = ct[rt].value;
    }
  }
} doit;

int A[MAXN];

int main() {
  int n, m, l, r;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &A[i]);
  }
  doit.work(A, n);
  while (m--) {
    scanf("%d%d", &l, &r);
    printf("%d\n", doit.query(l - 1, r - 1));
  }
  return 0;
}