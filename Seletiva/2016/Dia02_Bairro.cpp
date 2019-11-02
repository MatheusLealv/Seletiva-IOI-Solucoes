#include <bits/stdc++.h>
#define inf 2000000000
#define N 200050
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

pii best;

int n, k, sz[N], block[N], tot, ans[N];

vector<int> grafo[N], A, B;

int tam(int x, int p)
{
	sz[x] = 1;

	for(auto v: grafo[x])
	{
		if(block[v] || v == p) continue;
	
		sz[x] += tam(v, x);
	}

	return sz[x];
}

void split(int x, int p)
{
	int maior = tot - sz[x];

	for(auto v: grafo[x])
	{
		if(block[v] || v == p) continue;

		split(v, x);

		maior = max(maior, sz[v]);
	}

	if(maior < best.s) best = pii(x, maior);
}

int find_centroid(int x)
{
	best = pii(-1, inf);

	tot = tam(x, x);

	split(x, x);

	return best.f;
}

inline int bsearch(bool flag, int dist)
{
	if(!flag)
	{
		int ini = 0, fim = A.size() - 1, mid, best = -1;

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
		int ini = 0, fim = B.size() - 1, mid, best = -1;

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
