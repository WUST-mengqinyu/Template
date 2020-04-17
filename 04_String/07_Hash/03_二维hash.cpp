#define ull unsigned long long
const int maxn = 1005;
ull hs[maxn][maxn];
char a[maxn][maxn];
int n, m;
ull base1 = 131, base2 = 13331;
ull pwb1[maxn] = {1}, pwb2[maxn] = {1};

void init() {
    for (int i = 1; i < maxn; ++i) {
        pwb1[i] = pwb1[i - 1] * base1;
        pwb2[i] = pwb2[i - 1] * base2;
    }
}

void Hash() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            hs[i][j]=hs[i][j-1]*base1+a[i][j] - 'a';
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            hs[i][j]+=hs[i-1][j]*base2;
}

// 右下角(i,j)，行列长度n,m
ull getHs(int i, int j, int lenn, int lenm) {
    return hs[i][j] - hs[i - lenn][j] * pwb2[lenn] - 
            hs[i][j - lenm] * pwb1[lenm] +
            hs[i - lenn][j - lenm] * pwb2[lenn] * pwb1[lenm];
}