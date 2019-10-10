struct Matrix {
  ll a[2][2];
  Matrix() { memset(a, 0, sizeof (a)); }
  Matrix operator*(const Matrix &b) const {
    Matrix res;
    for (int i = 0; i <2; ++i)
      for (int j = 0; j <2; ++j)
        for (int k = 0; k < 2; ++k)
          res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % mod;
    return res;
  }
} ans, base;

void init() {
  base.a[0][0]  = base.a[1][0] = 1;
  base.a[0][1]=-1; 
  ans.a[0][0] = ans.a[1][1] = 1;
}

void qpow(int b) {
  while (b) {
    if (b & 1) ans = ans * base;
    base = base * base;
    b >>= 1;
  }
}