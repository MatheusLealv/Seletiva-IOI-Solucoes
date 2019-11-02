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

void fastscan(ll &number)
{
    bool negative = false;
    register ll c;

    number = 0;

    c = getchar();

    if (c=='-')
    {
        negative = true;

        c = getchar();
    }

    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;

    if (negative)
        number *= -1;
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	fastscan(n), fastscan(K);

	for(int i = 1; i <= n; i++) fastscan(v[i]), sum[i] = sum[i - 1] + v[i];

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
