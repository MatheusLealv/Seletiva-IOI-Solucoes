#include <bits/stdc++.h>
#define N 100050
#define inf 10000000000000000LL
#define mid ((a + b)/2)
#define l (2*nod)
#define r (2*nod + 1)
using namespace std;

typedef long long ll;

ll n, k, v[N], sum[N];

ll dp[N][5];

ll solve(int i, int cont)
{
	if(cont == 3) return 0;

	if(i > n) return -inf;

	if(dp[i][cont] != -1) return dp[i][cont];

	if(cont == 1)
	{
		ll A = solve(i + k, 2) + sum[i] - sum[i - k];

		ll B = solve(i + 1, 1);

		return dp[i][cont] = max(A, B);
	}
	else
	{
		ll A = solve(i + k, 3) + sum[i] - sum[i - k];

		ll B = solve(i + 1, 2);

		return dp[i][cont] = max(A, B);
	}
}

 main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>k;

	memset(dp, -1, sizeof dp);

	for(int i = 1, x; i <= n; i++)
	{
		cin>>v[i];

		v[i] *= -1;
	}

	for(int i = 1; i <= n; i++)
	{
		sum[i] = sum[i - 1] + v[i];
	}

	cout<<solve(k, 1)<<"\n";

}
