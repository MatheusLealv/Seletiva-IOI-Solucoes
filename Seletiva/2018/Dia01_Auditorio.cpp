#include <bits/stdc++.h>
#define N 255
#define M 62550
using namespace std;

int n, k, v[N], dp[N][M], opt[N][M];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>k;

	for(int i = 1; i <= n; i++) cin>>v[i];

	for(int x = 0; x < M; x ++)
	{
		int ok = 0;

		for(int i = n; i >= 0; i--)
		{
			if(ok or !x) dp[i][x] = 1, opt[i][x] = ok;

			else dp[i][x] = 0;

			if(!ok and x >= v[i] and dp[i][x - v[i]]) ok = i;
		}
	}

	if(dp[0][k])
	{
		cout<<"S\n";

		int id = opt[0][k], sum = k;

		while(id)
		{
			sum -= v[id];

			cout<<id-1<<" ";

			id = opt[id][sum];
		}

		cout<<"\n";
	}

	else cout<<"N\n";
}