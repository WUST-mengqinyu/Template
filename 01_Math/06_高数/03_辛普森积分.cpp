typedef double ld;
ld a, b, c, d;
inline ld f(ld x) { return (c * x + d) / (a * x + b); }
inline ld simpson(ld l, ld r, ld fl, ld fr, ld fm) { return (r - l) * (fl + fr + 4 * fm) / 6; }

inline ld asr(ld l, ld r, ld eps, ld fl, ld fr, ld fm) {
    ld flm = f((l + (l + r) / 2) / 2), frm = f((r + (l + r) / 2) / 2);
    ld L = simpson(l, (l + r) / 2, fl, fm, flm), R = simpson((l + r) / 2, r, fm, fr, frm), A = simpson(l, r, fl, fr, fm);
    if (fabs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15;
    return asr(l, (l + r) / 2, eps / 2, fl, fm, flm) + asr((l + r) / 2, r, eps / 2, fm, fr, frm);
}

inline ld cal(ld l, ld r) { return asr(l, r, 1e-10, f(l), f(r), f((l + r) / 2)); }