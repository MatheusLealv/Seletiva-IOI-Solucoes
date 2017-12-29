#include <bits/stdc++.h>
#define N 6000
using namespace std;

int n, best = 1000000000;

string s, x, y;

int dp[5][N];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	cin>>s;

	memset(dp, 0, sizeof dp);

	for(int i = s.size() - 1; i >= 0; i--) x += s[i];

	for(int i = 0; i < s.size(); i++)
	{
		for(int j = 0; j < x.size(); j++)
		{
			if(!i || !j)
			{
				if(s[i] == x[j]) dp[i%2][j] = 1;
				else dp[i%2][j] = 0;
			}
			else
			if(s[i] == x[j])
			{
				dp[i%2][j] = 1 + dp[(i - 1)%2][j - 1];
			}
			else
			{
				dp[i%2][j] = max(dp[(i)%2][j - 1], dp[(i - 1)%2][j]);
			}
		}
	}

	cout<<s.size() - max(dp[0][n - 1], dp[1][n - 1])<<"\n";
}