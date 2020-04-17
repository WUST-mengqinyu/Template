// 清零 head 和 tot
const int maxm = 4e5+5;
int ver[maxm], Next[maxm], head[maxn], edge[maxm];
void addEdge(int u, int v, int w){
    ver[++tot]=v;
    Next[tot]=head[u];
    head[u]=tot;
    edge[tot]=w;
}

for(int i = head[u]; i; i=Next[i])