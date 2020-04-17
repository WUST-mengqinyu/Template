const int maxn = 2e6 + 10;

int trie[maxn][30], tot;
bool flag[maxn];

void insert_ch(char *str)
{
    int len = strlen(str);
    int root = 0;
    for (int i = 0; i < len; i++)
    {
        int id = str[i] - 'a';
        if (!trie[root][id]) trie[root][id] = ++tot;
        root = trie[root][id];
    }
    flag[root] = true;
}

bool find_ch(char *str)
{
    int len = strlen(str);
    int root = 0;
    for (int i = 0; i < len; i++)
    {
        int id = str[i] - 'a';
        if (!trie[root][id]) return false;
        root = trie[root][id];
    }
    return true;
}