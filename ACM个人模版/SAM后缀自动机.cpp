//。求一个字符串有多少个不同的子串

 //SAM。 后缀自动机 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
char s[N];int len;
struct SAM{
    int last,cnt,nxt[N*2][26],fa[N*2],l[N*2];
    ll ans;
    void init(){
        last = cnt=1;
        memset(nxt[1],0,sizeof nxt[1]);
        fa[1]=0;ans=0;l[1]=0;
    }
    int inline newnode(){
        ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        fa[cnt]=l[cnt]=0;
        return cnt;
    }
    void add(int c){
        int p = last;
        int np = newnode();
        last = np;
        l[np] = l[p]+1;
        while (p&&!nxt[p][c]){
            nxt[p][c]=np;
            p = fa[p];
        }
        if (!p){
            fa[np]=1;
        }else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1){
                fa[np] = q;
            }else{
                int nq = newnode();
                memcpy(nxt[nq],nxt[q],sizeof nxt[q]);
                fa[nq] = fa[q];
                l[nq] = l[p]+1;
                fa[np]=fa[q]=nq;
                while (nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        ans+=l[last]-l[fa[last]];
    }
    void query(){
        init();
        for(int i=1;i<=len;i++){
            add(s[i]-'a');
        }
        printf("%lld\n",ans);
    }
}sam;
int main(int argc, char const *argv[])
{
	scanf("%s",s+1); len=strlen(s+1);
	sam.query();
	return 0;
}