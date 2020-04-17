const int maxn = 1005;
struct String{
    int nex[maxn];
    char x[maxn];
    int len;
    int getLength() {
        return len;
    }
    void getNext() {
        int n = len, i = 0, j = -1;
        nex[0] = -1;
        while (i < n) {
            if (j == -1 || x[i] == x[j]) nex[++i] = ++j;
            else j = -1;
        }
    }
    void input() {
        scanf("%s", x);
        len = strlen(x);
    }
    void inputAndCal() {
        scanf("%s", x);
        len = strlen(x);
        getNext();
    }
    void show() {
        printf("%s\n", x);
    }
    bool operator < (const String&oth) const {
        return strcmp(x, oth.x) < 0;
    }
    char operator [] (const int a) const {
        return x[a];
    }
    bool substring(String b) {//b is the substring of a
        int m = len, n = b.getLength();
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (j == -1 || x[i] == b[j]) ++i, ++j;
            else j = b.nex[j];
            if (j == n) return true;
        }
        return false;
    }
};