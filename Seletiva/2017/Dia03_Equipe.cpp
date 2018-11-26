#include <bits/stdc++.h>
#define N 201
#define M 1024
using namespace std;

int A[N], B[N], n, k, dp[M][M];

int solve(int i, int mask1, int mask2)
{
	if(mask1 == (1<<k) - 1 and mask2 == (1<<k) - 1) return 0;

	if(i > n) return 20000000;

	if(dp[mask1][mask2] != -1) return dp[mask1][mask2];

	int f1 = mask1 | A[i];

	int f2 = mask2 | B[i];

	return dp[mask1][mask2] = min(solve(i + 1, mask1, mask2), solve(i + 1, f1, f2) + 1 );
}

int main()
{
	cin>>n>>k;

	for(int i = 1, x, qtd; i <= n; i++)
	{
		cin >> qtd;

		B[i] = (1 << k) - 1;

		while(qtd--)
		{
			cin >> x;

			A[i] |= (1 << (x - 1));
		}

		B[i] ^= A[i];
	}

	memset(dp, -1, sizeof dp);

	int ans = solve(1, 0, 0);

	cout<<(ans <= n ? ans : -1)<<'\n';

	return 0;
}