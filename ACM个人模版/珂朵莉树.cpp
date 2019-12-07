#define IT std::set<node>::iterator

struct node
{
    int l,r;
    mutable int val;
    node(int L, int R=-1, int V=0):l(L), r(R), val(V) {}
    bool operator<(const node& o) const
    {
        return l < o.l;
    }
};
std::set<node> s;
//split(pos)操作是指将原来含有pos位置的节点分成两部分：[l,pos−1]和[pos,r]
inline IT split(int pos)
{
    IT it = s.lower_bound(node(pos));
    if (it != s.end() && it->l == pos) return it;
    --it;
    int L = it->l, R = it->r;
    int V = it->val;
    s.erase(it);
    s.insert(node(L, pos-1, V));
    return s.insert(node(pos, R, V)).first;
    //这里利用了pair<iterator,bool> insert (const value_type& val)的返回值
}
//assign操作迅速减小set的规模
inline void assign_val(int l, int r, int val)//区间全部赋值
{
    IT itr = split(r+1), itl = split(l);
    s.erase(itl, itr);
    //void erase (iterator first, iterator last)可删除[first,last)区间
    s.insert(node(l, r, val));
}
inline int query(int pos)
{
    IT it=s.lower_bound(node(pos));//找最靠近pos的l
    if(it!=s.end()&&it->l==pos)//pos就是一个区间的l
        return it->val;
    it--;
    int v=it->val;
    return v;
}
inline void add(int l,int r,int val)//区间加
{
	IT itr=split(r+1),itl=split(l);
	for(;itl!=itr;++itl)
		itl->val+=val;
	return;
}
inline int querysum(int l,int r)//区间求和
{
    IT itr = split(r+1),itl = split(l);
    int res=0;
    for(;itl!=itr;itl++)
        res+=(itl->r-itl->l+1)*itl->val ;
    return res;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        s.insert((node){i,i,a[i]});
    s.insert((node){n+1,n+1,0});
}
