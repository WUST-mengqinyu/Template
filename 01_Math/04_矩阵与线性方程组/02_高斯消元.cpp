int n;
double b[maxn], c[maxn][maxn];
//c：系数矩阵，b：常数

void guass() {
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++)
            if (fabs(c[j][i]) > eps) {
                for (int k = 1; k <= n; k++) swap(c[i][k], c[j][k]);
                swap(b[i], b[j]);
            }
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            double rate = c[j][i] / c[i][i];
            for (int k = i; k <= n; k++) c[j][k] -= c[i][k] * rate;
            b[j] -= b[i] * rate;
        }
    }
}