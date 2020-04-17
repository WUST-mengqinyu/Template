struct Base {
#define TYPE ll
    static const int len = 64;
    bool rel; int sz;
    TYPE a[len];

    void init() {
        rel = sz = 0;
        memset(a, 0, sizeof a);
    }

    TYPE &operator[](int x) {
        return a[x];
    }

    TYPE operator[](int x) const {
        return a[x];
    }


    void ins(ll x) {
        for(int i = 63; i >= 0; i --) {
            if((x >> i) & 1) {
                if(!d[i]) return void(d[i] = x);
                x ^= d[i];
            }
        }
    }

    void insert(TYPE t) {
        for (int i = len - 1; i >= 0; --i) {
            if (!(t >> i & 1)) continue;
            if (a[i]) t ^= a[i];
            else {
                for (int j = 0; j < i; ++j) if (t >> j & 1) t ^= a[j];
                for (int j = i+1; j < len; ++j) if (a[j] >> i & 1) a[j] ^= t;
                a[i] = t;
                ++sz;
                return;
            }
        }
        rel = true;
    }

    bool check(TYPE x) {
        for (int i = len - 1; i >= 0; i--)
            if ((x >> i) & 1) {
                if (a[i]) x ^= a[i];
                else return false;
            }
        return true;
    }
    TYPE mx() {
        TYPE res = 0;
        for (int i = len - 1; i >= 0; --i) {
            if ((res ^ (a[i])) > res) res ^= a[i];
        }
        return res;
    }
//    vector<TYPE> v;
//    void basis() {for (int i = 0; i < len; ++i) if (a[i]) v.push_back(a[i]);}
//    TYPE k_th(TYPE k) {
//        k -= rel;
//        if(k >= (((TYPE)1) << sz)) return -1;
//        TYPE ans = 0;
//        for(int i = 0; i < (int)v.size(); i ++) if(k & (((TYPE)1) << i)) ans ^= v[i];
//        return ans;
//    }
//    void init()
//    {
//        sz = 0;
//        for(int i = 0; i < len; i ++) if(a[i])
//                for(int j = 0; j < i; j ++)
//                    if(a[i] & (1ll << j)) a[i] ^= a[j];
//        for(int i = 0; i < len; i ++) if(a[i]) a[sz ++] = a[i];
//    }
    friend Base intersection(const Base &a, const Base &b) {
        Base ans = {}, c = b, d = b;
        for (int i = 0; i < len; i++) {
            TYPE x = a[i];
            if (!x)continue;
            int j = i;
            TYPE T = 0;
            for (; j >= 0; --j) {
                if ((x >> j) & 1)
                    if (c[j]) {
                        x ^= c[j];
                        T ^= d[j];
                    }
                    else break;
            }
            if (!x)ans[i] = T;
            else {
                c[j] = x;
                d[j] = T;
            }
        }
        return ans;
    }

#undef TYPE
};

// 前缀线性基
struct LinearBasis {
    int f[20], g[20];

    void ins(int x, int idx) {
        for (int i = 19; ~i; i--) {
            if ((x >> i) & 1) {
                if (f[i]) {
                    if (g[i] <= idx) {
                        x ^= f[i];
                        f[i] ^= x;
                        swap(g[i], idx);
                    }
                    else x ^= f[i];
                } else {
                    f[i] = x;
                    g[i] = idx;
                    break;
                }
            }
        }
    }

    int query(int l) {
        int res = 0;
        for (int i = 19; ~i; i--)
            if (g[i] >= l)
                res = max(res, res ^ f[i]);
        return res;
    }
} base[maxn];