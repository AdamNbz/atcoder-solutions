/*
Author : Nguyen Vo Ngoc Bao
School : University of Information Technology, VNU-HCM
*/
#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#ifndef ONLINE_JUDGE
   #if defined(__APPLE__)
      #include </Users/home/Documents/nbz_lib/debug.h>
   #elif defined(_WIN32) || defined(_WIN64)
      #include <C:/Users/Admin/OneDrive/Documents/nbz_lib/debug.h>
   #endif
#else
   #define dbg(...) 
#endif

#define fi first
#define se second
#define el '\n'
#define pb push_back
#define eb emplace_back
#define io() ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((ll)(x).size())
#define mask(i) (1LL << (i))
#define getbit(mask, i) (((mask) >> (i)) & 1)

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> p32;
typedef pair<ll, ll> p64;
typedef pair<double, double> pdd;
typedef vector<int> v32;
typedef vector<vector<int> > vv32;
typedef vector<ll> v64;
typedef vector<vector<ll> > vv64;
typedef vector<p32> vp32;
typedef vector<vector<p32> > vvp32;
typedef vector<p64> vp64;
typedef vector<vector<p64> > vvp64;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vs > vvs;

template<typename T> void ckmin(T& x, T y) {if (x>y) x = y;}
template<typename T> void ckmax(T& x, T y) {if (x<y) x = y;}
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int pop_cnt(ll mask) { return __builtin_popcountll(mask); }
int ctz(ull mask) { return __builtin_ctzll(mask); }
int logOf(ull mask) { return 63 - __builtin_clzll(mask); }
int parity(ull mask) { return __builtin_parityll(mask); }

const ll mod = (ll)(1e9+7);
const ll inf = numeric_limits<ll>::max();

void sol()
{
    int n, k; cin >> n >> k;
    v32 a(n);
    for (auto &x: a) cin >> x;

    int mx = *max_element(all(a));
    v32 cnt(mx+1, 0), dp(mx+1, 0);
    for (auto x: a) cnt[x]++;
    for (int i=1; i<=mx; i++)
        for (int j=i; j<=mx; j+=i) 
            dp[i] += cnt[j];
    
    vv32 cache(mx+1);
    auto cal = [&](int x) -> v32&
    {
        if (cache[x].empty())
        {
            for (int i=1; i*i<=x; i++)
            {
                if (!(x%i))
                {
                    cache[x].pb(i);
                    if (i*i != x) cache[x].pb(x/i);
                }
            }
            sort(rall(cache[x]));
        }
        
        return cache[x];
    };

    if (k == 1)
    {
        for (auto x: a) cout << x << el;
        return;
    }

    for (auto x: a)
    {
        auto crr = cal(x);
        int ans = 1;
        for (auto i: crr)
            if (dp[i] >= k) 
            {
                ans = i;
                break;
            }
        cout << ans << el;
    }
}

int32_t main()
{
    io();
    sol();
    cerr << "\nTime elapsed: " << 1000*clock()/CLOCKS_PER_SEC << "ms\n";
}