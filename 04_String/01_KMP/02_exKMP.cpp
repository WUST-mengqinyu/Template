const int maxn = 1e5 + 10;
int nex[maxn], extend[maxn];

//预处理计算Next数组
void getNext(char *str)
{
    int i = 0, j, po, len = strlen(str);
    nex[0] = len;     //初始化nex[0]
    while (str[i] == str[i + 1] && i + 1 < len) i++;   //计算nex[1]
    nex[1] = i;
    po = 1;   //初始化po的位置
    for (int i = 2; i < len; i++)
    {
        if (nex[i - po] + i < nex[po] + po)  //第一种情况，可以直接得到nex[i]的值
            nex[i] = nex[i - po];
        else    //第二种情况，要继续匹配才能得到nex[i]的值
        {
            j = nex[po] + po - i;
            if (j < 0) j = 0;    //如果i>po+nex[po],则要从头开始匹配
            while (i + j < len && str[j] == str[j + i]) j++;
            nex[i] = j;
            po = i;   //更新po的位置
        }
    }
}

void EXKMP(char *s1, char *s2)
{
    int i = 0, j, po, len = strlen(s1), l2 = strlen(s2);
    getNext(s2);
    while (s1[i] == s2[i] && i < l2 && i < len) i++;
    extend[0] = i;
    po = 0;
    for (int i = 1; i < len; i++)
    {
        if (nex[i - po] + i < extend[po] + po)
            extend[i] = nex[i - po];
        else
        {
            j = extend[po] + po - i;
            if (j < 0) j = 0;
            while (i + j < len && j < l2 && s1[j + i] == s2[j]) j++;
            extend[i] = j;
            po = i;
        }
    }
}