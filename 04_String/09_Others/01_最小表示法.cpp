// 0起始
int Gao(char a[], int len) {
    int i = 0, j = 1, k = 0;
    while (i < len && j < len && k < len) {
        int cmp = a[(j + k) % len] - a[(i + k) % len];
        if (cmp == 0) k++;
        else {
            if (cmp > 0) j += k + 1;
            else i += k + 1;
            if (i == j) j ++;
            k = 0;
        }
    }
    return min(i, j);
}