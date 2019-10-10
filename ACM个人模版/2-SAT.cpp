struct TwoSat {
    static const int MAX_NODE = 1000;
    vector<int> G[MAX_NODE];
    int n, stk[MAX_NODE], sz;
    bool mark[MAX_NODE];

    void init(int _n) {
        n = _n;
        for (int i = 0; i < n * 2; ++i) G[i].clear();
        memset(mark, 0, sizeof(mark));
    }

    void addClause(int x, int xVal, int y, int yVal) {
        x = x * 2 + xVal, y = y * 2 + yVal;
        G[x ^ 1].push_back(y);
        G[y ^ 1].push_back(x);
    }

    bool dfs(int x) {
        if (mark[x ^ 1]) return false;
        if (mark[x]) return true;
        stk[sz++] = x;
        mark[x] = true;
        for (int i = 0; i < (int)G[x].size(); ++i)
            if (!dfs(G[x][i])) return false;
        return true;
    }

    bool solve() {
        for (int i = 0; i < n * 2; i += 2)
            if (!mark[i] && !mark[i ^ 1]) {
                sz = 0;
                if (!dfs(i)) {
                    while (sz > 0) mark[stk[--sz]] = false;
                    if (!dfs(i ^ 1)) return false;
                }
            }

        return true;
    }
};