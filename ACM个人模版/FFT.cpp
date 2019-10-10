struct Complex{
    double x,y;
    Complex(double _x = 0.0, double _y = 0.0){
        x = _x; y = _y;
    }
    Complex operator -(const Complex &b)const{
        return Complex(x - b.x, y - b.y);
    }
    Complex operator +(const Complex &b)const{
        return Complex(x + b.x, y + b.y);
    }
    Complex operator *(const Complex &b)const{
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};
 
void change(Complex y[],int len){
    int i,j,k;
    for(i = 1, j = len / 2; i < len - 1; i++){
        if(i < j) swap(y[i],y[j]);
        k = len / 2;
        while(j >= k){
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}
//len必须是2^k
//on==1进行DFT；on==-1进行IDFT
void fft(Complex y[],int len,int on){
    change(y,len);
    for(int h = 2; h <= len; h <<= 1){
        Complex wn(cos(-on*2*pi/h),sin(-on*2*pi/h));
        for(int j = 0; j < len; j += h){
            Complex w(1,0);
            for(int k = j; k < j + h / 2; k++){
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if(on == -1){
        for(int i = 0; i < len; i++) y[i].x /= len;
    }
}
Complex x[maxn<<2];
int len,len1;
len = 1;
while(len < 2 * len1) len <<= 1;
for(int i = 0; i < len1; i++)
   x[i] = a[i];
for(int i = len1; i < len; i++)
   x[i] = Complex(0,0);
fft(x,len,1);
fft(x,len,-1);