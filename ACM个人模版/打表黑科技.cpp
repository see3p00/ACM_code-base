//如果打表发现某个数列: 差分有限次之后全为0  例如: 2017新疆乌鲁木齐ICPC现场赛D题 1,2,4,8,16,31,57,99,163,256,……
//【2018江苏南京ICPC现场赛也有这样的题目】
//那么可以使用以下黑科技计算出第k(1e18)项(对质数取模) (原理: 拉格朗日插值)
//预处理复杂度为线性, 每次计算复杂度为: O(传入项数个数)【同样也是线性】
//以下代码为内测版, 出锅了fold不背锅, 欢迎指出bug

------------------------下面是模板代码------------------------
typedef long long ll;

//mod一定要是质数
const int mod=1e9+7;

int pv[]={0,1,2,4,8,16,31,57}; //前几项, 前面无效值用0占位
const int st=1,ed=6;           //使用上面数组下标为[st,ed]的数据

ll fac[ed+5],inv[ed+5],facinv[ed+5];
ll pre[ed+5],saf[ed+5];

//预处理: fac[]阶乘, inv[]逆元, facinv[]阶乘逆元
//只需要main函数内调用一次!
void init()
{
    fac[0]=inv[0]=facinv[0]=1;
    fac[1]=inv[1]=facinv[1]=1;
    for(int i=2;i<ed+3;++i)
    {
        fac[i]=fac[i-1]*i%mod;
        inv[i]=mod-(mod/i*inv[mod%i]%mod);
        facinv[i]=facinv[i-1]*inv[i]%mod;
    }
}


//计算第x0项的值
//复杂度O(ed-st)
ll cal(ll x0)
{
    int n=ed-st;
    x0=((x0%mod)+mod)%mod;
    pre[0]=((x0-st)%mod+mod)%mod;
    saf[n]=((x0-st-n)%mod+mod)%mod;
    for(int i=1;i<=n;++i)
    {
        pre[i]=((pre[i-1]*(x0-st-i))%mod+mod)%mod;
        saf[n-i]=((saf[n-i+1]*(x0-st-n+i))%mod+mod)%mod;
    }
    ll res=0;
    for(int i=0;i<=n;++i)
    {
        ll fz=1;
        if(i!=0)fz=fz*pre[i-1]%mod;
        if(i!=n)fz=fz*saf[i+1]%mod;
        ll fm=facinv[i]*facinv[n-i]%mod;
        if((n-i)&1)fm=mod-fm;
        (res+=pv[i+st]*(fz*fm%mod)%mod)%=mod;
    }
    return res;
}