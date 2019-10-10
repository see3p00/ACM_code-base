// 区间修改 区间最值
struct Segtree
{
    ll maxx[maxn<<2],lazy[maxn<<2];
    inline void pushdown(int o)
    {
        if(lazy[o])
        {
            maxx[o<<1]+=lazy[o];
            maxx[o<<1|1]+=lazy[o];
            lazy[o<<1]+=lazy[o];
            lazy[o<<1|1]+=lazy[o];
            lazy[o]=0;
        }
    }
    inline void build(int o,int l,int r)
    {
        maxx[o]=lazy[o]=0;
        if(l==r){maxx[o]=sum[idx[l]];return ;}
        int m=(l+r)>>1;
        build(o<<1,l,m);build(o<<1|1,m+1,r);
        maxx[o]=max(maxx[o<<1],maxx[o<<1|1]);
    }
    inline void update(int o,int l,int r,int ql,int qr,int val)
    {
        if(l>qr||r<ql)return;
        if(ql<=l&&r<=qr){maxx[o]+=val;lazy[o]+=val;return;}
        pushdown(o);
        int m=(l+r)>>1;
        update(o<<1,l,m,ql,qr,val);
        update(o<<1|1,m+1,r,ql,qr,val);
        maxx[o]=max(maxx[o<<1],maxx[o<<1|1]);
    }
    inline ll query(int o,int l,int r,int ql,int qr)
    {
        if(ql<=l&&r<=qr)return maxx[o];
        pushdown(o);
        int m=(l+r)>>1;
        ll ans=-1e18;
        if(ql<=m) ans=max(ans,query(o<<1,l,m,ql,qr));
        if(qr>m) ans=max(ans,query(o<<1|1,m+1,r,ql,qr));
        return ans;
    }
}st;
