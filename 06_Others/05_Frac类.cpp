struct Frac {
    ll a, b;
    void getJian() {
        ll gcd = abs(__gcd(a, b));
        a /= gcd;
        b /= gcd;
        if (b < 0) {
            a = -a;
            b = -b;
        }
    }
    Frac(ll a_ = 1, ll b_ = 1) {
        a = a_;
        b = b_;
        getJian();
    }
    Frac operator + (const Frac& oth) {
        ll bt = b * oth.b;
        ll at = a * oth.b + oth.a * b;
        return Frac(at, bt);
    }
    Frac operator * (const Frac& oth) {
        a *= oth.a;
        b *= oth.b;
        getJian();
        return *this;
    }
    bool operator < (const Frac& oth) const {
        return a * oth.b < b * oth.a;
    }
    bool operator == (const Frac& oth) const {
        return a * oth.b == b * oth.a;
    }
    bool operator <= (const Frac& oth) const {
        return a * oth.b <= b * oth.a;
    }
};