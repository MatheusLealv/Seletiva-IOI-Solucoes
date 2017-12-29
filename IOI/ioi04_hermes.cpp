#include <bits/stdc++.h>
#define inf 0x3f3f3f
#define N 20050
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

int n, dp[4][2050][4];

pii v[N];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	v[0].f = v[0].s = 1000;

	for(int i = 1; i <= n; i++)
	{
		cin>>v[i].f>>v[i].s;

		v[i].f += 1000;

		v[i].s += 1000;
	}

	for(int i = n - 1; i >= 0; i--)
	{
		int x, y, a = i%2, b = (i + 1)%2;

		x = v[i].f;

		for(y = 0; y <= 2005; y++)
		{
			dp[a][y][0] = min(dp[b][y][0] + abs(x - v[i + 1].f), dp[b][x][1] + abs(y - v[i + 1].s));
		}

		y = v[i].s;

		for(x = 0; x <= 2005; x++)
		{
			dp[a][x][1] = min(dp[b][x][1] +  abs(y - v[i + 1].s), dp[b][y][0] + abs(v[i + 1].f - x));
		}
	}

	cout<<dp[n%2 == 0? n%2 : (n + 1)%2][v[0].f][0]<<"\n";

}