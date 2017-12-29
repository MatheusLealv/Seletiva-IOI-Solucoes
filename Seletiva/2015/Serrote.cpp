#include <bits/stdc++.h>
#define mod (1000000007LL)
using namespace std;
typedef long long ll;

ll dp[1050][1050];

ll solve(int n, int k)
{
    if(n == 0 || k < 0) return 0;

    if(n <= 2 && k == 0) return n;

    if(dp[n][k] != -1) return dp[n][k];

	return dp[n][k] = (solve(n - 1, k)*2*(k + 1) + solve(n - 1, k - 1)*(n - 2*k))%mod;
}

int n, k;

int main()
{
	cin>>n>>k;

	memset(dp, -1, sizeof dp);

	cout<<solve(n, k)<<"\n";
}