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

template <typename T>
class pfenwick {
public:
    vector<vector<pair<int, T>>> fw;
    int n;

    pfenwick(int _n) : n(_n + 1) 
    {
        fw.resize(n);
    }

    void upd(int i, int v, T val)
    {
        auto &tmp = fw[i];
        if (tmp.empty() || tmp.back().se < val) tmp.pb({v, val});
    }

    void modify(int v, int pos, T val) 
    {
        while (pos <= n)
        {
            upd(pos, v, val);
            pos += pos & -pos;
        }
    }

    T get(int i, int v) 
    {
        auto &tmp = fw[i];
        T ret = 0;
        int l = 0, r = sz(tmp)-1;
        while (l <= r) {
            int m = l+r>>1;
            if (tmp[m].fi <= v) {
                ret = tmp[m].se;
                l = m+1;
            } 
            else r = m-1;
        }
        return ret;
    }

    T query(int v, int pos)
    {
        T ret = 0;
        while (pos > 0)
        {
            ckmax(ret, get(pos, v));
            pos -= pos & -pos;
        }
        return ret;
    }
};

void sol()
{
    int n, q; cin >> n >> q;
    v64 a(n); for (auto &x: a) cin >> x;
    v32 r(q), x(q);
    for (auto i=0; i<q; i++) cin >> r[i] >> x[i];

    v32 val;
    val.reserve(n+q);
    for (auto i: a) val.pb(i);
    for (auto i: x) val.pb(i);
    sort(all(val));
    val.erase(unique(all(val)), val.end());
    int m = sz(val);

    auto comp = [&](int u)
    {
        int idx = int(lower_bound(all(val), u) - val.begin());
        return idx+1;
    };
    v64 acomp(n);
    for (int i=0; i<n; i++) acomp[i] = comp(a[i]);
    
    pfenwick<int> fw(m);
    v64 dp(n+1, 0);
    for (int i=1; i<=n; i++)
    {
        int crr = acomp[i-1], prev = fw.query(i-1, crr-1);
        dp[i] = prev+1;
        fw.modify(i, crr, dp[i]);
    }

    for (int i=0; i<q; i++) cout << fw.query(r[i], comp(x[i])) << el;
}

int32_t main()
{
    io();
    sol();
    cerr << "\nTime elapsed: " << 1000*clock()/CLOCKS_PER_SEC << "ms\n";
}