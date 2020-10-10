// 返回1～n中k因子的个数
ll dig(ll n, ll k) {
    if (k == 1) return n;
    ll res = 0;
    while (n > 0) {
        res += n / k;
        n /= k;
    }
    return res;
}
