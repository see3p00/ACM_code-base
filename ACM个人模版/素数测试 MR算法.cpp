#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int quickPow(int a,int b,int mod)
{
	int ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return ans;
}
bool millerRabbin(int n) {
  if (n < 3) return n == 2;
  int a = n - 1, b = 0;
  while (a % 2 == 0) a /= 2, ++b;
  int test_time=10;
  // test_time 为测试次数,建议设为不小于 8 的整数以保证正确率,但也不宜过大,否则会影响效率
  for (int i = 1, j; i <= test_time; ++i) {
    int x = rand() % (n - 2) + 2, v = quickPow(x, a, n);
    if (v == 1 || v == n - 1) continue;
    for (j = 0; j < b; ++j) {
      v = (long long)v * v % n;
      if (v == n - 1) break;
    }
    if (j >= b) return 0;
  }
  return 1;
}

int main()
{
    int n;cin>>n;
    cout<<millerRabbin(n)<<endl;
    return 0;
}