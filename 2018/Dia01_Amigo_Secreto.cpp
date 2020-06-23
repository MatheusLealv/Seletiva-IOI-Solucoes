// Seletiva IOI 2019 - Dia 01 - Amigo Secreto
// Matheus Leal V

#include <bits/stdc++.h>
#define N 100050
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

ll inf = 200000000000000;

ll n, ok[N], ans, t, pai[N], peso[N], cor[N], cnt, grau[N], custo[N], sum[N], opt[N];

bool inside[N];

vector<ll> v[N], lista, ciclo[N];

vector<pii> grafo[N], G[N], grafo2[N];

ll Find(ll x)
{
	if(x == pai[x]) return x;

	return pai[x] = Find(pai[x]);
}

void join(ll a, ll b, ll c)
{
	a = Find(a), b = Find(b);

	if(a == b)
	{
		opt[a] = min(opt[a], c);

		return;
	}

	t--;

	if(peso[a] > peso[b]) pai[a] = b, opt[b] = min({c, opt[a], opt[b]});

	else if(peso[a] < peso[b]) pai[b] = a, opt[a] = min({c, opt[a], opt[b]});

	else pai[a] = b, opt[b] = min({c, opt[a], opt[b]}), peso[b] ++;
}

void dfscolor(ll x, ll c)
{
	ok[x] = 1, cor[x] = c;

	v[c].push_back(x);

	for(auto v: G[x])
	{
		if(cor[v.f] != -1) continue;

		dfscolor(v.f, c);
	}
}

bool cmp(pii A, pii B)
{
	if(A.s != B.s) return A.s < B.s;

	return A.f < B.f;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(ll i = 1; i <= n; i++) pai[i] = i, opt[i] = inf;

	for(ll i = 1, x, c; i <= n; i++)
	{
		cin>>x>>c;

		grau[x] ++;

		grafo[i].push_back({x, c});

		grafo2[x].push_back({i, c});

		G[i].push_back({x, c});

		G[x].push_back({i, c});

		join(i, x, c);
	}

	memset(cor, -1, sizeof cor);

	for(ll i = 1; i <= n; i++)
	{
		if(cor[i] == -1)
		{
			dfscolor(i, cnt);

			++cnt;
		}
	}

	for(ll i = 1; i <= n; i++) if(!grau[i]) lista.push_back(i);

	for(ll i = 0; i < lista.size(); i++)
	{
		ll x = lista[i];

		for(auto v: grafo[x])
		{
			grau[v.f] --;

			if(!grau[v.f]) lista.push_back(v.f);
		}
	}

	sort(lista.begin(), lista.end());

	for(ll i = 1; i <= n; i++)
		if(!binary_search(lista.begin(), lista.end(), i))
			ciclo[cor[i]].push_back(i), inside[i] = 1;

	for(ll i = 1; i <= n; i++)
	{
		sort(grafo2[i].begin(), grafo2[i].end(), cmp);

		for(auto v: grafo2[i]) sum[i] += v.s;

		if(!inside[i]) continue;

		custo[cor[i]] += sum[i] - grafo2[i].back().s;
	}

	for(ll i = 0; i < cnt; i++)
	{
		ll opt = inf;

		if(v[i].size() == ciclo[i].size()) continue;

		for(auto x: ciclo[i])
		{
			if(grafo2[x].size() <= 1) continue;

			for(auto v: grafo2[x])
			{
				if(!inside[v.f]) continue;

				ll aux;

				if(grafo2[x].back().s != v.s) aux = 0;

				else aux = -(sum[x] - grafo2[x].back().s) + (sum[x] - grafo2[x][grafo2[x].size() - 2].s);

				opt = min(opt, custo[i] + aux);
			}	
		}

		if(opt < inf) ans += opt;
	}

	for(ll i = 0; i < cnt; i++)
	{
		if(v[i].size() != ciclo[i].size()) continue;

		ll x = v[i][0];

		if(cnt > 1) ans += opt[Find(x)];
	}

	for(ll x = 1; x <= n; x++)
	{
		if(inside[x]) continue;

		if(grafo2[x].size() > 1) ans += sum[x] - grafo2[x].back().s;
	}

	cout<<ans<<"\n";
}
