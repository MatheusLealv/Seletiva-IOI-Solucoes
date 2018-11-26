#include <bits/stdc++.h>
#define f first
#define s second
#define N 2000002
#define logn 22
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int n, q, T[N], cor[N], ok[N], cnt = 1, l, r, anc[N][logn], best[N][logn], nivel[N], pai[N], peso[N];

ll sum[N], k;

char op;

pii query[N];

vector<pii> grafo[N], MST[N];

inline int check(int u, int v)
{
	if(nivel[u] < nivel[v]) swap(u, v);

	int resp = 0;

	for(int i = logn - 1; i >= 0; i--)
		if(nivel[u] - (1<<i) >= nivel[v]) resp = max(resp, best[u][i]), u = anc[u][i];

	if(u == v) return resp;

	for(int i = logn - 1; i >= 0; i--)
		if(anc[u][i] != -1 && anc[u][i] != anc[v][i])
			resp = max(max(resp, best[u][i]), best[v][i]), u = anc[u][i], v = anc[v][i];

	return max(max(resp, best[u][0]), best[v][0]);
}

vector< pair<int, pii > > A;

void dfs0(int x, int p)
{
	T[x] = 1;

	anc[x][0] = p;

	nivel[x] = nivel[p] + 1;

	for(auto v: MST[x])
	{
		if(v.f == p) continue;

		best[v.f][0] = v.s;

		dfs0(v.f, x);
	}
}

int Find(int x)
{
	if(x == pai[x]) return x;

	return pai[x] = Find(pai[x]);
}

inline void join(int a, int b)
{
	a = Find(a), b = Find(b);

	if(a == b) return;

	if(peso[a] > peso[b]) pai[b] = a;

	else if(peso[a] < peso[b]) pai[a] = b;

	else pai[a] = b, peso[b] ++;
}

inline void init()
{
	sort(A.begin(), A.end());

	for(int i = 0; i <= n; i++) pai[i] = i;

	for(auto x: A)
	{
		int a = x.s.f, b = x.s.s, d = x.f;

		if(Find(a) == Find(b)) continue;

		join(a, b);

		MST[a].push_back({b, d});

		MST[b].push_back({a, d});
	}

	memset(anc, -1, sizeof anc);

	for(int i = 0; i <= n; i++)
	{
		if(T[i]) continue;

		dfs0(i, i);
	}

	for(int j = 1; j < logn; j++)
	{
		for(int i = 0; i <= n; i++)
		{
			if(anc[i][j - 1] == -1) continue;

			anc[i][j] = anc[anc[i][j - 1]][j - 1];

			best[i][j] = max(best[anc[i][j - 1]][j - 1], best[i][j - 1]);
		}
	}
}

void dfs(int x)
{
	ok[x] = 1;

	cor[x] = cnt;

	for(auto v: grafo[x])
	{
		if(ok[v.f]) continue;

		ll sign = (v.f < x ? -1: 1), c = v.s;

		sum[v.f] = sum[x] + sign*c;

		dfs(v.f);
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>q;

	for(int i = 1; i <= q; i++)
	{
		cin>>op;

		if(op == 'C')
		{
			cin>>l>>r;
			
			query[i] = {l, r};
		}

		else
		{
			cin>>l>>r>>k;

			grafo[l - 1].push_back({r, k});

			grafo[r].push_back({l - 1, k});

			A.push_back({i, {l - 1, r}});
		}
	}

	for(int i = 0; i <= n + 1; i++)
	{
		if(!ok[i])
		{
			++cnt;

			dfs(i);
		}
	}

	init();

	for(int i = 1; i <= q; i++)
	{
		if(query[i] == pii(0, 0)) continue;

		else
		{
			int u = query[i].s, v = query[i].f - 1;

			if(cor[u] == cor[v] and check(u, v) <= i) cout<<sum[ query[i].s ] - sum[ query[i].f - 1 ]<<"\n";

			else cout<<"Esquecido\n";
		}
	}
}