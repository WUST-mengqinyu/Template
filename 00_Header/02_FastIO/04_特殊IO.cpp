// 代替gets
scanf("%[^\n]%*c", ss)

// 高精分数输出
void print(ll x, ll y, int need) { // need 表示小数位数
    int a[need];
    printf("%lld.", x / y);
    ll t = x % y;
    for (int i = 0; i < need; i++) {
        t *= 10;
        a[i] = t / y;
        t = t % y;
    }
    if (t * 10 / y >= 5)a[need - 1]++;
    int i = need - 1;
    while (a[i] == 10) {
        a[i] = 0;
        a[--i]++;
    }
    for (int i = 0; i < need; i++) putchar(a[i]);
    putchar('\n');
}

// type mx
// int 10
// int64 19
// int128 38
template<class T, int g = 10>
void print(T x) {
    vector<char> a(38);
    if (x < 0) {x = -x;putchar('-');}
    if (x == 0) {putchar('0');return;}
    int tot = 0;
    while (x > 0) {
        a[tot++] = x % g;
        x /= 10;
    }
    for (int i = tot - 1; i >= 0; --i) putchar('0' + a[i]);
}