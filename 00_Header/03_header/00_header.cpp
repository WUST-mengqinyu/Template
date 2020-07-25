// Editor -> Live Templates
// add template group acm
// add template main
// C++ Declaration

#include <bits/stdc++.h>
#define ll long long
#define x first
#define y second
#define sz size()
#define all(x) x.begin(), x.end()
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<long long> vl;

template <class T>
inline bool scan(T &ret){
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; //EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

const ll mod = 1e9+7;
const int maxn = $MAXN$;
const int inf = 0x3f3f3f3f;

ll qp(ll x, ll n, ll mod = ::mod) {
    ll res = 1; x %= mod;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main(int argc, char* argv[]) {
    $END$
    return 0;
}

// C++ Expression debug
freopen("data.in","r",stdin);
freopen("data.out","w",stdout);
clock_t ST = clock();
cerr << "time: " << ((clock()-ST)*1000.0 / CLOCKS_PER_SEC) << "ms" << endl;


// C++ Expression tkase
int T;
scanf("%d", &T);
for (int kase = 1; kase <= T; ++kase) { 
$END$
}