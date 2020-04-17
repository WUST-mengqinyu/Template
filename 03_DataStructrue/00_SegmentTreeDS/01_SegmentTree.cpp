const int maxn = 2e5+5;
// 序列
int a[maxn];

struct SegmentTree {
#define TYPE int
#define USELAZY 0
    TYPE val[maxn << 2];
    int sz;
//    check this type
    vector<int> lazy;

    inline TYPE comb(const TYPE& a, const TYPE& b) {
        TYPE res;
        res = a + b;
        return res;
    }

    int le, re, k;

    inline void build(int rt, int l, int r) {
        if (USELAZY) lazy[rt] = 0;
        if (l == r) {
            val[rt] = a[l];
            return;
        }
        int mid = l + r >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
        pushup(rt);
    }
    inline void build() {build(1, 1, sz);}

    inline void init(int sz_) {
        sz = sz_;
        lazy.resize(sz_ << 2);
        build();
    }
    inline void pushup(int rt) {val[rt] = comb(val[rt << 1], val[rt << 1 | 1]);}
    inline void deal(int rt, int kt) {
//        todo:
        val[rt] = comb(val[rt], kt);
    }
    inline void pushdown(int rt, int len) {
        if (lazy[rt]) {
            // check the lazy change
            lazy[rt << 1] += lazy[rt];
            lazy[rt << 1 | 1] += lazy[rt];
            deal(rt << 1, lazy[rt]);
            deal(rt << 1 | 1, lazy[rt]);
            lazy[rt] = 0;
        }
    }

    inline void update(int rt, int l, int r) {
        if (le <= l && r <= re) {
            deal(rt, k);
            return;
        }
        if (USELAZY) pushdown(rt, r - l + 1);
        int mid = l + r >> 1;
        if (le <= mid) update(rt << 1, l, mid);
        if (re > mid) update(rt << 1 | 1, mid + 1, r);
        pushup(rt);
    }

    inline TYPE query(int rt, int l, int r) {
        if (le <= l && r <= re) {
            return val[rt];
        }
        if (USELAZY) pushdown(rt, r - l + 1);
        // check the zero type
        TYPE res;
        int mid = l + r >> 1;
        if (le <= mid) res = comb(res, query(rt << 1, l, mid));
        if (re > mid) res = comb(res, query(rt << 1 | 1, mid + 1, r));
        return res;
    }

    // check return type
    inline int query(int l, int r) {
        le = l, re = r;
        return query(1, 1, sz);
    }
    inline void modify(int l, int r, int kt) {
        le = l, re = r, k = kt;
        update(1, 1, sz);
    }

//    inline void pt(int rt, int l, int r) {
//        if (l == r) {
//            printf("%d ", val[l]);
//            return;
//        }
//        pushdown(rt, r - l + 1);
//        int mid = l + r >> 1;
//        if (le <= mid) pt(rt << 1, l, mid);
//        if (re > mid) pt(rt << 1 | 1, mid + 1, r);
//    }

#undef TYPE
};
