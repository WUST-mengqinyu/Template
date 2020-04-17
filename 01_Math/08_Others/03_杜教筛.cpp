#include <bits/stdc++.h>
#include <tr1/unordered_map>

using namespace std;
typedef long long ll;

const int N = 5e6;

bool vis[N + 1];
int mu[N + 1], sumu[N + 1], prim[N + 1], cnt;

tr1::unordered_map<int, int> Smu;

void get_mu(int n)
{
    mu[1] = 1;
    for(int i = 2; i <= n; i ++)
    {
        if(!vis[i]) { prim[++ cnt] = i; mu[i] = -1; }
        for(int j = 1; j <= cnt && prim[j] * i <= n; j ++)
        {
            vis[prim[j] * i] = 1;
            if(i % prim[j] == 0) break;
            else mu[i * prim[j]] = -mu[i];
        }
    }
    for(int i = 1; i <= n; i ++) sumu[i] = sumu[i - 1] + mu[i];
}

int phi[N + 1]; ll sumphi[N + 1];
tr1::unordered_map<ll, ll> Sphi;

void get(int n)
{
    phi[1] = mu[1] = 1;
    for(int i = 2; i <= n; i ++)
    {
        if(!vis[i])
        {
            prim[++ cnt] = i;
            mu[i] = -1; phi[i] = i - 1;
        }
        for(int j = 1; j <= cnt && prim[j] * i <= n; j ++)
        {
            vis[i * prim[j]] = 1;
            if(i % prim[j] == 0)
            {
                phi[i * prim[j]] = phi[i] * prim[j];
                break;
            }
            else mu[i * prim[j]] = -mu[i], phi[i * prim[j]] = phi[i] * (prim[j] - 1);
        }

    }
    for(int i = 1; i <= n; i ++) sumu[i] = sumu[i - 1] + mu[i], sumphi[i] = sumphi[i - 1] + phi[i];
}

ll getSum_mu(int x)
{
    if(x <= N) return sumu[x];
    if(Smu[x]) return Smu[x];
    int ans = 1;
    for(int l = 2, r; l >= 0 && l <= x && r < 2147483647; l = r + 1)
    {
        r = x / (x / l);
        ans -= (r - l + 1) * getSum_mu(x / l);
    }
    return Smu[x] = ans;
}

ll getSum_phi(ll x)
{
    if(x <= N) return sumphi[x];
    if(Sphi[x]) return Sphi[x];
    ll ans = x * (x + 1) / 2;
    for(ll l = 2, r; l <= x; l = r + 1)
    {
        r = x / (x / l);
        ans -= (r - l + 1) * getSum_phi(x / l);
    }
    return Sphi[x] = ans;
}