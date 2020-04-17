#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 50005;

struct MO {
    int l, r, id, oppre;
}q[maxn];

int n, m, col[maxn], block, belong[maxn], colpre[maxn];
int changepos[maxn], changepre[maxn], changenow[maxn];
int vis[maxn * 20];
int ans;
int res[maxn];
bool cmp(const MO& a, const MO& b) {
    if (belong[a.l] != belong[b.l]) return a.l < b.l;
    if (belong[a.r] != belong[b.r]) return a.r < b.r;
    return a.oppre < b.oppre;
}
void add(int x) {}

void del(int x) {}

void unmodify(int pos, int now) {
    if (q[pos].l <= changepos[now] && changepos[now] <= q[pos].r) {
        del(changenow[now]);
        add(changepre[now]);
    }
    col[changepos[now]] = changepre[now];
}

void modify(int pos, int now) {
    if (q[pos].l <= changepos[now] && changepos[now] <= q[pos].r) {
        del(changepre[now]);
        add(changenow[now]);
    }
    col[changepos[now]] = changenow[now];
}

int main() {
    scanf("%d%d", &n, &m);
    block = pow(n, 0.66666);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &col[i]);
        colpre[i] = col[i];
        belong[i] = i / block + 1;
    }
    char s[2];
    int t = 0, t2 = 0;
    for (int i = 1; i <= m; ++i) {
        scanf("%s", s);
        if (s[0] == 'Q') {
            ++t;
            scanf("%d%d", &q[t].l, &q[t].r);
            q[t].oppre = t2;
            q[t].id = t;
        } else {
            ++t2;
            scanf("%d%d", &changepos[t2], &changenow[t2]);
            changepre[t2] = colpre[changepos[t2]];
            colpre[changepos[t2]] = changenow[t2];
        }
    }
    sort(q + 1, q + 1 + t, cmp);
    int l = 1, r = 0, now = 0;
    for (int i = 1; i <= t; ++i) {
        while(r < q[i].r) add(col[++r]);
        while(r > q[i].r) del(col[r--]);
        while(l < q[i].l) del(col[l++]);
        while(l > q[i].l) add(col[--l]);
        while (now < q[i].oppre) modify(i, ++now);
        while (now > q[i].oppre) unmodify(i, now--);
        res[q[i].id] = ans;
    }
    for (int i = 1; i <= t; ++i) printf("%d\n", res[i]);
    return 0;
}