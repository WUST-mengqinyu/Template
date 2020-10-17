const int N = 305;
const int mod = 1e9 + 7;

int n, m, a[N][N];

int Gauss(int n) {
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        for (int k = i + 1; k <= n; k++) {
            while (a[k][i]) {
                int d = a[i][i] / a[k][i];
                for (int j = i; j <= n; j++) {
                    a[i][j] = (a[i][j] - 1LL * d * a[k][j] % mod + mod) % mod;
                }
                std::swap(a[i], a[k]);
                ans = -ans;
            }
        }
        ans = 1LL * ans * a[i][i] % mod;
    }
    return (ans % mod + mod) % mod;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        a[u][v]--, a[v][u]--;
        a[u][u]++, a[v][v]++;
    }
    printf("%d\n", Gauss(n - 1));
    return 0;
}