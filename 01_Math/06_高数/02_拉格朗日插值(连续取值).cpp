int x[maxn], y[maxn];
int s1[maxn], s2[maxn], ifac[maxn];

//如果x的取值是连续一段，可以做到O(n)求解
int lagrange(int n, int *x, int *y, int xi) {
	int ans = 0;
	s1[0] = (xi - x[0]) % mod, s2[n + 1] = 1;
	for(int i = 1; i <= n; i ++) s1[i] = 1ll * s1[i - 1] * (xi - x[i]) % mod;
	for(int i = n; i >= 0; i --) s2[i] = 1ll * s2[i + 1] * (xi - x[i]) % mod;
	ifac[0] = ifac[1] = 1;
	for(int i = 2; i <= n; i ++) ifac[i] = -1ll * mod / i * ifac[mod % i] % mod;
	for(int i = 2; i <= n; i ++) ifac[i] = 1ll * ifac[i] * ifac[i - 1] % mod;
	for(int i = 0; i <= n; i ++)
		(ans += 1ll * y[i] * (i == 0 ? 1 : s1[i - 1]) % mod * s2[i + 1] % mod * ifac[i] % mod * (((n - i) & 1) ? -1 : 1) * ifac[n - i] % mod) %= mod;
	return (ans + mod) % mod;
}