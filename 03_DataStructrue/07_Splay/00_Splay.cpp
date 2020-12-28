/*
1. 插入x数
2. 删除x数(若有多个相同的数，因只删除一个)
3. 查询x数的排名(若有多个相同的数，因输出最小的排名)
4. 查询排名为x的数
5. 求x的前驱(前驱定义为小于x，且最大的数)
6. 求x的后继(后继定义为大于x，且最小的数)
*/

const int maxn = 1e5+50;
struct Splay {
    int ch[maxn][2], fa[maxn], val[maxn], cnt[maxn], sz[maxn], tot, rt;
    inline bool chk(int x) { return ch[fa[x]][1] == x; }
    inline void pushup(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }
    void rotate(int x) {
        int y = fa[x], z = fa[y], k = chk(x), w = ch[x][k ^ 1];
        ch[y][k] = w; fa[w] = y;
        ch[z][chk(y)] = x, fa[x] = z;
        ch[x][k ^ 1] = y; fa[y] = x;
        pushup(y), pushup(x);
    }
    void splay(int x, int goal = 0) {
        while (fa[x] != goal) {
            int y = fa[x], z = fa[y];
            if (z != goal) {
                if (chk(x) == chk(y)) rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
        if (!goal) rt = x;
    }
    void insert(int x) {
        int cur = rt, p = 0;
        while (cur && val[cur] != x) {
            p = cur;
            cur = ch[cur][x > val[cur]];
        }
        if (cur) cnt[cur] ++;
        else {
            cur = ++tot;
            if (p) ch[p][x > val[p]] = cur;
            ch[cur][0] = ch[cur][1] = 0;
            fa[cur] = p; val[cur] = x;
            cnt[cur] = sz[cur] = 1;
        }
        splay(cur);
    }
    void find(int x) {
        int cur = rt;
        while (ch[cur][x > val[cur]] && x != val[cur]) cur = ch[cur][x > val[cur]];
        splay(cur);
    }
    int kth(int k) {
        int cur = rt;
        while (1) {
            if (ch[cur][0] && k <= sz[ch[cur][0]]) cur = ch[cur][0];
            else if (k > sz[ch[cur][0]] + cnt[cur]) k -= sz[ch[cur][0]] + cnt[cur], cur = ch[cur][1];
            else break;
        }
        return cur;
    }
    int pre(int x) {
        find(x);
        if (val[rt] < x) return rt;
        int cur = ch[rt][0];
        while (ch[cur][1]) cur = ch[cur][1];
        return cur;
    }
    int succ(int x) {
        find(x);
        if (val[rt] > x) return rt;
        int cur = ch[rt][1];
        while (ch[cur][0]) cur = ch[cur][0];
        return cur;
    }
    void del(int x) {
        int lst = pre(x), nxt = succ(x);
        splay(lst), splay(nxt, lst);
        int del = ch[nxt][0];
        if (cnt[del] > 1) cnt[del] --, splay(del);
        else ch[nxt][0] = 0;
    }
    int getrk(int x) {
        find(x);
        return sz[ch[rt][0]];
    }
} solve;

int n;

int main() {
	solve.insert(0x3f3f3f3f);
	solve.insert(0xcfcfcfcf);
	read(n);
	while (n--) {
		int opt, x;
		read(opt, x);
		if (opt == 1) solve.insert(x);
		else if (opt == 2) solve.del(x);
		else if (opt == 3) print(solve.getrk(x));
		else if (opt == 4) print(solve.val[solve.kth(x + 1)]);
		else if (opt == 5) print(solve.val[solve.pre(x)]);
		else print(solve.val[solve.succ(x)]);
	}
	return 0;
}