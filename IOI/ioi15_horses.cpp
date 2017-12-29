#include <bits/stdc++.h>
#define mod 1000000007LL
#define N 500050
#define l (2*nod)
#define ri (2*nod + 1)
#define mid ((a + b)/2)
using namespace std;
typedef long long int ll;

ll n, x[N], y[N], q, tree[4*N], prod = 1, bit[N];

map<ll, ll> mapa;

set<ll> pos;

ll Pow(ll base, ll p)
{
	if(mapa[base] > 0) return mapa[base];

    if(p == 0) return 1;

    if(p == 1) return base%mod;

    ll ans = Pow(base, p/2)%mod;

    ans = (ans*ans)%mod;

    if(p & 1) ans = (ans*base)%mod;

    return mapa[base] = ans%mod;
}

ll inverse(ll x)
{
	ll ans = Pow(x, mod - 2)%mod;

	return ans;
}

void upd(int nod, int a, int b, int i, ll x)
{
	if(i < a || i > b) return;
	if(a == b)
	{
		tree[nod] = x;
		return;
	}
	upd(l, a, mid, i, x), upd(ri, mid + 1,b,  i, x);
	tree[nod] = max(tree[l], tree[ri]);
}

ll query(int nod, int a, int b, int i, int j)
{
	if(j < a || i > b) return 0LL;
	if(i <= a && j >= b) return tree[nod];
	return max(query(l, a, mid, i, j), query(ri, mid + 1, b, i, j));
}

ll getans()
{
	ll acum = 1, resp = 0, p = 1, ini = 1, ans = 0, cont = 0;

	set<ll>::iterator it = --pos.end();

	vector<ll> pii;

	for(int i = 0; i <= 30; i++)
	{
		pii.push_back(*it);

		if(it == pos.begin()) break;

		--it;
	}

	ll dp = 0;

	while(p < mod && cont <= 30)
	{
		ll pi = pii[dp++];

		p *= x[pi];

		if(p >= mod)
		{
			p /= x[pi];
			break;
		}

		if(p >= mod || dp >= pii.size()) break;

		++cont;
	}

	cont = 0;

	ll ant = n + 1;

	dp = 0;

	while(acum < mod && cont <= 30)
	{
		ll pi = pii[dp++];

		ll yi = query(1, 1, n, pi, ant - 1);

		ll aux = (p*inverse(acum))%mod;

		aux = aux*yi;

		if(aux > resp)
		{
			ans = ((prod)*inverse(acum))%mod;
			ans = (yi*ans)%mod;
			resp = aux;
		}

		acum *= x[pi];

		ant = pi;

		if(acum >= mod || dp >= pii.size()) break;

		++cont;
	}

	cout<<ans%mod<<"\n";
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(int i = 1; i <= n; i++) 
	{
		cin>>x[i];

		prod = (prod*x[i])%mod;

		if(x[i] != 1) pos.insert(i);
	}

	pos.insert(0);

	pos.insert(n + 1);

	x[0] = x[n + 1] = y[0] = y[n + 1] = 1;

	for(int i = 1; i <= n; i++)
	{
		cin>>y[i];

		upd(1, 1, n, i, y[i]);
	}

	pos.insert(0);

	cin>>q;

	prod = (mod + prod)%mod;

	getans();

	for(int i = 1; i <= q; i++)
	{
		ll tip, idx, val;

		cin>>tip>>idx>>val;

		idx++;

		if(tip == 2)
		{
			y[idx] = val;

			upd(1, 1, n, idx, y[idx]);
		}
		else
		{
			if(x[idx] == 1 && val != 1) pos.insert(idx);
			else if(x[idx] != 1 && val == 1) pos.erase(idx);

			prod = (prod*inverse(x[idx]))%mod;

			prod = (prod*val)%mod;

			x[idx] = val; 

			prod %= mod;
		}

		getans();
	}
}