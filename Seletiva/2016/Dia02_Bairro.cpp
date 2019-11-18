#include <bits/stdc++.h>
#define inf 2000000000
#define N 400050
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

pii best;

int n, k, sz[N], block[N], tot, ans[N], vis[N];

int pai[N], viss[N];

vector<int> grafo[N], A, B;

vector<int> lista;

int deep[N], tempo;

bool cmp(int a, int b)
{
	return deep[a] > deep[b];
}

inline int find_centroid(int u)
{
	lista.clear();

	++tempo;

	queue<int> fila;

	fila.push(u);

	int qtd = 0;

	deep[u] = 1;

	while(!fila.empty())
	{
		int x = fila.front();

		lista.push_back(x);

		//cout<<x<<" "<<deep[x]<<"\n";

		qtd ++;

		fila.pop();

		viss[x] = tempo;

		for(auto v: grafo[x])
		{
			if(viss[v] != tempo and !block[v])
			{
				viss[v] = tempo;

				deep[v] = deep[x] + 1;

				fila.push(v);
			}
		}
	}

	sort(lista.begin(), lista.end(), cmp);

	for(auto x: lista)
	{
		sz[x] = 1;

		int maior = 0;

		for(auto v: grafo[x])
			if(deep[v] > deep[x] and !block[v])
			{
				maior = max(maior, sz[v]);
				sz[x] += sz[v];
			}

		maior = max(maior, qtd - sz[x]);

		if(maior <= qtd/2) return x;
	}
}

inline int bsearch(bool flag, int dist)
{
	if(!flag)
	{
		int ini = 0, fim = (int)A.size() - 1, mid, best = -1;

		while(fim >= ini)
		{
			mid = (ini + fim)/2;

			if(A[mid] <= k - dist)
			{
				best = mid;

				ini = mid + 1;
			}

			else fim = mid - 1;
		}

		return best + 1;
	}

	else
	{
		int ini = 0, fim = (int)B.size() - 1, mid, best = -1;

		while(fim >= ini)
		{
			mid = (ini + fim)/2;

			if(B[mid] <= k - dist)
			{
				best = mid;

				ini = mid + 1;
			}

			else fim = mid - 1;
		}

		return best + 1;
	}
}

void update(int x, int p, int dist, bool flag)
{
	if(dist > k) return;

	if(x <= n && flag) A.push_back(dist);

	if(x <= n && !flag) B.push_back(dist);

	for(auto v: grafo[x])
	{
		if(block[v] || v == p) continue;

		update(v, x, dist + 1, flag);
	}
}

void query(int x, int p, int dist)
{
	if(dist > k) return;

	int A = bsearch(0, dist), B = bsearch(1, dist);

	ans[x] += A - B;

	for(auto v : grafo[x])
	{
		if(block[v] || v == p) continue;

		query(v, x, dist + 1);
	}
}

void solve(int x)
{		
	x = find_centroid(x);

	block[x] = 1;

	A.clear();

	update(x, x, 0, 1);

	sort(A.begin(), A.end());

	ans[x] += bsearch(0, 0);

	for(auto v: grafo[x])
	{
		if(block[v]) continue;

		B.clear();

		update(v, x, 1, 0);

		sort(B.begin(), B.end());

		query(v, x, 1);

	}

	for(auto v : grafo[x]) if(!block[v]) solve(v);
}

void dfs(int x)
{
	cout<<"dfs "<<x<<"\n";
	viss[x] = 1;

	for(auto v: grafo[x])
		if(!viss[v]) dfs(v);
}

queue<int> fila;


int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>k;

	for(int i = 1, a, b; i < n; i++)
	{
		cin>>a>>b;

		grafo[a].push_back(n + i);

		grafo[n + i].push_back(a);

		grafo[n + i].push_back(b);

		grafo[b].push_back(n + i);
	}
	solve(1);

	int best = 0;

	if(k%2 == 0) for(int i = 1; i <= n; i++) best = max(best, ans[i]);

	else for(int i = n + 1; i <= 2*n; i++) best = max(best, ans[i]);

	cout<<best<<"\n";
}
