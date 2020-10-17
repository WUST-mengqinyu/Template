// ---
// $n$,$m$小$p$大
// ---
map<int, ll> m;

const int MOD = 1e9+7;
void fun(int n, int k) {
    for (int i = 2; i <= sqrt(n * 1.0); i++) {
        while (n % i == 0) {
            n /= i;
            m[i] += k;
        }
    }
    if (n > 1) {
        m[n] += k;
    }
}

ll C(ll a, ll b) {
    if (a < b || a < 0 || b < 0)
        return 0;
    m.clear();
    ll ret = 1;
    b = min(a - b, b);
    for (int i = 0; i < b; i++) {
        fun(a - i, 1);
    }
    for (int i = b; i >= 1; i--) {
        fun(i, -1);
    }
    for (__typeof(m.begin()) it = m.begin(); it != m.end(); it++) {
        if ((*it).second != 0) {
            ret *= qp((*it).first, (*it).second);
            ret %= MOD;
        }
    }
    return ret;
}

int main(int argc,char *argv[])
{
    ll a, b;
    while (scanf("%lld%lld", &a, &b) != EOF) {
        printf("%lld\n", C(a, b));
    }
    return 0;
}