// ---
// $p$小$n$,$m$大
// ---

const int NICO = 100000+10;
const int MOD  = 99991;
ll f[NICO];  

ll Lucas(ll a,ll k) 
{  
    ll res = 1;  
    while(a && k)  
    {  
        ll a1 = a % MOD;
        ll b1 = k % MOD;  
        if(a1 < b1) return 0;
        res = res*f[a1]*qp(f[b1]*f[a1-b1]%MOD,MOD-2)%MOD;
        a /= MOD;  
        k /= MOD;  
    }  
    return res;  
}  

void init()  
{  
    f[0] = 1;
    for(int i=1;i<=MOD;i++) 
    { 
        f[i] = f[i-1]*i%MOD;    
    }
}  

int main()  
{  
    init();
    cout << Lucas(5,2) << endl;
}