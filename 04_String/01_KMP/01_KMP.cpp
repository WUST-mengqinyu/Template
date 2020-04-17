// nxt[0]表示失配到完全不匹配
int nxt[maxm];

void getNext(char *s, int len) {
    int i = 0, j = -1;
    nxt[i] = j;
    while (i < len) {
        if (j == -1 || s[i] == s[j]) nxt[++i] = ++j;
        else j = nxt[j];
    }
}

// a为原串，b为模式串，下标从0开始，找第一个出现模式串的位置（起点为1），找不到返回-1
int KMP(char *a, char *b, int n, int m) {
    getNext(b, m);
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (j == -1 || a[i] == b[j]) ++i, ++j;
        else j = nxt[j];
    }
    return j == m ? i - m + 1 : -1;
}