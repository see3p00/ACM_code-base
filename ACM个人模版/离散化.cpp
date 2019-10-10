#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3f3f3f3f;
vector<ll> dz;

int Discrete(ll v)
{
	return lower_bound(dz.begin(), dz.end(), v) - dz.begin();
}
int main()
{
#ifdef LOCAL
	freopen("C:/input.txt", "r", stdin);
#endif
    	dz.clear();
    	dz.push_back(-INF); //绝对小
	sort(dz.begin(), dz.end());
	dz.erase(unique(dz.begin(), dz.end()), dz.end());

	return 0;
}
