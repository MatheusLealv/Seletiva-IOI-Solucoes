#include <bits/stdc++.h>
#define N 400
#define f first
#define s second
#define mp make_pair
using namespace std;

vector<pair< pair<int, int>, pair<int, int> > > A;
int peso[N][N], cont = 1, resp = 0, tam[N*N], mapa[N][N], n, pai[N*N], BFS[N][N];

void setpeso(int x, int y)
{
	int id = mapa[x][y];
	int a = mapa[x + 1][y], b = mapa[x - 1][y], c = mapa[x][y + 1], d = mapa[x][y - 1];
	//cout<<id<<" "<<a<<" "<<b<<" "<<c<<" "<<d<<"\n";
	int minia = min(peso[x][y], peso[x + 1][y]), maxa = max(peso[x][y], peso[x + 1][y]);
	int minib = min(peso[x][y], peso[x - 1][y]), maxb = max(peso[x][y], peso[x - 1][y]);
	int minic = min(peso[x][y], peso[x][y + 1]), maxc = max(peso[x][y], peso[x][y + 1]);
	int minid = min(peso[x][y], peso[x][y - 1]), maxd = max(peso[x][y], peso[x][y - 1]);

	if(a > 0) A.push_back(mp(mp(maxa, minia), mp(id, a)));
	if(b > 0) A.push_back(mp(mp(maxb, minib), mp(id, b)));
	if(c > 0) A.push_back(mp(mp(maxc, minic), mp(id, c)));
	if(d > 0) A.push_back(mp(mp(maxd, minid), mp(id, d)));

}

int Find(int x)
{
	if(x == pai[x]) return x;
	return pai[x] = Find(pai[x]);
}

void join(int a, int b)
{
	a = Find(a);
	b = Find(b);
	if(a == b) return;
	if(tam[a] < tam[b]) pai[a] = b;
	else if(tam[a] > tam[b]) pai[b] = a;
	else pai[a] = b, tam[b]++;
}

int f()
{
	queue< pair<int, int> > bfs;

	bfs.push(mp(1, 1));

	BFS[1][1] = 1;

	while(!bfs.empty())
	{
		int x = bfs.front().first, y = bfs.front().second;

		bfs.pop();

		if(x > n || x < 1 || y > n || y < 1) continue;

		if(peso[x + 1][y] <= resp && !BFS[x + 1][y])
		{
			BFS[x + 1][y] = BFS[x][y] + 1;
			bfs.push(mp(x + 1, y));
		}
		if(peso[x - 1][y] <= resp && !BFS[x - 1][y])
		{
			BFS[x - 1][y] = BFS[x][y] + 1;
			bfs.push(mp(x - 1, y));
		}
		if(peso[x][y + 1] <= resp && !BFS[x][y + 1])
		{
			BFS[x][y + 1] = BFS[x][y] + 1;
			bfs.push(mp(x, y + 1));
		}
		if(peso[x][y - 1] <= resp && !BFS[x][y - 1])
		{
			BFS[x][y - 1] = BFS[x][y] + 1;
			bfs.push(mp(x, y - 1));
		}
	}
	return BFS[n][n];
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n;

	for(int i = 1; i<=n; i++)
		for(int j = 1; j<=n; j++) cin>>peso[i][j];

	for(int i = 1; i<=n; i++)
		for(int j = 1; j<=n; j++)
		{
			mapa[i][j] = cont++;
		}

	for(int i = 0; i<= cont; i++) pai[i] = i;

	for(int i = 1; i<=n; i++)
		for(int j = 1; j<= n; j++) setpeso(i, j);

	sort(A.begin(), A.end());

	//cout<<Find(mapa[1][1])<<" "<<Find(mapa[n][n])<<"\n";
	
	for(int i = 0; i< A.size(); i++)
	{
		int a = A[i].second.first, b = A[i].second.second;

		if(Find(mapa[1][1]) == Find(mapa[n][n])) break;

		resp = max(max(A[i].first.first, A[i].first.second), resp);

		join(a, b);

	}
	cout<<resp<<" ";
	cout<<f()<<"\n";
}