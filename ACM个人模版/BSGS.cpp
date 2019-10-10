//  求解 a^x mod p 和b 同余
long long pow_mod(int a,int b,int m)
{
    long long res=1;
    while(b)
    {
        if(b&1)res=res*a%m;
        a=a*a%m;
        b>>=1;
    }
    return res;
}
long long BSGS(long long a,long long b,long long p){
    map<long ,long>hash;
    hash.clear();
    b%=p;
    int t=(int)sqrt(p)+1;
    for(int j=0;j<t;j++){
        int val=(long long)b*pow_mod(a,j,p)%p;
        hash[val]=j;
    }
    a=pow_mod(a,t,p);
    if(a==0){
        if(b==0){
            return 1;
        }else{
            return -1;
        }
    }
    for(int i=0;i<=t;i++){
        int val=pow_mod(a,i,p);
        int j=hash.find(val)==hash.end()?-1:hash[val];
        if(j>=0&&i*t-j>=0){
            return i*t-j;
        }
    }
    return -1;//无解时返回-1
}
