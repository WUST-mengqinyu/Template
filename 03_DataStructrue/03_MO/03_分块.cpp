// 非预处理数组版
inline int belong(int x) { return (x - 1) / block + 1; }
inline int lpos(int x) { return 1 + (x - 1) * block; }
inline int rpos(int x) { return min(n, x * block); }
int sz = (n - 1) / block + 1;

// 预处理版，maxn大于1e6已经不可能处理了
const int maxb = 1005;
int n, m;
int belong[maxn], lpos[maxb], rpos[maxb];
int val[maxn], lazy[maxb];
int block;

scanf("%d", &n);
block = sqrt(n);
for (int i = 1; i <= n; ++i) {
    scanf("%d", &val[i]);
    belong[i] = (i - 1) / block + 1;
}
int sz = (n - 1) / block + 1;
for (int i = 1; i <= sz; ++i) {
    lpos[i] = 1 + (i - 1) * block;
    rpos[i] = i * block;
}
rpos[sz] = n;