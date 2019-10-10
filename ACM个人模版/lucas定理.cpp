ll pow2(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
ll inv(ll x){return pow2(x,mod-2);}
ll fac[maxn],invfac[maxn];
void init(int n)
{
	ll i;
	fac[0]=1;
	for(i=1;i<n;i++) fac[i]=fac[i-1]*i%mod;
	invfac[n-1]=inv(fac[n-1]);
	for(i=n-2;~i;i--) invfac[i]=invfac[i+1]*(i+1)%mod;
}
ll C(int n,int m)
{
	if(m>n||m<0||n<0) return 0;
	return fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}
//C(n,m) n,m<=1e18 p<=1e5
//p must be a prime number
ll Lucas(ll n,ll m,ll p)
{
	if(m==0) return 1;
	return C(n%p,m%p)*Lucas(n/p,m/p,p)%p;
}