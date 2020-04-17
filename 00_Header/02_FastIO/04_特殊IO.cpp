// 代替gets
scanf("%[^\n]%*c", ss)

void out2(int x, int flag = 1) {
    if (x == 0) {
        if (flag) putchar('0');
        return;
    }
    out2(x >> 1, 0);
    putchar('0' + x % 2);
}

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