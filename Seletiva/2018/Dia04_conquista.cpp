#include <bits/stdc++.h>
#define N 1001
#define inf 2000000000
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

int n, m, mat[N][N], dp[N][N][3], T;

int solve(int x, int y, int dir)
{
	if(x <= 0 or y <= 0 or x > n or y > m) return -inf;

	if(x == n && y == m) return mat[x][y];

	if(dp[x][y][dir] != -1) return dp[x][y][dir];

	if(dir == 0) return dp[x][y][dir] = max(solve(x,y + 1, 0), solve(x + 1, y, 2)) + mat[x][y];

	if(dir == 1) return dp[x][y][dir] = max(solve(x, y - 1, 1), solve(x + 1, y, 2)) + mat[x][y];

	if(dir == 2) return dp[x][y][dir] = max(max(solve(x, y + 1, 0), solve(x, y - 1, 1)), solve(x + 1, y, 2)) + mat[x][y];
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>m;

	memset(dp, -1, sizeof dp);

	for(int i =1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin>>mat[i][j];

	cout<<max(solve(1, 1, 0), solve(1, 1, 2))<<"\n\n";
}