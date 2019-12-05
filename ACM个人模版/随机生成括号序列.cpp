#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5 ;

string solve()
{
	string res, stk;
	int n = 30;
	while (n--)
	{
		char ch = "()[]{}"[rand() % 6];
		if (ch == '(' || ch == '[' || ch == '{')
			res += ch, stk += ch;
		else
		{
			if (ch == ')' && (stk == "" || stk.back() != '('))
				return "";
			if (ch == ']' && (stk == "" || stk.back() != '['))
				return "";
			if (ch == '}' && (stk == "" || stk.back() != '{'))
				return "";
			res += ch, stk.pop_back();
		}
	}
	if (stk != "")
		return "";
	return res;
}
int main()
{
#ifdef LOCAL
	//freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
#endif
	srand(time(NULL));
	string str;
	while (str.size() < 30)
		str += solve();
	cout << str << endl;

	return 0;
}