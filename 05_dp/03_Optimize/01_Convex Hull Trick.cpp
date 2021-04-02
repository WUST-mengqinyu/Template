// eg: 
// fi = min(fj + (hi-hj)**2 + C)
// fj + hj**2 = 2hihj - hi**2 + fi - C
// gx {
//    x : -2hj
//    y : fj + hj **2
// }
// fi = y + x hi + hi * hi + C
// so:
// f[i] = get(h[i]) + h[i]*h[i] + C
// add(-2*h[i], h[i]*h[i]+f[i])

const int maxn = 1e6+50;
struct CHT {
    using P = pair<ll, ll>;
    P qu[maxn];
    int st, ed;
    CHT():st(1), ed(0) {}
    inline int sz() { return ed - st + 1; }
    ll eval(P& p, ll x) {
        return p.first * x + p.second;
    }
    bool ok(P &a, P &b, P &c) {
        return (b.first - a.first) * (c.second - b.second) < (b.second - a.second) * (c.first - b.first);
    }
    void add(ll x, ll y) {
        P tmp = {x, y};
        while (sz() >= 2 && !ok(qu[ed - 1], qu[ed], tmp))
            ed --;
        qu[++ed] = tmp;
    }
    ll get(ll x) {
        while (sz() >= 2 && eval(qu[st], x) >= eval(qu[st + 1], x))
            st ++;
        return eval(qu[st], x);
    }
}so;