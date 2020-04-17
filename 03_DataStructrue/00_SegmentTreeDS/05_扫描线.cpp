// 范用型扫描线，del储存上界+1，add储存下界，先del后add即可
struct node {
    int lpos, rpos, linepos;
    bool operator < (const node& oth) const {
        return linepos < oth.linepos;
    }
};
vector<node> add, del;
int delpos = 0;
int res = 0;
for (int addpos = 0; addpos < add.size(); ++addpos) {
    while (delpos < del.size() && del[delpos].linepos <= add[addpos].linepos) {
        up(del[delpos].lpos, del[delpos].rpos, -1);
        delpos ++;
    }
    up(add[addpos].lpos, add[addpos].rpos, 1);
    res = max(res, val[1]);
}

// 求面积并
#define maxn 222
#define tmp (st<<1)
#define mid ((l+r)>>1)
#define lson l,mid,tmp
#define rson mid+1,r,tmp|1
using namespace std;
int cnt[maxn<<2];
double sum[maxn<<2];
double x[maxn];
struct Seg{
    double h,l,r;
    int s;
    Seg(){}
    Seg(double a,double b,double c,int d):l(a),r(b),h(c),s(d){}
    bool operator<(const Seg &cmp)const{
        return h<cmp.h;
    }
}ss[maxn];
void push_up(int st,int l,int r){
    if(cnt[st])sum[st]=x[r+1]-x[l];
    else if(l==r)sum[st]=0;
    else sum[st]=sum[tmp]+sum[tmp|1];
}
void update(int L,int R,int c,int l,int r,int st){
    if(L<=l&&r<=R){
        cnt[st]+=c;
        push_up(st,l,r);
        return ;
    }
    if(L<=mid)update(L,R,c,lson);
    if(R>mid)update(L,R,c,rson);
    push_up(st,l,r);
}
int main(){
    int n,tot=1,m;
    while(scanf("%d",&n)&&n){
        double a,b,c,d;
        m=0;
        while(n--){
            scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
            x[m]=a;
            ss[m++]=Seg(a,c,b,1);
            x[m]=c;
            ss[m++]=Seg(a,c,d,-1);
        }
        sort(x,x+m);
        sort(ss,ss+m);
        double ans=0;
        for(int i=0;i<m;++i){
            int l=lower_bound(x,x+m,ss[i].l)-x;
            int r=lower_bound(x,x+m,ss[i].r)-x-1;
            update(l,r,ss[i].s,0,m-1,1);
            ans+=sum[1]*(ss[i+1].h-ss[i].h);
        }
        printf("Test case #%dnTotal explored area: %.2lfnn",tot++,ans);
    }
    return 0;
}

// 面积交
#include<bits/stdc++.h>
#define maxn 100005
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define pb push_back
using namespace std;

double tree[maxn<<2],tree2[maxn<<2];
int lazy[maxn<<2];
vector<double>ve;

struct seg{
    double l,r,h;
    int flag;
    seg(){}
    seg(double _l,double _r,double _h,int _flag){l=_l,r=_r,h=_h,flag=_flag;}
    bool operator<(const seg &b)const{return h<b.h;}
}s[maxn];

void push_up(int l,int r,int rt){
    if(lazy[rt]) tree[rt]=ve[r]-ve[l-1];
    else if(l==r) tree[rt]=0;
    else tree[rt]=tree[rt<<1]+tree[rt<<1|1];
}

void push_up2(int l,int r,int rt){
    if(lazy[rt]>1) tree2[rt]=ve[r]-ve[l-1];
    else if(l==r) tree2[rt]=0;
    else if(lazy[rt]==1)tree2[rt]=tree[rt<<1]+tree[rt<<1|1];
    else tree2[rt]=tree2[rt<<1]+tree2[rt<<1|1];
}

void build(int l,int r,int rt){
    tree[rt]=0,lazy[rt]=0;
    if(l==r) return;
    int mid=l+r>>1;
    build(lson);
    build(rson);
}

