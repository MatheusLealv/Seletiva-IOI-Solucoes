#include <bits/stdc++.h>
#define N 10005
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

vector<pii> grafo[N];

ll n, k, dp[N][60], ans = 2000000000000000000LL;

void solve(ll x, ll p)
{
	for(auto v: grafo[x])
	{
		if(v.f == p) continue;

		solve(v.f, x);

		for(ll q = k; q >= 0; q--)
			for(ll j = 0; j <= q; j++)
				dp[x][q] = min(dp[x][q], dp[x][q - j] + dp[v.f][j] + v.s);
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>k;

	for(ll i = 1, a, b, c; i < n; i++)
	{
		cin>>a>>b>>c;

		grafo[a].push_back({b, c});

		grafo[b].push_back({a, c});
	}

	for(ll i = 0; i < N; i++)
		for(ll j = 2; j < 60; j++)
			dp[i][j] =  2000000000000000000LL;

	solve(1, 1);

	for(ll i = 1; i <= n; i++) ans = min(ans, dp[i][k]);

	cout<<ans<<"\n";
}