// 原题1e5个区间有2e5个端点，离散化出来4e5个区间
// 然后线段树需要4e5*4=16e5的大小
// 注意三个数组要开离散化数量的四倍，如果不需要sz可以不用这个数组。
int val[maxn << 4];
int lpos[maxn << 2], rpos[maxn << 2], tot, sz[maxn << 2];
vector<int> xpos;
sort(xpos.begin(), xpos.end());
xpos.erase(unique(xpos.begin(), xpos.end()), xpos.end());
tot = 1;
lpos[1] = rpos[1] = xpos[0];
sz[1] = 1;
for (int i = 1; i < xpos.size(); ++i) {
    if (xpos[i] - xpos[i - 1] != 1) {
        lpos[++tot] = xpos[i - 1] + 1;
        rpos[tot] = xpos[i] - 1;
        sz[tot] = rpos[tot] - lpos[tot] + 1;
    }
    ++tot;
    lpos[tot] = rpos[tot] = xpos[i];
    sz[tot] = 1;
}
le = lower_bound(lpos + 1, lpos + 1 + tot, p[i].x) - lpos;
re = upper_bound(rpos + 1, rpos + 1 + tot, p[i].y) - rpos - 1;