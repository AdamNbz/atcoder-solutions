/*
Author : Nguyen Vo Ngoc Bao
School : University of Information Technology, VNU-HCM
*/
#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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

int pop_cnt(ll mask) { return __builtin_popcountll(mask); }
int ctz(ull mask) { return __builtin_ctzll(mask); }
int logOf(ull mask) { return 63 - __builtin_clzll(mask); }

const ll mod = (ll)(1e9+7);
const ll inf = (ll)(2e18);

void sol()
{
    int n, m, q; cin >> n >> m >> q;
    vs grid(n+1);
    vv64 color(n+1, v64(m+1)), cnt(n+1, v64(m+1)), c(n+1, v64(m+1)), r(n+1, v64(m+1));
    int x1, y1, x2, y2, node, edge, row, col;

    for (int i=1; i<=n; i++) cin >> grid[i];

    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
            color[i][j] = (int)(grid[i][j-1])-48;
    
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=m; j++)
        {
            if (color[i][j] == color[i-1][j] && color[i][j] == 1)
            {
                cnt[i][j]++;
                r[i][j]++;
            }
            if (color[i][j] == color[i][j-1] && color[i][j] == 1)
            {
                cnt[i][j]++;
                c[i][j]++;
            }
        }
    }

    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=m; j++)
        {
            color[i][j] += color[i][j-1] + color[i-1][j] - color[i-1][j-1];
            cnt[i][j] += cnt[i][j-1] + cnt[i-1][j] - cnt[i-1][j-1];
            r[i][j] += r[i][j-1];
            c[i][j] += c[i-1][j];
        }
    }

    while (q--)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        node = color[x2][y2] - color[x2][y1-1] - color[x1-1][y2] + color[x1-1][y1-1];
        edge = cnt[x2][y2] - cnt[x2][y1-1] - cnt[x1-1][y2] + cnt[x1-1][y1-1];
        row = r[x1][y2] - r[x1][y1-1];
        col = c[x2][y1] - c[x1-1][y1];
        cout << node-edge+col+row << el;
    }
}

int32_t main()
{
    io();
    sol();
    cerr << "\nTime elapsed: " << 1000*clock()/CLOCKS_PER_SEC << "ms\n";
}