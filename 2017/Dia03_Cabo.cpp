#include <bits/stdc++.h>
#define N 52
#define inf 2000000000
using namespace std;

int n, v[N], s, dp[N][N/2][N*N];

int solve(int i, int q, int l)
{
	if(i > n) return (!q ? abs(2*l - s) : inf);

	if(dp[i][q][l] != -1) return dp[i][q][l];

	return dp[i][q][l] = min(solve(i + 1, q - 1, l + v[i]), solve(i + 1, q, l));
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(int i = 1; i <= n; i++) cin>>v[i], s += v[i];

	memset(dp, -1, sizeof dp);

	cout<<solve(1, n/2, 0)<<"\n";
}