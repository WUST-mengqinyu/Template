unordered_map<int, int> Hash;

int exBSGS(int a, int b, int p) {
    a %= p, b %= p;
    if (b == 1) return 0;
    if (!b && !a) return 1;
    if (!a) return -1;
    if (!b) {
        int ret = 0, d;
        while ((d = __gcd(a, p)) != 1) {
            ++ret, p /= d;
            if (p == 1) return ret;
        }
        return -1;
    }
    int ret = 0, A = a, B = b, P = p, C = 1, d;
    while ((d = __gcd(A, P)) != 1) {
        if (B % d) return -1;
        P /= d, B /= d;
        C = 1ll * C * (A / d) % P;
        ++ret;
        if (C == B) return ret;
    }
    Hash.clear();
    int f = 1, t = sqrt(P) + 1;
    for (int i = 0; i < t; i++) {
        Hash[1ll * f * B % P] = i;
        f = 1ll * f * A % P;
    }
    int tf = f;
    f = 1ll * f * C % P;
    for (int i = 1; i <= t; i++) {
        if (Hash.find(f) != Hash.end()) return ret + i * t - Hash[f];
        f = 1ll * f * tf % P;
    }
    return -1;
}