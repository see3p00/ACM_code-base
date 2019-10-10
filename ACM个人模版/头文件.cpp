/*Author wzazzy*/
#pragma GCC optimize(2)
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<iostream>
#include<sstream>
#include<set>
#include<map>
#include<stack>
#include<list>
#include<queue>
#include<bitset>
#include<vector>
#include<utility>
#include<limits.h>
#include<assert.h>
#include<iomanip>
#include<unordered_map>
#define SZ(X) ((int)(X).size())
#define ALL(X) (X).begin(), (X).end()
#define REP(I, N) for (int I = 0; I < (N); ++I)
#define REPP(I, A, B) for (int I = (A); I < (B); ++I)
#define FOR(I, A, B) for (int I = (A); I <= (B); ++I)
#define FORS(I, S) for (int I = 0; S[I]; ++I)
#define RS(X) scanf("%s", (X))
#define SORT_UNIQUE(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#ifdef LOCAL
#define debug(x) cout << "[" << __func__ << ": " #x " = " << (x) << "]\n"
#define TIME cerr << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl,0;
#else
#define debug(x) ;
#define TIME ;
#endif
#define GET_POS(c,x) (lower_bound(c.begin(),c.end(),x)-c.begin())+1
#define CASET int ___T; scanf("%d", &___T); for(int cs=1;cs<=___T;cs++)
#define MP make_pair
#define PB emplace_back
#define MEM(X,Y) memset((X), (Y), sizeof((X)))
#define F first
#define S second
using namespace std;
typedef  unsigned int u32;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPII;
typedef pair<LL,LL> PLL;
typedef vector<PLL> VPLL;
const int MOD =1e9+7;
const int inf=0x3f3f3f3f;
LL gcd(LL a,LL b){return b==0?a:gcd(b,a%b);}
void ADD(LL& x,LL v){x=(x+v)%MOD;if(x<0)x+=MOD;}
//*******************************************************************//

#ifdef LOCAL
freopen("input.txt","r",stdin);
#endif
