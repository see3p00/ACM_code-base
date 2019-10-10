struct Linear_Basis
{
    LL b[63],nb[63],tot;
    void init()
    {
        tot=0;
        memset(b,0,sizeof(b));
        memset(nb,0,sizeof(nb));
    }
    bool ins(LL x)
    {
        for(int i=62;i>=0;i--)
            if (x&(1LL<<i))
            {
                if (!b[i]) {b[i]=x;break;}
                x^=b[i];
            }
        return x>0;
    }
    LL Max(LL x)
    {
        LL res=x;
        for(int i=62;i>=0;i--)
            res=max(res,res^b[i]);
        return res;
    }
    LL Min(LL x)
    {
        LL res=x;
        for(int i=0;i<=62;i++)
            if (b[i]) res^=b[i];
        return res;
    }
    void rebuild()
    {
        for(int i=62;i>=0;i--)
            for(int j=i-1;j>=0;j--)
                if (b[i]&(1LL<<j)) b[i]^=b[j];
        for(int i=0;i<=62;i++)
            if (b[i]) nb[tot++]=b[i];
    }
    LL Kth_Max(LL k)
    {
        LL res=0;
        for(int i=62;i>=0;i--)
            if (k&(1LL<<i)) res^=nb[i];
        return res;
    }
} LB;


struct Linear_Basis {
    static const int L = 32;
    u32 a[L];
    Linear_Basis() {
        memset(a, 0, sizeof a);
    }
    u32& operator [](int x) {
        return a[x];
    }
    u32 operator [](int x) const {
        return a[x];
    }
    void insert(u32 x) {
        for (int i = L - 1; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (a[i]) x ^= a[i];
                else {
                    a[i] = x;
                    break;
                }
            }
        }
    }
    bool check(u32 x) {
        for (int i = L - 1; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (a[i]) x ^= a[i];
                else return 0;
            }
        }
        return 1;
    }
    //线性基求交
    friend Linear_Basis intersection(const Linear_Basis &a, const Linear_Basis &b) {
        Linear_Basis ans = Linear_Basis(), c = b, d = b;
        for (int i = 0; i <= L - 1; ++i) {
            u32 x = a[i];
            if (!x) continue;
            int j = i; u32 T = 0;
            for (; j >= 0; --j) {
                if ((x >> j) & 1) {
                    if (c[j]) {
                        x ^= c[j];
                        T ^= d[j];
                    } else {
                        break;
                    }
                }
            }
            if (!x) ans[i] = T;
            else {
                c[j] = x;
                d[j] = T;
            }
        }
        return ans;
    }
};
