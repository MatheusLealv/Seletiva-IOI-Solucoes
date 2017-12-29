#include <bits/stdc++.h>
#define int long long
#define N 100050
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

int n, m, k, dist[N], cor[N], cnt, leaf[N][2], best;

vector< pii > grafo[N];

vector<int> lista[N], v;

void dfs(int x, int p, int c, int flag)
{
	lista[c].push_back(x);

	cor[x] = c;

	for(int i = 0; i < grafo[x].size(); i++)
	{
		int v = grafo[x][i].f, d = grafo[x][i].s;

		if(v == p) continue;

		dist[v] = dist[x] + d;

		dfs(v, x, c, flag);
	}
}

void dist_leaf(int x, int p, int k)
{
	for(int i = 0; i < grafo[x].size(); i++)
	{
		int v = grafo[x][i].f, d = grafo[x][i].s;

		if(v == p ) continue;

		leaf[v][k] = leaf[x][k] + d;

		dist_leaf(v,x, k);
	}
}

vector<int> ans;

void diameter(int c)
{
	int x = lista[c][0], dmax = -1, A = x, B;

	for(int i = 0; i < lista[c].size(); i++)
	{
		int v = lista[c][i];

		if(dist[v] > dmax)
		{
			dmax = dist[v];

			A = v;
		}
	}

	dist[A] = dmax = 0;

	dfs(A, A, c, 0);

	for(int i = 0; i < lista[c].size(); i++)
	{
		int v = lista[c][i];

		if(dist[v] > dmax)
		{
			dmax = dist[v];

			B = v;
		}
	}

	best = max(best, dmax);

	leaf[A][0] = leaf[B][1] = 0;

	dist_leaf(A, A, 0);

	dist_leaf(B, B, 1);

	int DMAX = 100000000000000000;

	for(int i = 0; i < lista[c].size(); i++)
	{
		int v = lista[c][i];

		DMAX = min(DMAX, max(leaf[v][0], leaf[v][1]));
	}

	ans.push_back(DMAX);
}

 main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>m>>k;

	for(int i = 1, a, b, c; i <= m; i++)
	{
		cin>>a>>b>>c;

		a++, b++;

		grafo[a].push_back(pii(b, c));

		grafo[b].push_back(pii(a, c));
	}

	memset(dist, -1, sizeof dist);

	for(int i = 1; i <= n; i++)
	{
		if(dist[i] == -1)
		{
			dist[i] = 0;

			dfs(i, i, cnt++, 1);

			diameter(cnt - 1);
		}
	}

	sort(ans.rbegin(), ans.rend());

	if(ans.size() > 1) best = max(best, ans[0] + ans[1] + k);

	if(ans.size() > 2) best = max(best, ans[1] + ans[2] + 2*k);

	cout<<best<<"\n";
}