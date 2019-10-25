// 判断二维点能否构成正方形
struct node{
    double x,y;
}d[30];
double getdis(node a,node b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
bool isequal(double x,double y){
    if(x-y>=-1e-8&&x-y<=1e-8)
        return true;
    return false;
}
bool isSquare(node a,node b,node c,node d){
    double len[6];
    len[0]=getdis(a,b);
    len[1]=getdis(a,c);
    len[2]=getdis(a,d);
    len[3]=getdis(b,c);
    len[4]=getdis(b,d);
    len[5]=getdis(c,d);
    double len1=len[0];
    double len2=len[0];
    for(int i=1;i<6;++i){
        if(!isequal(len[i],len2)&&!isequal(len[i],len1))
            len2=len[i];
    }
    for(int i=0;i<6;++i){
        if(isequal(len[i],len2)||isequal(len[i],len1));
        else return false;
    }
    if(len2-len1<-1e-8)
        std::swap(len1,len2);
    if(!isequal(2*len1*len1,len2*len2))
        return false;
    return true;
}