struct PalindromicTree{
    int p,n,last,fail[maxn],tr[maxn][26],s[maxn],len[maxn],cnt[maxn];
    int newnode(int Len){
        for(int i = 0;i < 26; ++i) tr[p][i] = 0;
        len[p] = Len; cnt[p] = 0;
        return p++; 
    }
    void init(){
         p = n = last = 0;
         newnode(0);newnode(-1);
         fail[0] = 1;s[0] = -1;
    }
    int getfail(int x){
        while(s[n-len[x]-1] != s[n]) x = fail[x];
        return x;
    }
    void add(int x,int pos){
        s[++n] = x;
        int cur = getfail(last);
        if(!tr[cur][x]){
            int now = newnode(len[cur]+2);
            //e[now] = (node){pos-len[now]+1,pos};  //记录每个本质不同回文串出现的区间
            fail[now] = tr[getfail(fail[cur])][x]; 
            tr[cur][x] = now;                                  
        } 
        last = tr[cur][x];
        cnt[last]++;
    }
    void count(){
        for(int i = p-1;i > 0; --i) cnt[fail[i]] += cnt[i];
    }
}T;