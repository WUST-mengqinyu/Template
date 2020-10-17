vector<pair<ll, int> > getFactors(ll x) {
    vector<pair<ll, int>> fact;
    for (int i = 1; prim[i] <= x / prim[i]; i++) {
        if (x % prim[i] == 0) {
            fact.emplace_back(prim[i], 0);
            while (x % prim[i] == 0) fact.back().second++, x /= prim[i];
        }
    }
    if (x != 1) fact.emplace_back(x, 1);
    return fact;
}