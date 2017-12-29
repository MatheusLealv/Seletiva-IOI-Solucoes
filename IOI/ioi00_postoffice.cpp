#include <bits/stdc++.h>
#define N 400
#define inf 0x3f3f3f3f
using namespace std;

int n, K, v[N], sum[N], dist[N][N], dp[N][N], pos[N][N], p[N], from[N][N];

void print( int n, int p ) {
    if ( p == 0 ) return ;
    print( from[n][p] - 1, p - 1 );

    cout<<v[(from[n][p] + n)/2]<<" ";
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>K;

	for(int i = 1; i <= n; i++) cin>> v[i];

	sort(v + 1, v + n + 1);

	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			int mid = (i + j)/2;
			for(int k = min(i, j); k <= max(i, j); k++)
			{
				dist[i][j] += abs( v[mid] - v[k] );
			}
		}
	}

	memset(dp, inf, sizeof dp);

	dp[0][0] = 0;

	//for(int i = 1; i <= n; i++) dp[i][1] = dist[1][i];

	for(int k = 1; k <= K; k++)
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= i; j++)
			{
				if(dp[j - 1][k - 1] + dist[i][j] < dp[i][k])
				{
					dp[i][k] = dp[j - 1][k - 1] + dist[i][j];

					from[i][k] = j;
				}
			}
		}
	}

	cout<<dp[n][K]<<"\n";

	print(n, K);

}