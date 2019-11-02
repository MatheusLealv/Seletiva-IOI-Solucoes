#include <bits/stdc++.h>
#define f first
#define s second
#define N 1000005
#define inf 1000000000000LL
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

ll n, K, v[N], sum[N], pos = 0, qcnt;

pii dp[N];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>K;

	for(int i = 1; i <= n; i++) cin>>v[i], sum[i] = sum[i - 1] + v[i];

	ll ini = 0, fim = inf, mid;

	for(int cnt = 0; cnt < 45; cnt ++)
	{
		mid = (ini + fim)/2;

		pii best = pii(0, 0);

		for(int i = 1; i <= n; i++)
		{
			best = max(best, pii(dp[i - 1].f - sum[i - 1], dp[i - 1].s) );

			dp[i] = max(dp[i - 1], pii(best.f + sum[i] - mid, best.s + 1));
		}

		qcnt = dp[n].s;

		if(qcnt > K) ini = mid;

		else if(qcnt < K)fim = mid;
	}

	pii best = pii(0, 0);

	for(int i = 1; i <= n; i++)
	{
		best = max(best, pii(dp[i - 1].f - sum[i - 1], dp[i - 1].s) );

		dp[i] = max(dp[i - 1], pii(best.f + sum[i] - mid, best.s + 1));
	}

	cout<<max(0LL, dp[n].f + mid*K)<<"\n";
}
© 2019 GitHub, Inc.
