const int maxn=1e6+5;
int primer[maxn],pcnt;
bool insp[maxn];
ll fsum1[maxn],fsum2[maxn];
const int mod=1e9+7,INV6=166666668;
void sieve() {
	for(int i=2;i<maxn;i++) {
		if(!insp[i]) {
			primer[++pcnt]=i;
			fsum1[pcnt]=(fsum1[pcnt-1]+i)%mod;
			fsum2[pcnt]=(fsum2[pcnt-1]+1ll*i*i)%mod;
		}
		for(int j=1;j<=pcnt&&primer[j]*i<maxn;j++) {
			insp[i*primer[j]]=1;
			if(i%primer[j]==0) break;
		}
	}
}

// Let g(j,m) be the sum of f'(i) for all i which is not greater
// than m and is prime or the min pri-factor of i > p[j] 
// We got that g(j,m)=g(j−1,m)−f'(p[j])*( g(j−1,m/p[j])−\sum_{i=1}^{j−1}f'(p[i]) )
// g(0,m) = \sum_{i=2}^m f'(j)
// Here f'(j) is a function whose value equals f(j) when j is prime 
// and f'(j) is an acompletely multiplicative function
// We can use DP to calc g(j,{n/1,n/2,...,n/n}) (sqrt(n) situation in total)
// So g(j,m) equals to the sum of f(i) for all primer i which not greater than m
//  when p[j]*p[j] > m
int id1[maxn],id2[maxn],tot=0;
ll val[maxn],n,g1[maxn],g2[maxn];
//index of n/1,n/2....n/n
inline int getid(ll m) {
	if(m<=n/m) return id1[m];
	return id2[n/m];
}
void init() {
	for(ll l=1,r;l<=n;l=r+1) {
		r=n/(n/l);ll w=n/l;
		val[++tot]=w;
		if(w<=n/w) id1[w]=tot;
		else id2[n/w]=tot;
		w%=mod;
		g1[tot]=w*(w+1)/2%mod;
		g2[tot]=w*(w+1)%mod*(2ll*w+1)%mod*INV6%mod;
		g1[tot]=(g1[tot]-1+mod)%mod;
		g2[tot]=(g2[tot]-1+mod)%mod;
	}
	// Start DP
	for(int i=1;1ll*primer[i]*primer[i]<=n;i++) {
		for(int j=1;j<=tot&&1ll*primer[i]*primer[i]<=val[j];j++) {
			int k=getid(val[j]/primer[i]);
			g1[j]=(g1[j]-1ll*primer[i]*(g1[k]-fsum1[i-1]+mod)%mod+mod)%mod;
			g2[j]=(g2[j]-1ll*primer[i]*primer[i]%mod*(g2[k]-fsum2[i-1]+mod)%mod+mod)%mod;
		}
	}	
}
ll getS(ll m,int k) {
	if(m<primer[k]) return 0;
	ll res=(g2[getid(m)]-g1[getid(m)]-fsum2[k-1]+fsum1[k-1])%mod;
	for(int i=k;1ll*primer[i]*primer[i]<=m;i++) {
		for(ll pie=primer[i],pie1=pie*primer[i];pie1<=m;pie=pie1,pie1*=primer[i]){
			ll t1=pie%mod,t2=pie1%mod;
			res=(res+t1*(t1-1)%mod*getS(m/pie,i+1)%mod+t2*(t2-1)%mod)%mod;
		}
	}
	return (res+mod)%mod;
}
int main() {
    sieve();cin>>n;	
    init();
    // for(int i=1;i<=10;i++) cout<<g1[i]<<endl;
    // cout<<g1[1]<<endl;
    cout<<(getS(n,1)+1)%mod<<endl;
    return 0;
}