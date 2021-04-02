struct Link_Cut_Tree{
    int top,ch[N][2],ff[N],val[N],tag[N],q[N];
    void init(int n) {
        for (int i=1;i<=n;i++) {
            ch[i][0]=ch[i][1]=ff[i]=tag[i]=0;
        }
    }
    bool isroot(int x) {
        return ch[ff[x]][0]!=x && ch[ff[x]][1]!=x;
    }
    void push_down(int x) {
        if (tag[x]) {
            swap(ch[x][0],ch[x][1]);
            tag[ch[x][0]]^=1;
            tag[ch[x][1]]^=1;
            tag[x]=0;
        }
    }
    void Rotate(int x) {
        int y=ff[x],z=ff[y],k=ch[y][1]==x;
        if (!isroot(y)) {
            ch[z][ch[z][1]==y]=x;
        }
        ff[x]=z;
        ch[y][k]=ch[x][k^1],ff[ch[y][k]]=y;
        ch[x][k^1]=y,ff[y]=x;
    }
    void Splay(int x) {
        top=1;q[top]=x;
        for (int i=x;!isroot(i);i=ff[i]) q[++top]=ff[i];
        for (int i=top;i;i--) push_down(q[i]);
        while(!isroot(x)) {
            int y=ff[x],z=ff[y];
            if (!isroot(y)) {
                if ((ch[y][0]==x)^(ch[z][0]==y)) Rotate(x);
                else Rotate(y);
            }
            Rotate(x);
        }
    }
    void Access(int x) {
        for (int y=0;x;y=x,x=ff[x]) {
            Splay(x);ch[x][1]=y;
        }
    }
    void Makeroot(int x) {
        Access(x);Splay(x);
        tag[x]^=1;
        push_down(x);
    }
    int Findroot(int x) {
        Access(x); Splay(x);
        push_down(x);
        while(ch[x][0]) {
            push_down(x);x=ch[x][0];
        }
        Splay(x);
        return x;
    }
    void Split(int x,int y) {
        Makeroot(x);
        Access(y); Splay(y);
    }
    void Link(int x,int y) {
        Makeroot(x);
        if (Findroot(y)==x) return;
        ff[x]=y;
    }
    void Cut(int x,int y) {
        Makeroot(x);
        if (Findroot(y)!=x || ff[y]!=x || ch[y][0]) return;
        ff[y]=ch[x][1]=0;
    }
    bool Connect(int x,int y) {
        return Findroot(x)==Findroot(y);
    }
}lct;