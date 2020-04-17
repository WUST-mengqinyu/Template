// 适用于正负整数
template <class T>
inline bool scan(T &ret){
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; //EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

template <class T>
inline void write(int x, int digit=10) {
    static int sta[35];
    int top = 0;
    do {
      sta[top++] = x % digit, x /= digit;
    } while (x);
    while (top) putchar(sta[--top] + 48);
}

inline int read() {
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}