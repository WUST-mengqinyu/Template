int n, m;
int belong[maxn], lpos[maxn], rpos[maxn];
int val[maxn], nxt[maxn], k[maxn], lst[maxn];
int block;

void update(int pos) {
    int llim = lpos[belong[pos]], rlim = rpos[belong[pos]];
    for (int i = pos; i >= llim; --i) {
        if (val[i] + i > rlim) {
            k[i] = 1;
            nxt[i] = val[i] + i;
            if (val[i] + i > n) lst[i] = i;
            else lst[i] = lst[nxt[i]];
        } else {
            k[i] = 1 + k[val[i] + i];
            nxt[i] = nxt[val[i] + i];
            lst[i] = lst[val[i] + i];
        }
    }
}

void init() {
    for (int i = n; i >= 1; --i) {
        int rlim = rpos[belong[i]];
        if (val[i] + i > rlim) {
            k[i] = 1;
            nxt[i] = val[i] + i;
            if (val[i] + i > n) lst[i] = i;
            else lst[i] = lst[nxt[i]];
        } else {
            k[i] = 1 + k[val[i] + i];
            nxt[i] = nxt[val[i] + i];
            lst[i] = lst[val[i] + i];
        }
    }
}

int query(int pos) {
    int res = 0;
    while (pos <= n) {
        res += k[pos];
        if (nxt[pos] > n) printf("%d ", lst[pos]);
        pos = nxt[pos];
    }
    return res;
}

int main(int argc, char* argv[]) {
    scanf("%d%d", &n, &m);
    block = sqrt(n) * 1.6 + 1;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &val[i]);
        belong[i] = (i - 1) / block + 1;
    }
    int sz = (n - 1) / block + 1;
    for (int i = 1; i <= sz; ++i) {
        lpos[i] = 1 + (i - 1) * block;
        rpos[i] = i * block;
    }
    rpos[sz] = n;
    init();
    while (m--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int pos;
            scanf("%d", &pos);
            printf("%d\n", query(pos));
        } else {
            int pos, kl;
            scanf("%d%d", &pos, &kl);
            val[pos] = kl;
            update(pos);
        }
    }
    return 0;
}