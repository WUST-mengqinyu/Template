const int maxn = 2e4 + 10;

struct SuffixAutomation
{
	int last, cnt;
	int ch[maxn << 1][26], fa[maxn << 1], len[maxn << 1], pos[maxn << 1];
    int sz[maxn << 1], a[maxn << 1], c[maxn << 1];

	void init()
	{
	    last = cnt = 1;
	    memset(ch[1], 0, sizeof ch[1]);
	    fa[1] = len[1] = 0;
        a[1] = c[1] = 0;
    }

    int inline newnode(int idx)
    {
        ++cnt;
        memset(ch[cnt], 0, sizeof ch[cnt]);
        fa[cnt] = len[cnt] = sz[cnt] = a[cnt] = c[cnt] = 0;
        pos[cnt] = idx;
        return cnt;
    }

	void ins(int c)
	{
		int p = last , np = newnode(pos[last] + 1);
		last = np, len[np] = len[p] + 1;
		for(; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
		if(!p) fa[np] = 1;
		else
		{
			int q = ch[p][c];
			if(len[p] + 1 == len[q]) fa[np] = q;
			else
			{
				int nq = newnode(pos[p] + 1);
				len[nq] = len[p] + 1;
				memcpy(ch[nq], ch[q], sizeof ch[q]);
				fa[nq] = fa[q], fa[q] = fa[np] = nq;
				for(; ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
			}
		}
        sz[np] = 1;
	}

	int solve(int n)
	{
        /*求两个串的LCS:
            对一个字符串建立SAM，记录一个当前匹配的长度Len和当前节点v，枚举另一个字符串的每个字符；
            如果p有字符v的转移边出边，则使Len加一，并使p转移到出边指向的节点上;
            否则不断向父节点上跳，直到当前节点有字符p的转移出边，或者跳到根节点；
        */
        int p = 1, ans = 0, now_len = 0;
        for(int i = 0; s2[i]; i ++)
        {
            if(ch[p][s2[i] - 'a']) p = ch[p][s2[i] - 'a'], now_len ++;
            else
            {
                for(;p && !ch[p][s2[i] -'a'] ; p = fa[p]) ;
                if(p == 0) now_len = 0, p = 1;
                else now_len = len[p] + 1, p = ch[p][s2[i] - 'a'];
            }
            ans = max(now_len, ans);
        }
    }

    void Toposort()
    {
        long long ans = 0;
        for(int i = 1; i <= cnt; i ++) c[len[i]] ++;
        for(int i = 1; i <= cnt; i ++) c[i] += c[i - 1];
        for(int i = 1; i <= cnt; i ++) a[c[len[i]] --] = i;
        for(int i = cnt; i; i --) sz[fa[a[i]]] += sz[a[i]];
    }
}sam;
