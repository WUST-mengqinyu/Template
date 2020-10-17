ll gcd(ll a,ll b) {while(b^=a^=b^=a%=b);return a;}

ll gcd(ll a,ll b){ return b==0?a:gcd(b,a%b); }

ll exgcd(ll a, ll b, ll &x, ll &y) {
    ll d = a;
    if (b) d = exgcd(b, a % b, y, x), y -= x * (a / b);
    else x = 1, y = 0;
    return d;
}

// ax + by = c
// x = x + k*dx
// y = y - k*dx
// 当x和y都非负时返回1，x，y即为当前最小非负整数解（优先x）
bool solve(ll a, ll b, ll c, ll &x, ll &y, ll &dx, ll &dy) {
    x = y = dx = dy = 0;
    if (a == 0 && b == 0) return 0;
    ll x0, y0;
    ll d = exgcd(a, b, x0, y0);
    if (c % d != 0) return 0;
    dx = b / d, dy = a / d;
    x = (x0 % dx * ((c / d) % dx) % dx + dx) % dx;
    y = (c - a * x) / b;
    // 删掉这一句返回x的最小非负整数解
    if (y < 0) return 0;
    return 1;
}