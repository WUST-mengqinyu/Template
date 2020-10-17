const int maxn = 1e5 + 10;
int x[maxn], y[maxn];
int qp(int a, int n) {
	ll ans = 1, base = a;
	for(; n; (base *= base) %= mod, n >>= 1) if(n & 1) (ans *= base) %= mod;
	return ans;
}

int lagrange(int n, int *x, int *y, int xi) {
	int ans = 0;
	for(int i = 0; i <= n; i ++) {
		int s1 = 1, s2 = 1;
		for(int j = 0; j <= n; j ++) if(i != j) {
			s1 = 1ll * s1 * (xi - x[j]) % mod;
			s2 = 1ll * s2 * (x[i] - x[j]) % mod;
		}
		ans = (1ll * ans + 1ll * y[i] * s1 % mod * qp(s2, mod - 2) % mod) % mod;
	}
	return (ans + mod) % mod;
}