void add(int L,int R,int v,int l,int r,int rt){
    if(L<=l&&R>=r){
        lazy[rt]+=v;
        push_up(l,r,rt);
        push_up2(l,r,rt);
        return;
    }
    int mid=l+r>>1;
    if(L<=mid) add(L,R,v,lson);
    if(R>mid) add(L,R,v,rson);
    push_up(l,r,rt);
    push_up2(l,r,rt);
}

int getid(double x){ return lower_bound(ve.begin(),ve.end(),x)-ve.begin()+1;}

int main(){
    int n;
    int Case=1;
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        ve.clear();
        int tot=0;
        double x1,y1,x2,y2;
        for(int i=1;i<=n;i++){
            scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2);
            ve.pb(x1),ve.pb(x2);
            s[++tot]=seg(x1,x2,y1,1);
            s[++tot]=seg(x1,x2,y2,-1);
        }
        sort(ve.begin(),ve.end());
        ve.erase(unique(ve.begin(),ve.end()),ve.end());
        sort(s+1,s+tot+1);
        int N=ve.size();
        build(1,N,1);
        double ans=0;
        for(int i=1;i<tot;i++){
            int L=getid(s[i].l);
            int R=getid(s[i].r)-1;
            add(L,R,s[i].flag,1,N,1);
            ans+=tree2[1]*(s[i+1].h-s[i].h);
        }
        printf("%.2f\n",ans);
    }
}

// 求周长并
#include<bits/stdc++.h>
#define maxn 100005
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define pb push_back
using namespace std;

int tree[maxn<<2];
int lazy[maxn<<2];
vector<int>ve[2];
int k;

struct seg{
    int l,r,h;
    int flag;
    seg(){}
    seg(int _l,int _r,int _h,int _flag){l=_l,r=_r,h=_h,flag=_flag;}
    bool operator<(const seg &b)const{return h<b.h;}
}s[maxn];

void push_up(int l,int r,int rt){
    if(lazy[rt]) tree[rt]=ve[k][r]-ve[k][l-1];
    else if(l==r) tree[rt]=0;
    else tree[rt]=tree[rt<<1]+tree[rt<<1|1];
}

void build(int l,int r,int rt){
    tree[rt]=0,lazy[rt]=0;
    if(l==r) return;
    int mid=l+r>>1;
    build(lson);
    build(rson);
}

void add(int L,int R,int v,int l,int r,int rt){
    if(L<=l&&R>=r){
        lazy[rt]+=v;
        push_up(l,r,rt);
        return;
    }
    int mid=l+r>>1;
    if(L<=mid) add(L,R,v,lson);
    if(R>mid) add(L,R,v,rson);
    push_up(l,r,rt);
}

int getid(int x){return lower_bound(ve[k].begin(),ve[k].end(),x)-ve[k].begin()+1;}

int main(){
    int n;
    while(~scanf("%d",&n)){
        ve[0].clear();
        ve[1].clear();
        int x1,y1,x2,y2;
        for(int i=1;i<=n;i++){
            scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
            ve[0].pb(x1),ve[0].pb(x2);
            ve[1].pb(y1),ve[1].pb(y2);
            s[i]=seg(x1,x2,y1,1);
            s[i+n]=seg(x1,x2,y2,-1);
            s[i+n+n]=seg(y1,y2,x1,1);
            s[i+n+n+n]=seg(y1,y2,x2,-1);
        }
        int ans=0;
        int pos=1;
        for(k=0;k<2;k++){
            sort(ve[k].begin(),ve[k].end());
            ve[k].erase(unique(ve[k].begin(),ve[k].end()),ve[k].end());
            sort(s+pos,s+pos+n+n);
            int N=ve[k].size();
            build(1,N,1);
            int pre=0;
            for(int i=pos;i<pos+n+n;i++){
                int L=getid(s[i].l);
                int R=getid(s[i].r)-1;
                add(L,R,s[i].flag,1,N,1);
                ans+=abs(tree[1]-pre);
                pre=tree[1];
            }
            pos+=n+n;
        }
        printf("%d\n",ans);
    }
}