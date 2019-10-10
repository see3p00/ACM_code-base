/*在一个文本串中查找子串是否存在或者组成字符的最近位置,
这个子串的特点是由文本串中的字符按照从左往右的顺序截取若干个得到的
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+5;
char s[maxn],str[maxn];
int nx[maxn][30];
int main()
{
#ifdef LOCAL
    freopen("input.txt","r",stdin);
#endif
    scanf("%s",s+1);
    int n=strlen(s+1);
    
    for(int i=n;i>=1;i--)
    {
    	for(int j=0;j<26;j++)
    		nx[i-1][j]=nx[i][j];
    	nx[i-1][s[i]-'a']=i;
    }
    int q;
    scanf("%d",&q);
    while(q--)
    {
    	scanf("%s",str);
    	int len=strlen(str);
    	bool flag=0;
    	for(int i=0,now=0;i<len;i++)
    	{
    		now=nx[now][str[i]-'a'];
    		if(!now) {flag=1;break;}
    	}
    	if(flag)puts("No");
    	else puts("Yes");
    }
    return 0;
}