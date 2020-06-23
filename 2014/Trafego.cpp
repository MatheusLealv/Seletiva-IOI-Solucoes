#include <bits/stdc++.h>
#define N 50050
#define mp make_pair
#define f first
#define s second
#define pb push_back
#define inf 0x3f3f3f3f
#define llg long long int
#define pb push_back
using namespace std;
typedef pair<int, int> piii;

#define minheap priority_queue <piii, vector<piii>, greater<piii> >

int n, m, dist[N];

struct edge
{
	int x, d, g, r;

	edge(int a1, int d1, int g1, int r1)
	{
		x = a1, d = d1, g = g1, r = r1;
	}
};

vector<edge> grafo[N];

bool check(int g, int r, int time)
{
	int dx = r + g;
	int dt = time%dx;
	if(dt >= g) return 0;
	return 1;
}

int dt(int g, int r, int time)
{
	int dx = time%(r + g);
	return (r + g - dx);
}

int dijkstra()
{
	memset(dist, inf, sizeof dist);

	dist[1] = 0;

	minheap pq;

	pq.push(mp(0,1));

	while(!pq.empty())
	{
		piii P = pq.top();
		
		pq.pop();

		int x = P.s, time = P.f;

		if(time > dist[x]) continue;

		for(int i = 0; i< grafo[x].size(); i++)
		{
			int v = grafo[x][i].x, custo = grafo[x][i].d, g = grafo[x][i].g, r = grafo[x][i].r;

			if(check(g, r, time + custo))
			{
				if(dist[v] > dist[x] + custo)
				{
					dist[v] = dist[x] + custo;
					pq.push(mp(dist[v],v));
				}
			}
			else
			{
				if(dist[v] > dist[x] + dt(g, r, time + custo) + custo)
				{
					dist[v] = dist[x] + dt(g, r, time + custo) + custo;
					pq.push(mp(dist[v], v));
				}
			}
		}	
	}

	return dist[n];

}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin>>n>>m;

	for(int i = 1,a , b, c, d, e; i<=m; i++)
	{
		cin>>a>>b>>c>>d>>e;
		grafo[a].pb(edge(b, c, d, e));
	}

	cout<<dijkstra()<<"\n";
}