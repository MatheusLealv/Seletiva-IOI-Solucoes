#include <bits/stdc++.h>
#define inf 2000000000
#define N 2000010
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

vector<pii> grafo[N];

int n, k, sz[N], block[N], tot, proc[N], visit[N], cnt, ans = inf;

pii best;

int tam(int x, int p)
{
	sz[x] = 1;

	for(auto v: grafo[x]) if(v.f!= p && !block[v.f]) sz[x] += tam(v.f, x);

	return sz[x]; 
}

void Split(int x, int p)
{
	int maior = tot - sz[x];

	for(auto v: grafo[x])
	{
		if(v.f == p || block[v.f]) continue;

		Split(v.f, x);

		maior = max(maior, sz[v.f]);
	}

	if(maior < best.s) best = pii(x, maior); 
}

int find_centroid(int x)
{
	tot = tam(x, x);

	best = pii(inf, inf);

	Split(x, x);

	return best.f;
}

void update(int x, int p, int dist, int peso)
{
	if(peso > k) return;

	if(visit[peso] < cnt) proc[peso] = dist, visit[peso] = cnt;

	else proc[peso] = min(proc[peso], dist);

	if(peso == k) ans = min(ans, dist);

	for(auto v: grafo[x])
	{
		if(v.f == p || block[v.f]) continue;

		update(v.f, x, dist + 1, peso + v.s);
	}
}

void query(int x, int p, int dist, int peso)
{
	if(peso > k) return;

	if(visit[k - peso] == cnt) ans = min(ans, proc[k - peso] + dist);

	for(auto v: grafo[x])
	{
		if(v.f == p || block[v.f]) continue;

		query(v.f, x, dist + 1, peso + v.s);
	}
}

void solve(int x)
{
	x = find_centroid(x);

	block[x] = 1;

	++cnt;

	for(auto v: grafo[x])
	{
		if(block[v.f]) continue;

		query(v.f, x, 1, v.s);

		update(v.f, x, 1, v.s);
	}

	for(auto v: grafo[x])
	{
		if(block[v.f]) continue;

		solve(v.f);
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>k;

	for(int i = 1, a, b, c; i < n; i++)
	{
		cin>>a>>b>>c;

		a++, b++;

		grafo[a].push_back(pii(b, c));

		grafo[b].push_back(pii(a, c));
	}

	solve(1);
	cout<<(ans >= inf ? -1 : ans)<<"\n";
}