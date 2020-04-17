/*
1. 插入x数
2. 删除x数(若有多个相同的数，因只删除一个)
3. 查询x数的排名(若有多个相同的数，因输出最小的排名)
4. 查询排名为x的数
5. 求x的前驱(前驱定义为小于x，且最大的数)
6. 求x的后继(后继定义为大于x，且最小的数)
*/

const int N = 1e5 + 7;

struct Splay {
	int ch[N][2], fa[N], val[N], cnt[N], size[N], tol, root;
	inline bool chk(int x) {
		return ch[fa[x]][1] == x;
	}
	inline void pushup(int x) {
		size[x] = size[ch[x][0]] + size[ch[x][1]] + cnt[x];
	}
	void rotate(int x) {
		int y = fa[x], z = fa[y], k = chk(x), w = ch[x][k ^ 1];
		ch[y][k] = w; fa[w] = y;
		ch[z][chk(y)] = x; fa[x] = z;
		ch[x][k ^ 1] = y; fa[y] = x;
		pushup(y); pushup(x);
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
		if (!goal) root = x;
	}
	void insert(int x) {
		int cur = root, p = 0;
		while (cur && val[cur] != x) {
			p = cur;
			cur = ch[cur][x > val[cur]];
		}
		if (cur) {
			cnt[cur]++;
		} else {
			cur = ++tol;
			if (p) ch[p][x > val[p]] = cur;
			ch[cur][0] = ch[cur][1] = 0;
			fa[cur] = p; val[cur] = x;
			cnt[cur] = size[cur] = 1;
		}
		splay(cur);
	}
	void find(int x) {
		int cur = root;
		while (ch[cur][x > val[cur]] && x != val[cur])
			cur = ch[cur][x > val[cur]];
		splay(cur);
	}
	int kth(int k) {
		int cur = root;
		while (1) {
			if (ch[cur][0] && k <= size[ch[cur][0]])
				cur = ch[cur][0];
			else if (k > size[ch[cur][0]] + cnt[cur])
				k -= size[ch[cur][0]] + cnt[cur], cur = ch[cur][1];
			else 
				break;
		}
		return cur;
	}
	int pre(int x) {
		find(x);
		if (val[root] < x) return root;
		int cur = ch[root][0];
		while (ch[cur][1]) cur = ch[cur][1];
		return cur;
	}
	int succ(int x) {
		find(x);
		if (val[root] > x) return root;
		int cur = ch[root][1];
		while (ch[cur][0]) cur = ch[cur][0];
		return cur;
	}
	void del(int x) {
		int last = pre(x), nxt = succ(x);
		splay(last); splay(nxt, last);
		int del = ch[nxt][0];
		if (cnt[del] > 1)
			cnt[del]--, splay(del);
		else
			ch[nxt][0] = 0;
	}
	int getrk(int x) {
		find(x);
		return size[ch[root][0]];
	}
} splay;

int n;

int main() {
	//freopen("in.txt", "r", stdin);
	splay.insert(0x3f3f3f3f);
	splay.insert(0xcfcfcfcf);
	read(n);
	while (n--) {
		int opt, x;
		read(opt, x);
		if (opt == 1) splay.insert(x);
		else if (opt == 2) splay.del(x);
		else if (opt == 3) print(splay.getrk(x));
		else if (opt == 4) print(splay.val[splay.kth(x + 1)]);
		else if (opt == 5) print(splay.val[splay.pre(x)]);
		else print(splay.val[splay.succ(x)]);
	}
	flush();
	return 0;
}