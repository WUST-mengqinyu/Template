struct Trie {
    int tree[maxn*20][2], tot;
    int flag[maxn*20];

    void insert_ch(int x) {
        int root = 0;
        flag[0]++;
        for (int i = 30; i >= 0; --i) {
            int id = (x >> i) & 1;
            if (!tree[root][id]) {
                tree[root][id] = ++tot;
                tree[tree[root][id]][0] = tree[tree[root][id]][1] = 0;
                flag[tree[root][id]] = flag[tree[tree[root][id]][0]] = flag[tree[tree[root][id]][1]] = 0;
            }
            root = tree[root][id];
            flag[root]++;
        }
    }

    void del(int x) {
        int root = 0;
        flag[0]--;
        for (int i = 30; i >= 0; --i) {
            int id = (x >> i) & 1;
            assert(tree[root][id]);
            if (flag[tree[root][id]] == 1) {
                flag[tree[root][id]] = 0;
                tree[root][id] = 0;
                return;
            }
            root = tree[root][id];
            flag[root]--;
        }
    }

    int find_ch(int x, int flag = 0) { // flag 0 最小异或值， 1 最大异或值
        int root = 0;
        int res = 0;
        for (int i = 30; i >= 0; --i) {
            int id = ((x >> i) & 1);
            if (flag) id = !id;
            if (tree[root][id]) {
                root = tree[root][id];
                res = res << 1 | id;
            } else {
                root = tree[root][!id];
                res = res << 1 | (!id);
            }
        }
        return res;
    }

    void init() {
        tree[0][0] = tree[0][1] = 0;
        tot = 0;
    }
};