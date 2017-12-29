#include <bits/stdc++.h>
#define N 1000050
using namespace std;
typedef long long ll;

ll n, peso[N], w[N], pai[N];

vector<ll> grafo[N];

ll dfs(ll x, ll p)
{
	w[x] = peso[x];

	for(int i = 0; i < grafo[x].size(); i++)
	{
		ll v = grafo[x][i];

		if(v == p) continue;

		pai[v] = x;

		w[x] += dfs(v, x);
	}

	return w[x];
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(int i = 1; i <= n; i++) cin>>peso[i];

	for(int i = 1, a, b; i < n; i++)
	{
		cin>>a>>b;

		a++; b++;

		grafo[a].push_back(b);

		grafo[b].push_back(a);
	}

	pai[1] = 1;

	dfs(1, 1);

	ll tot = w[1], ans = 1000000000000000000, id = 0;

	for(ll i = 1; i <= n; i++)
	{
		ll aux = 0, sum = w[i];

		for(ll j = 0; j < grafo[i].size(); j++)
		{
			ll v = grafo[i][j];

			if(grafo[i][j] == pai[i]) continue;

			aux = max(aux, w[v]);
		}

		aux = max(aux, tot - w[i]);

		if(aux < ans)
		{
			ans = aux;
			id = i;
		}
	}

	cout<<id - 1<<"\n";
}