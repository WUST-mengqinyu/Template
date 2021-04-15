struct Trie {
    int son[maxn * 20][2], tot;
    int flag[maxn * 20];

    void insert(int x) {
        int rt = 0;
        flag[0]++;
        for (int i = 30; i >= 0; --i) {
            bool id = (x >> i) & 1;
            if (!son[rt][id]) {
                son[rt][id] = ++tot;
                son[tot][0] = son[tot][1] = 0;
                flag[tot] = flag[son[tot][0]] = flag[son[tot][1]] = 0;
            }
            rt = son[rt][id];
            flag[rt]++;
        }
    }

    void del(int x) {
        int rt = 0;
        flag[0]--;
        for (int i = 30; i >= 0; --i) {
            int id = (x >> i) & 1;
            assert(son[rt][id]);
            if (flag[son[rt][id]] == 1) {
                flag[son[rt][id]] = 0;
                son[rt][id] = 0;
                return;
            }
            rt = son[rt][id];
            flag[rt]--;
        }
    }

    int find_ch(int x, int flag = 0) { // flag 0 最小异或值， 1 最大异或值
        int rt = 0;
        int res = 0;
        for (int i = 30; i >= 0; --i) {
            int id = ((x >> i) & 1);
            if (flag) id = !id;
            if (son[rt][id]) {
                rt = son[rt][id];
                res = res << 1 | id;
            } else {
                rt = son[rt][!id];
                res = res << 1 | (!id);
            }
        }
        return res;
    }

    void init() {
        son[0][0] = son[0][1] = 0;
        tot = 0;
    }
};