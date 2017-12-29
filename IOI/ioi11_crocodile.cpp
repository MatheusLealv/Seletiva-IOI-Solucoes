#include <bits/stdc++.h>
#define inf 2000000000
#define N 100050
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;
#define heap priority_queue<pii, vector<pii>, greater<pii> >

int m, k, n, dist[N], saida[N], removed[N], prev[N], check[N];

vector<pii> original[N], grafo[N];

bool verify(int x)
{
	if(check[x] == 0)
	{
		check[x] = 1;
		return false;
	}

	if(check[x] == 2) return false;

	return true;
}

void bfs()
{
	heap pq;

	int ans = 0;

	for(int i = 1; i <= n; i++) if(saida[i]) check[i] = 1, pq.push(pii(0, i));

	while(!pq.empty())
	{
		int x = pq.top().s, dis = pq.top().f;

		pq.pop();

		if(!verify(x)) continue;

		if(x == 1)
		{
			ans = dis;

			break;
		}

		check[x] = 2;

		for(int i = 0; i < grafo[x].size(); i++)
		{
			int v = grafo[x][i].f, peso = grafo[x][i].s;

			if(check[v] == 2) continue;

			pq.push(pii(dis + peso, v));
		}
	}

	cout<<ans<<"\n";
}

int main()
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


	for(int i = 1, x; i <= k; i++)
	{
		cin>>x;

		saida[x + 1] = 1;
	}

	bfs();

}