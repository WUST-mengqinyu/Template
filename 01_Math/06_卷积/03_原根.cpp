#include<bits/stdc++.h>
#define ll long long
#define IL inline
#define RG register
using namespace std;

ll prm[1000],tot,N,root;

ll Power(ll bs,ll js,ll MOD){
    ll S = 1,T = bs;
    while(js){
        if(js&1)S = S*T%MOD;
        T = T*T%MOD;
        js >>= 1;
    } return S;
}

IL ll GetRoot(RG ll n){
    RG ll tmp = n - 1 , tot = 0;
    for(RG ll i = 2; i <= sqrt(tmp); i ++){
        if(tmp%i==0){
            prm[++tot] = i;
            while(tmp%i==0)tmp /= i;
        }
    }
    if(tmp != 1)prm[++tot] = tmp;            //质因数分解
    for(RG ll g = 2; g <= n-1; g ++){
        bool flag = 1;
        for(RG int i = 1; i <= tot; i ++){     //检测是否符合条件
            if(Power(g,(n-1)/prm[i],n) == 1)
                { flag = 0; break; }
        }
        if(flag)return g;
    }return 0;                        //无解
}

int main(){
    cin >> N;
    root = GetRoot(N);
    cout<<root<<endl;
    return 0;
}