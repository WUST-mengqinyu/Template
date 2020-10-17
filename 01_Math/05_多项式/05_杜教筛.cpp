const int maxn=3e6+5;

unordered_map<int,ll> Mmu;
unordered_map<int,ll> Mphi;
ll mu[maxn],phi[maxn],prim[maxn],pcnt,mn[maxn];
void get_T() {
    phi[1]=mu[1]=1;
    for(int i=2;i<maxn;i++) {
        if(!mn[i]) {
            mn[i]=i;prim[++pcnt]=i;
            phi[i]=i-1;mu[i]=-1;
        }
        for(int j=1;j<=pcnt&&i*prim[j]<maxn;j++) {
            mn[i*prim[j]]=prim[j];
            if(i%prim[j]==0) {
                phi[i*prim[j]]=phi[i]*prim[j];
                break;
            }
            mu[i*prim[j]]=-mu[i];
            phi[i*prim[j]]=phi[i]*(prim[j]-1);
        }
    }
    for(int i=1;i<maxn;i++)
        mu[i]+=mu[i-1],phi[i]+=phi[i-1];
}
ll Smu(int n) {
    if(n==1) return 1;
    if(n<maxn) return mu[n];
    if(Mmu.find(n)!=Mmu.end()) return Mmu[n];
    ll ans=0;
    for(int l=2,r;l<=n;l=r+1) {
        r=min(n,n/(n/l));
        ans+=Smu(n/l)*(r-l+1);
    }
    return Mmu[n]=1-ans;
}
ll Sphi(int n) {
    if(n==1) return 1;
    if(n<maxn) return phi[n];
    if(Mphi.find(n)!=Mphi.end()) return Mphi[n];
    ll ans=0;
    for(int l=2,r;l<=n;l=r+1) {
        r=min(n,n/(n/l));
        ans+=Sphi(n/l)*(r-l+1);
    }
    return Mphi[n]=1ll*n*(n+1)/2-ans;
}
int main() {
    get_T();
    int T;cin>>T;while(T--) {
        int n;cin>>n;
        cout<<Sphi(n)<<' '<<Smu(n)<<endl;
    }
    return 0;
}