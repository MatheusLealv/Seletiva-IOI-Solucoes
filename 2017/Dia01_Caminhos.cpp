#include <bits/stdc++.h>
#define N 10050
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

ll n, m, d[N], inf = 2000000000000000;

pii dist[N];

vector<pii> grafo[N];

void bfs()
{
	d[1] = 1;

	queue<int> fila;

	fila.push(1);

	while(!fila.empty())
	{
		int x = fila.front();

		fila.pop();

		for(auto v: grafo[x])
		{
			if(d[v.f]) continue;

			d[v.f] = d[x] + 1;

			fila.push(v.f);
		}
	}

	for(int i = 1; i <= n; i++) d[i] --;
}

ll check(ll k)
{
	for(int i = 1; i <= n; i++) dist[i] = {inf, inf};

	dist[1] = {0, 0};

	priority_queue < pair<ll, pii>, vector<pair<ll, pii> >, greater < pair<ll, pii> > > pq;

	pq.push({0, {0, 1}});

	while(!pq.empty())
	{
		ll x = pq.top().s.s, y = pq.top().s.f, d = pq.top().f;

		pq.pop();

		if(pii(d, y) > dist[x]) continue;

		for(auto v: grafo[x])
		{
			pii novo = {d + v.s + k, y + 1};

			if(dist[v.f] > novo)
			{
				dist[v.f] = novo;

				pq.push({dist[v.f].f, {dist[v.f].s, v.f}});
			}
		}
	}

	ll mx = -inf;

	for(int i = 1; i <= n; i++) mx = max(mx, -d[i] + dist[i].s);

	return mx;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>m;

	for(int i = 1, a, b, c; i <= m; i++)
	{
		cin>>a>>b>>c;

		grafo[a].push_back({b, c});

		grafo[b].push_back({a, c});
	}

	bfs();

	ll ini = 0, fim = 1000000000000ll, mid, best = -1;

	while(fim >= ini)
	{
		mid = (ini + fim)/2;

		ll mx = check(mid);

		if(mx > 0) ini = mid + 1;

		else fim = mid - 1, best = mid;
	}

	cout<<best<<"\n";
}