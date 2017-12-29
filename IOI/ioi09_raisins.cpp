#include <bits/stdc++.h>
#define N 55
#define inf 0x3f3f3f3f
using namespace std;

int n, m, dp[N][N][N][N], mat[N][N], bit[N][N];

void upd(int x, int y, int v)
{
	if(!x || !y) return;

	for(int i = x; i < N; i += (i&-i))
		for(int j = y; j < N; j += (j&-j)) bit[i][j] += v;
}

int query(int x, int y)
{
	if(!x || !y) return 0;

	int sum = 0;

	for(int i = x; i > 0; i -= (i&-i))
		for(int j = y; j > 0; j -= (j&-j))
			sum += bit[i][j];

	return sum;
}

int sum(int xi, int yi, int xii, int yii)
{
	if(xi > xii) swap(xi, xii);
	if(yi > yii) swap(yi, yii);

	int A = query(xii, yii);

	int B = query(xii, yi - 1);

	int C = query(xi - 1, yii);

	int D = query(xi - 1, yi - 1);

	return A - B - C + D;
}

int solve(int xi, int yi, int xii, int yii)
{
	if(xi == xii && yi == yii) return 0;

	if(dp[xi][yi][xii][yii] != -1) return dp[xi][yi][xii][yii];

	int ans = inf, s = sum(xi, yi, xii, yii);

	for(int i = xi; i < xii; i++)
	{
		ans = min(ans, solve(xi, yi, i, yii) + solve(i + 1, yi, xii, yii) + s);
	}

	for(int i = yi; i < yii; i++)
	{
		ans = min(ans, solve(xi, yi, xii, i) + solve(xi, i + 1, xii, yii) + s);
	}

	return dp[xi][yi][xii][yii] = ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>m;

	memset(dp, -1, sizeof dp);

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
		{
			cin>>mat[i][j];

			upd(i, j, mat[i][j]);
		}

	cout<<solve(1, 1, n, m)<<"\n";
}