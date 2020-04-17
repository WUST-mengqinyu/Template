class AC_automation
{
public:
    int trie[maxn][26], cnt;
    int tag[maxn];
    int fail[maxn], num[maxn], res[maxn], in[maxn], Map[maxn];

    void init()
    {
        memset(trie, 0, sizeof trie);
        memset(tag, 0, sizeof tag);
        memset(fail, 0, sizeof fail);
        cnt = 0;
    }

    void insert(char *str, int id)
    {
        int root = 0;
        for (int i = 0; str[i]; i++)
        {
            int id = str[i] - 'a';
            if (!trie[root][id]) trie[root][id] = ++cnt;
            root = trie[root][id];
        }
        if(!tag[root]) tag[root] = id;
        Map[id] = tag[root];
    }

    void build()
    {
        queue<int> que;
        for (int i = 0; i < 26; i++) if (trie[0][i]) que.push(trie[0][i]);
        while (!que.empty())
        {
            int k = que.front();
            que.pop();
            for (int i = 0; i < 26; i++)
            {
                if (trie[k][i])
                {
                    fail[trie[k][i]] = trie[fail[k]][i];
                    que.push(trie[k][i]);
                    in[fail[trie[k][i]]] ++;
                } else trie[k][i] = trie[fail[k]][i];
            }
        }
    }

    void toposort()
    {
        queue<int> que;
        for(int i = 1; i <= cnt; i ++) if(in[i] == 0) que.push(i);
        while(!que.empty())
        {
            int u = que.front(); que.pop();
            res[tag[u]] = num[u];
            int v = fail[u]; in[v] --;
            num[v] += num[u];
            if(in[v] == 0) que.push(v);
        }
    }

    void query(char *str, int n)
    {
        int u = 0, len = strlen(s);
        for(int i = 0; i < len; i ++)
            u = trie[u][str[i] - 'a'], num[u] ++;
        toposort();
        for(int i = 1; i <= n; i ++) printf("%d\n", res[Map[i]]);
    }
} AC;