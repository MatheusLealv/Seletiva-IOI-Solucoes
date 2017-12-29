#include <bits/stdc++.h>
#define N 100050
#define l (2*nod)
#define r (2*nod + 1)
#define mid ((a + b)/2)
using namespace std;

int x, y, tree[4*N], lazy[4*N];

inline void prop(int nod, int a, int b)
{
	if(lazy[nod] != -1)
	{
		tree[nod] = lazy[nod]*(b - a + 1);

		if(a != b)
		{
			lazy[l] = lazy[r] = lazy[nod];
		}

		lazy[nod] = -1;
	}
}

void upd(int nod, int a, int b, int i, int j, int x)
{
	prop(nod, a, b);

	//cout<<"UPDATE "<<a<<" "<<b<<"\n";

	if(j < a || i > b) return;

	if(i <= a && j >= b)
	{
		tree[nod] = (b - a + 1)*x;

		if(a != b)
		{
			lazy[l] = lazy[r] = x;
		}

		return;
	}

	upd(l, a, mid, i, j, x), upd(r, mid + 1, b, i, j, x);

	tree[nod] = tree[l] + tree[r];
}

int query(int nod, int a, int b, int i, int j)
{
	prop(nod, a, b);

	if(j < a || i > b) return 0;

	if(i <= a && j >= b) return tree[nod];

	return query(l, a, mid, i, j) + query(r, mid + 1, b, i, j);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>x>>y;

	int ans = 1;

	memset(lazy, -1, sizeof lazy);

	for(int i = 1; i < y; i++)
	{
		int p, pp;

		cin>>p>>pp;

		upd(1, 0, x, p, pp, 1);

		if(query(1, 0, x, 0, x) == x + 1)
		{
			upd(1, 0, x, 0, x, 0);

			upd(1, 0, x, p, pp, 1);
			ans += 2;
		}

	}

	cout<<ans<<"\n";
}