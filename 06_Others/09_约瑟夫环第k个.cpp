ll kth(ll n, ll m, ll k) { // n个人，m间隔，第k个出列的人
    if (m == 1) return k;
    ll res = (m - 1) % (n - k + 1);
    for (ll i = n - k + 2, stp = 0; i <= n; i += stp, res += stp * m) {
        if (res + m >= i) {
            res = (res + m) % i;
            i++;
            stp = 0;
        } else {
            stp = (i - res - 2) / (m - 1);
            if (i + stp > n) {
                res += (n - (i - 1)) * m;
                break;
            }
        }
    }
    return res + 1;
}

ll dieInXturn(int n, int k, int x) { // n个人，m间隔，第k个人出列时间
    ll tmp = 0;
    while (n) {
        x = (x + n) % n;
        if (k > n)x += (k - x - 1 + n - 1) / n * n;
        if ((x + 1) % k == 0) {
            tmp += (x + 1) / k;
            break;
        } else {
            if (k > n) {
                tmp += x / k;
                ll ttmp = x;
                x = x - (x / n + 1) * (x / k) + (x + n) / n * n - k;
                n -= ttmp / k;

            } else {
                tmp += n / k;
                x = x - x / k;
                x += n - n / k * k;
                n -= n / k;
            }
        }
    }
    return tmp;
}