#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 5e5+5;
pair<int, int> a[maxn];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].second >> a[i].first;
    }
    sort(a + 1, a + 1 + n);
    int res = 1;
    int tmp = a[1].first;
//    printf("%d %d\n", a[1].second, a[1].first);
    for (int i = 2; i <= n; ++i) {
        if (a[i].second > tmp) {
            res ++;
//            printf("%d %d\n", a[i].second, a[i].first);
            tmp = a[i].first;
        }
    }
    printf("%d\n", res);
    return 0;
}

