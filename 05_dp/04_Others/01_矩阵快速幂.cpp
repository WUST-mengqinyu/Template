const int sz = 5;
struct Matrix {
    ll a[sz][sz];
    Matrix() { memset(a, 0, sizeof a); }
    void pr() {
        printf("*\n");
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                printf("%lld ", a[i][j]);
            }
            printf("\n");
        }
    }
    void tr() {
        for (int i = 0; i < sz; ++i) {
            for (int j = i + 1; j < sz; ++j) {
                swap(a[i][j], a[j][i]);
            }
        }
    }
} res, t1;

void init() {
    ;
}

Matrix mul(Matrix a, Matrix b) {
    Matrix res;
    // assert(a.m == b.n)
    for (int i = 0; i < sz; i++) // a.n
        for (int j = 0; j < sz; j++) // b.m
            for (int k = 0; k < sz; k++) // a.m, b.n
                (res.a[i][j] += a.a[i][k] * b.a[k][j] % mod) %= mod;
    return res;
}

Matrix Pow(ll n) {
    init();
    //for(int i = 0; i < cur; i++) res.a[i][i] = 1;
    while (n > 0) {
        if (n & 1) res = mul(res, t1);
        t1 = mul(t1, t1);
        n >>= 1;
    }
    return res;
}