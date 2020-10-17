const static int N = 4e6 + 6;
typedef long long ll;
ll pos[N];
const ll mod = 998244353, root = 3;
inline ll fastpow(ll a, ll b) {
    ll ans = 1;
    for (;b;a=a*a%mod,b>>=1) if(b&1)ans=ans*a%mod;
    return ans;
}
inline void exgcd(ll a,ll b,ll &g,ll &x,ll &y) {
    if (!b) g=a,x=1,y=0;
    else exgcd(b,a%b,g,y,x),y-=x*(a/b);
}
inline ll inv(ll a) {
   ll g,x,y;
    exgcd(a,mod,g,x,y);
    return (x%mod+mod)%mod;
}
void init(const int &n) {
    for (int i = 0,j=0; i < n; ++i) {
        pos[i]=j;for (int l = n >> 1; (j ^= l) < l; l >>= 1);
    }
}
void transform(ll *a, const int &n, bool inverse) {
    for (int i=0; i<n;++i) if(i>pos[i]) swap(a[i],a[pos[i]]);
    for (int l=2; l<=n;l<<=1) {
        int m=l/2;ll omega=fastpow(inverse?inv(root):root,(mod-1)/l);
        for (ll *p=a;p!=a+n;p+=l) {
            ll x=1;
            for (int i=0;i<m;++i,x=x*omega%mod) {
                ll t=x*p[m+i]%mod;
                p[m+i]=(p[i]-t+mod)%mod;(p[i]+=t)%=mod;
            }
        }
    }
}
void dft(ll *a, const int &n) {
    transform(a,n,0); 
}
void idft(ll *a, const int &n) {
    const ll INV=inv(n);
    transform(a,n,1);
    for (int i=0;i<n;i++) a[i]=a[i]*INV % mod;
}
const int maxn=4e6+6;
ll a[maxn],b[maxn],c[maxn],pic[maxn],pec[maxn],plc[maxn],ppc[maxn];
int INV[maxn];
void poly_inv(int n,ll *a,ll *b) {
	if(n==1) {b[0]=inv(a[0]);return;}
	poly_inv((n+1)/2,a,b);
	int cnt=1;while(cnt<=n*2) cnt<<=1;init(cnt);
	copy(a,a+n,pic);fill(pic+n,pic+cnt,0);fill(b+n,b+cnt,0);dft(pic,cnt);dft(b,cnt);
	for(int i=0;i<cnt;i++) (b[i]*=(2ll-pic[i]*b[i])%mod)%=mod;
	for(int i=0;i<cnt;i++) b[i]=(b[i]+mod)%mod;
	idft(b,cnt);fill(b+n,b+cnt,0);
}
void poly_ln(int n,ll *a,ll *b) { //G'=F'/F
    poly_inv(n,a,b);
    int cnt=1;while(cnt<=n*2-3) cnt<<=1;init(cnt);
    for(int i=0;i<n-1;i++) plc[i]=a[i+1]*(i+1)%mod;
    fill(plc+n-1,plc+cnt,0);fill(b+n,b+cnt,0);dft(plc,cnt);dft(b,cnt);
    for(int i=0;i<cnt;i++) b[i]=plc[i]*b[i]%mod;
	idft(b,cnt);for(int i=n-1;i>=1;i--) b[i]=b[i-1]*INV[i]%mod;b[0]=0;
	fill(b+n,b+cnt,0);
}
void poly_exp(int n,ll *a,ll *b) {
	if(n==1) {b[0]=1;return;}
	poly_exp((n+1)/2,a,b);poly_ln(n,b,pec);
	int cnt=1;while(cnt<=n*2-2) cnt<<=1;init(cnt);
	for(int i=0;i<n;i++) pec[i]=(-pec[i]+a[i])%mod;pec[0]+=1;
	dft(pec,cnt);dft(b,cnt);
	for(int i=0;i<cnt;i++) b[i]=(b[i]*pec[i])%mod;
	idft(b,cnt);fill(b+n,b+cnt,0);
}
void poly_pow(int n,ll *a,ll *b,ll k) {
	poly_ln(n,a,ppc);
	for(int i=0;i<n;i++) ppc[i]*=k;
	poly_exp(n,ppc,b);
}
char buff[maxn];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    int n;cin>>n>>buff;
	INV[1]=1;for(int i=2;i<n;++i) INV[i]=(mod-mod/i)*INV[mod%i]%mod;
    ll k=0;
    for(int i=0;buff[i];i++) k=(k*10+buff[i]-'0')%mod;
    for(int i=0;i<n;i++) cin>>a[i];
    poly_pow(n,a,b,k);
    for(int i=0;i<n;i++) cout<<b[i]<<' ';
}