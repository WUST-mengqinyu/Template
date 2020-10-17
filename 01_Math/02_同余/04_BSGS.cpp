// 求 a^x = b % p
int BSGS(int a, int b, int p) {
    map<int, int> hash;
    b %= p;
    int t = (int) sqrt(p) + 1;
    for (int j = 0; j < t; j++) {
        int val = 1ll * b * qp(a, j, p) % p;
        hash[val] = j;
    }
    a = qp(a, t, p);
    if (a == 0) return b == 0 ? 1 : -1;
    for (int i = 0; i <= t; i++) {
        int val = qp(a, i, p);
        int j = hash.find(val) == hash.end() ? -1 : hash[val];
        if (j >= 0 && i * t - j >= 0) return i * t - j;
    }
    return -1;
}