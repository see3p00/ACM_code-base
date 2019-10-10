 
#include<bits/stdc++.h>
#define il inline
#define pb push_back
#define ms(_data,v) memset(_data,v,sizeof(_data))
#define sc(n) scanf("%d",&n)
#define SC(n,m) scanf("%d %d",&n,&m)
#define SZ(a) int((a).size())
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define drep(i,a,b)	for(int i=a;i>=b;--i)
using namespace std;
typedef long long ll;
const ll inf=0x3f3f3f3f;
const double pi=acos(-1.0);
const double eps=1e-9;
int a[50],b[50],aa[3][32];
il void insert(int x,int cur) {
    for(int i=31; i>=0; --i) {
        if(x>>i) {
            if(!aa[cur][i]) {
                aa[cur][i]=x;
                break;
            }
            x^=aa[cur][i];
        }
    }
}
il void Intersect(int x,int y) {
    int t1[32],t2[32];
    for(int i=0; i<32; ++i) {
        t1[i]=t2[i]=aa[x][i];
    }
    for(int i=0; i<32; ++i) {
        if(aa[y][i]) {
            int x=aa[y][i],tp=0;
            for(int j=31; j>=0; --j) {
                if(x>>j) {
                    if(!t1[j]) {
                        t1[j]=x,t2[j]=tp;
                        break;
                    }
                    x^=t1[j],tp^=t2[j];
                }
            }
            if(!x) insert(tp,2);
        }
    }
}
int main(){
	for(int i=0;i<=30;++i){
		cin>>a[i];
		insert(a[i],0);	
	} 
	for(int i=0;i<=30;++i){
		cin>>b[i];
		insert(b[i],1);	
	} 
	Intersect(0,1); //a,b的线性基交 
	//a[2][]; 
	return 0;
}