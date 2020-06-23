#include <bits/stdc++.h>
#define N 300010
#define f first
#define s second
using namespace std;
#define int long long
typedef pair<int, int> pii;

int n, m, v[N], sz[N], pai[N], ans[N], q;

vector< pair<int, pii> > A;

vector< pii > pais[N], filhos[N], pref[N];

void join(int a, int b, int c)
{
	a = pai[a], b = pai[b];

	if(a == b) return;

	//a é sempre pai de b
	if(sz[a] < sz[b]) swap(a, b); 

	for(auto w: filhos[b])
	{
		pais[w.s].push_back({c, a});

		filhos[a].push_back({c, w.s});

		int custo = (!pref[a].empty() ? pref[a].back().s : 0) + v[w.s];

		pref[a].push_back({c, custo});

		pai[w.s] = a;
	}

	sz[a] += sz[b];

	ans[a] += ans[b];

	pai[b] = a;
}

int query(int a, int k)
{
	int u = a;

	//subo para os pais até onde der
	for(auto w: pais[a])
		if(w.f <= k)
			u = w.s;

	//depois, olho todos os filhos do maior pai possivel
	int ini = 0, fim = (int) filhos[u].size() - 1, mid, best;

	int resp = 0;

	while(fim >= ini)
	{
		mid = (ini + fim)/2;

		if(pref[u][mid].f <= k)
		{
			best = mid;

			ini = mid + 1;
		}

		else fim = mid - 1;
	}

	return pref[u][best].s;
}

int32_t main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>m;

	for(int i = 1; i <= n; i++)
	{
		cin>>v[i];

		filhos[i].push_back({0, i});

		pref[i].push_back({0, v[i]});

		sz[i] = 1;

		ans[i] = v[i];

		pai[i] = i;
	}

	for(int i = 1, a, b, c; i <= m; i++)
	{
		cin>>a>>b>>c;

		A.push_back({c, {a, b}});
	}

	sort(A.begin(), A.end());

	for(auto w: A)
	{
		int a = w.s.f, b = w.s.s, c = w.f;

		join(a, b, c);
	}

	cin>>q;

	int ant = 0;

	for(int i = 1; i <= q; i++)
	{
		int x, k;

		cin>>x>>k;

		k += ant;

		ant = query(x, k);

		cout<<ant<<"\n";
	}
}
