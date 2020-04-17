// hash常用素数
// 61, 83, 113, 151, 211
// 91815541, 38734667, 68861641
// 917120411, 687840301, 386910137, 515880193
// 1222827239, 1610612741

typedef unsigned long long ull;
struct mhash {
    // 自然溢出无模数 805306457
    ull base[maxn];
    ull hash_index[maxn];
    ull seed; //31, 131
    void inithash(ull seedt = 31) {
        base[0] = 1;
        seed = seedt;
        for (int i = 1; i < maxn; ++i) base[i] = base[i - 1] * seed;
    }
    void H(char *p, int n) { // from 1 to n
        hash_index[0] = 0;
        for (int i = 1; i <= n; ++i) hash_index[i] = hash_index[i - 1] * seed + p[i] - 'a';
    }
    ull gethash(int s, int e) {
        return hash_index[e] - hash_index[s - 1] * base[e - s + 1];
    }
};

// 26个素数，解决加法hash
int prime[] = {34183,13513,152993,13591,19687,350869,111187,766091,769297,
               633469,752273,298651,617191,880421,136067,
               1408397,726899,458921,2133701,2599847,2730947,4696343,10267237,
               18941059,34078909,69208409};