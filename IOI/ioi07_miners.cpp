#include <bits/stdc++.h>
#define N 100050
using namespace std;
int n, v[N], dp[4][4][4][4][4];
string s;

int get(char c)
{
	if(c == 'M') return 1;
	else if(c == 'F') return 2;
	else if(c == 'B') return 3;
}

int cont(int a, int b, int c)
{
	int ans = 0;
	if(a == 1 || b == 1 || c == 1) ans++;
	if(a == 2 || b == 2 || c == 2) ans++;
	if(a == 3 || b == 3 || c == 3) ans++;
	return ans;
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	cin>>s;

	for(int i = 0; i<s.size(); i++) v[i + 1] = get(s[i]);

	int k = 0, y = 1;

	for(int i = n; i>=0; i--)
	{

		swap(k, y);

		for(int a = 0; a < 4; a++)
		{
			for(int b = 0; b< 4; b++)
			{
				for(int c = 0; c < 4; c++)
				{
					for(int d = 0; d< 4; d++)
					{
						int A = dp[y][b][ v[i] ][c][d] + cont(a, b, v[i]);
						int B = dp[y][a][b][d][ v[i] ] + cont(c, d, v[i]);
						dp[k][a][b][c][d] = max(A, B);
					}
				}
			}
		}
	}

	cout<<dp[k][0][0][0][0]<<"\n";
}