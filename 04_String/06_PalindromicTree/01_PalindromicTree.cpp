const int maxn = 2e6+6;
const int N = 26;
const int mod = 51123987;

struct Palindromic_Tree {
//    vector<pair<int, int> > next[maxn];
    int next[maxn][N];//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
    int fail[maxn]{};//fail指针，失配后跳转到fail指针指向的节点
    int cnt[maxn]{}; //表示节点i表示的本质不同的串的个数（建树时求出的不是完全的，最后count()函数跑一遍以后才是正确的）
    int num[maxn]{}; //表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数
    int len[maxn]{};//len[i]表示节点i表示的回文串的长度（一个节点表示一个回文串）
    int S[maxn]{};//存放添加的字符
    int last{};//指向新添加一个字母后所形成的最长回文串表示的节点。
    int n{};//表示添加的字符个数。
    int p{};//表示添加的节点个数。
    //0向前加，1向后加字符
    //int last[2];
    //int lpos, rpos;

    int newnode(int l) {//新建节点
//        next[p].clear();
        for (int i = 0; i < N; ++i) next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
        return p++;
    }

    void init() {//初始化
        n = last = p = 0;
        newnode(0);
        newnode(-1);
        S[n] = -1;//开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
        // lpos 为字符串最大长度
        // last[0] = last[1] = 0;
        // lpos = 100000, rpos = lpos - 1;
        // S[lpos - 1] = S[rpos + 1] = -1;
    }

    int get_fail(int x) {//和KMP一样，失配后找一个尽量最长的
        // op 0 向前， 1 向后
        // if (op == 0) while (S[lpos + len[x] + 1] != S[lpos]) x = fail[x];
        // else while(S[rpos - len[x] - 1] != S[rpos]) x = fail[x];
        while (S[n - len[x] - 1] != S[n]) x = fail[x];
        return x;
    }

//    int find(int u, int c) {
//        vector<pair<int, int> > & x = next[u];
//        int sz = x.size();
//        for(int i = 0; i < sz; ++i) {
//            if(x[i].first == c) return x[i].second;
//        }
//        return 0;
//    }

    int add(int c) {
        // 注意清空左右字符
        // if (op == 0) S[--lpos] = c, S[lpos - 1] = -1;
        // else S[++rpos] = c, S[rpos + 1] = -1;
        S[++n] = c;
        int cur = get_fail(last);//通过上一个回文串找这个回文串的匹配位置
//        int x = find(cur, c);
//        if (!x) {
        if (!next[cur][c]) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            int now = newnode(len[cur] + 2);//新建节点
//            x = now;
//            fail[now] = find(get_fail(fail[cur]), c);
//            next[cur].emplace_back(make_pair(c, now));
            fail[now] = next[get_fail(fail[cur])][c];//和AC自动机一样建立fail指针，以便失配后跳转
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
//        last = x;
        // 修改最终长度
        // if (len[last[op]] == rpos - lpos + 1) last[op ^ 1] = last[op];
        last = next[cur][c];
        cnt[last]++;
        return num[last];
    }

    void count() {
        for (int i = p - 1; i >= 0; --i) cnt[fail[i]] += cnt[i];
        //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
    }
} solve;

char s[maxn];

// 求相交回文串数量
ll a[maxn], b[maxn];
int main() {
    solve.init();
    int n;
    scanf("%d", &n);
    scanf("%s", s);
    for (int i = 0; i < n; ++i) a[i] = solve.add(s[i] - 'a');
    solve.init();
    for (int i = n - 1; i >= 0; --i) b[i] = (b[i + 1] + solve.add(s[i] - 'a')) % mod;
    ll res = (b[0] * (b[0] - 1) / 2) % mod;
    for (int i = 0; i < n; ++i) res = ((res - (a[i] * b[i + 1]) + mod) % mod) % mod;
    printf("%lld\n", res);
    return 0;
}
