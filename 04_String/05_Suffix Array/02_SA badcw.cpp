namespace SA {
    const int maxn = 2e5 + 10;
    int t1[maxn], t2[maxn], c[maxn];
    int Rank[maxn], height[maxn];
    int RMQ[maxn];
    int mm[maxn];
    int sa[maxn];
    int best[25][maxn];
    bool cmp(int *r, int a, int b, int l) {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }
    void da(char str[], int sa[], int Rank[], int height[], int n, int m) {
        n++;
        int i, j, p, *x = t1, *y = t2;
        for (i = 0; i < m; i++)c[i] = 0;
        for (i = 0; i < n; i++)c[x[i] = str[i]]++;
        for (i = 1; i < m; i++)c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i--)sa[--c[x[i]]] = i;
        for (j = 1; j <= n; j <<= 1) {
            p = 0;
            for (i = n - j; i < n; i++)y[p++] = i;
            for (i = 0; i < n; i++)if (sa[i] >= j)y[p++] = sa[i] - j;
            for (i = 0; i < m; i++)c[i] = 0;
            for (i = 0; i < n; i++)c[x[y[i]]]++;
            for (i = 1; i < m; i++)c[i] += c[i - 1];
            for (i = n - 1; i >= 0; i--)sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (i = 1; i < n; i++)
                x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
            if (p >= n)break;
            m = p;
        }
        int k = 0;
        n--;
        for (i = 0; i <= n; i++)Rank[sa[i]] = i;
        for (i = 0; i < n; i++) {
            if (k)k--;
            j = sa[Rank[i] - 1];
            while (str[i + k] == str[j + k])k++;
            height[Rank[i]] = k;
        }
    }
    void initRMQ(int n) {
        for (int i = 1; i <= n; i++)
            RMQ[i] = height[i];
        mm[0] = -1;
        for (int i = 1; i <= n; i++)
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
        for (int i = 1; i <= n; i++)best[0][i] = i;
        for (int i = 1; i <= mm[n]; i++)
            for (int j = 1; j + (1 << i) - 1 <= n; j++) {
                int a = best[i - 1][j];
                int b = best[i - 1][j + (1 << (i - 1))];
                if (RMQ[a] < RMQ[b])best[i][j] = a;
                else best[i][j] = b;
            }
    }
    int askRMQ(int a, int b) {
        int t;
        t = mm[b - a + 1];
        b -= (1 << t) - 1;
        a = best[t][a];
        b = best[t][b];
        return RMQ[a] < RMQ[b] ? a : b;
    }
    int lcp(int a, int b) {
        a = Rank[a];
        b = Rank[b];
        if (a > b) swap(a, b);
        //cout << askRMQ(a + 1, b) << endl;
        return height[askRMQ(a + 1, b)];
    }
    void preprocess(char *str, int n, int m) {
        da(str, sa, Rank, height, n, m);
        initRMQ(n);
    }
}
