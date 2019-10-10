//二维平面最近点对问题
// first: sort(p+1, p+1+n);   result: Divide(1, n)
struct point
{
    int x, y; //存点坐标
    bool operator <(const point& B)const { return x < B.x; }
}p[maxn];
int dis(point &A, point &B) { return (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y); }
point Q[100050];
int Divide(int l, int r)
{
    if(l == r) return 1e7;
    int mid = (l+r)>>1, d, tx = p[mid].x, tot = 0;
    d = min(Divide(l, mid), Divide(mid+1, r));
    for(int i = l, j = mid+1; (i <= mid || j <= r); i++)
    {
        while(j <= r && (p[i].y > p[j].y || i > mid)) Q[tot++] = p[j], j++; //归并按y排序
        if(abs(p[i].x - tx) < d && i <= mid)  //选择中间符合要求的点
        {
            for(int k = j-1; k > mid && j-k < 3; k--) d = min(d, dis(p[i], p[k]));
            for(int k = j; k <= r && k-j < 2; k++) d = min(d, dis(p[i], p[k]));
        }
        if(i <= mid) Q[tot++] = p[i];
    }
    for(int i = l, j = 0; i <= r; i++, j++) p[i] = Q[j];
    return d;
}