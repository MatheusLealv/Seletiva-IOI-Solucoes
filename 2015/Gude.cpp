#include <bits/stdc++.h>
#define inf 200000000000000LL
#define N 300050
#define l (2*nod)
#define r (2*nod + 1)
#define mid ((a + b)/2)
#define int long long
using namespace std;

int n, v[N], dp[N], k, tree[4*N];

void upd(int nod, int a, int b, int i, int x)
{
	if(a == b)
	{
		tree[nod] = x;

		return;
	}

	if(i <= mid) upd(l, a, mid, i, x);

	else upd(r, mid + 1, b, i, x);

	tree[nod] = min(tree[l], tree[r]);
}

int query(int nod, int a, int b, int i, int j)
{
	if(j < a || i > b) return inf;

	if(i <= a && j >= b) return tree[nod];

	return min(query(l, a, mid, i, j), query(r, mid + 1, b, i, j));
}

inline void update(int pos, int val)
{
	upd(1, 0, n, pos, val);
}

inline int query(int a, int b)
{
	return query(1, 0, n, a, b);
}

 main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>k;

	for(int i = 1; i <= n; i++) cin>>v[i];

	sort(v + 1, v + n + 1);

	for(int i = 0; i <= n; i++) update(i, inf);

	dp[0] = 0;

	update(1, -v[1]);

	for(int i = 1; i <= n; i++)
	{
		dp[i] = query(1, i) + v[i] + k;

		update(i + 1, dp[i] - v[i + 1]);
	}

	cout<<dp[n]<<"\n";
}