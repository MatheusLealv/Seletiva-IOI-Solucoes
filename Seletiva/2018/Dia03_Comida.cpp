#include <bits/stdc++.h>
#define N 100050
#define l (2*nod)
#define r (2*nod + 1)
#define mid ((a + b)/2)
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

ll n, q, v[N], inf = 200000000000000000, pref[N], soma;

pii tree[4*N];

ll lazy[4*N];

inline void prop(ll nod, ll a, ll b)
{
	if(!lazy[nod]) return;

	tree[nod].f += lazy[nod];

	if(a != b)
	{
		lazy[l] += lazy[nod];

		lazy[r] += lazy[nod];
	}

	lazy[nod] = 0;
}

void build(ll nod, ll a, ll b)
{
	if(a == b)
	{
		tree[nod] = {pref[a], a};

		return;
	}

	build(l, a, mid), build(r, mid + 1, b);

	tree[nod] = min(tree[l], tree[r]);
}

void upd(ll nod, ll a, ll b, ll i, ll j, ll x)
{
	prop(nod, a, b);

	if(j < a or i > b) return;

	if(i <= a and j >= b)
	{
		tree[nod].f += x;

		if(a != b)
		{
			lazy[l] += x;

			lazy[r] += x;
		}

		return;
	}

	upd(l, a, mid, i, j, x), upd(r, mid + 1, b, i, j, x);

	tree[nod] = min(tree[l], tree[r]);
}

pii query(ll nod, ll a, ll b, ll i, ll j)
{
	prop(nod, a, b);

	if(j < a or i > b) return {inf, inf};

	if(i <= a and j >= b) return tree[nod];

	return min(query(l, a, mid, i, j), query(r, mid + 1, b, i, j));
}

inline ll Ans()
{
	if(soma < 0) return 0;

	ll opt = query(1, 1, n, 1, n - 1).s;

	return opt + 1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>q;

	for(ll i = 1, t; i <= n; i++)
	{
		cin>>t>>v[i];

		if(t == 1) v[i] *= -1;

		soma += v[i];
	}

	for(ll i = 1; i <= n; i++) pref[i] = pref[i - 1] + v[i];

	build(1, 1, n);

	ll tt = Ans();

	cout<<tt<<"\n";

	for(ll i = 1; i <= q; i++)
	{
		ll t, p, v;

		cin>>t>>p>>v;

		if(t == 1)
		{
			upd(1, 1, n, p, n, -v);

			soma -= v;
		}

		else
		{
			upd(1, 1, n, p, n, +v);

			soma += v;
		}

		ll tt = Ans();

		cout<<tt<<"\n";
	}
}