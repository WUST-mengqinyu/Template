const int maxn = 1e5 + 10;

char s[maxn];

char tmp[maxn << 1];
int Len[maxn << 1];

int init(char *str)
{
    int len = strlen(str);
    tmp[0] = '@';
    for (int i = 1; i <= 2 * len; i += 2)
    {
        tmp[i] = '#';
        tmp[i + 1] = str[i / 2];
    }
    tmp[2 * len + 1] = '#';
    tmp[2 * len + 2] = '$';
    tmp[2 * len + 3] = 0;
    return 2 * len + 1;
}

int manacher(char *str)
{
    int mx = 0, ans = 0, pos = 0;
    int len = init(str);
    for (int i = 1; i <= len; i++)
    {
        if (mx > i) Len[i] = min(mx - i, Len[2 * pos - i]);
        else Len[i] = 1;
        while (tmp[i - Len[i]] == tmp[i + Len[i]]) Len[i]++;
        if (Len[i] + i > mx) mx = Len[i] + i, pos = i;
    }
}