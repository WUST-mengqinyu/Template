int prim[maxn], tot;
bool v[maxn];
void init() {
    for (int i = 2; i < maxn; ++i) {
        if (!v[i]) prim[++tot] = i;
        for (int j = i + i; j < maxn && j <= (ll)i * i; j += i) v[j] = 1;
    }
}