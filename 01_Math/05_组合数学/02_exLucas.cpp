typedef long long ll;

ll p, n, m;

ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if(!b) { x = 1; y = 0; return a; }
	ll res = exgcd(b, a % b, x, y), t;
	t = x, x = y, y = t - a / b * y;
	return res;
}

ll qp(ll a, ll n, ll mod)
{
	ll ans = 1, base = a;
	for(; n; n >>= 1, (base *= base) %= mod) if(n & 1) (ans *= base) %= mod;
	return ans; 
}

ll fac(ll n, ll a, ll b)
{
	if(!n) return 1;
	ll res = 1;
	for(ll i = 2; i <= b; i ++) 
		if(i % a) (res *= i) %= b;
	res = qp(res, n / b, b);
	for(ll i = 2; i <= n % b; i ++)
		if(i % a) (res *= i) %= b;
	return res * fac(n / a, a, b) % b;
}

ll inv(ll n, ll mod) 
{
	ll x, y;
	exgcd(n, mod, x, y);
	return (x += mod) > mod ? x - mod : x;
}

ll CRT(ll b, ll mod) { return b * inv(p / mod, mod) % p * (p / mod) % p; }

ll C(ll n, ll m, ll a, ll b)
{
	ll up = fac(n, a, b), d1 = fac(m, a, b), d2 = fac(n - m, a, b);
	ll k = 0;
	for(ll i = n; i; i /= a) k += i / a;
	for(ll i = m; i; i /= a) k -= i / a;
	for(ll i = n - m; i; i /= a) k -= i / a;
	return up * inv(d1, b) % b * inv(d2, b) % b * qp(a, k, b) % b; 
}

ll exlucas(ll n, ll m)
{
	ll res = 0, tmp = p, b;
	int lim = sqrt(p) + 5;
	for(int i = 2; i <= lim; i ++) if(tmp % i == 0)
	{
		b = 1;
		while(tmp % i == 0) tmp /= i, b *= i;
		(res += CRT(C(n, m, i, b), b)) %= p;
	}
	if(tmp > 1) (res += CRT(C(n, m, tmp, tmp), tmp)) %= p;
	return res;
}