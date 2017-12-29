#include <bits/stdc++.h>
#define N 100050
using namespace std;

int n, Viz[N], Tempo[N][2], resp;

bool doente[N];

vector<int> grafo[N];

void Reset(int x)
{
	Tempo[x][0] = max(Tempo[x][0], 0);

	Tempo[x][1] = max(Tempo[x][1], 0);

	Viz[x] = max(Viz[x], 0);
}

void propag(int x, int p, int maior)
{
	if(!Tempo[x][0]) doente[x] = 1, Tempo[x][1] = 0, resp ++;

	else if(Viz[x] == 1 && p == -1) resp ++, doente[x] = 1;

	else if(Viz[x] == 1) return;

	else if(!Viz[x]) Tempo[x][1] = maior + 1, doente[x] = 1;

	else doente[x] = 1, Tempo[x][1] = 0, resp ++;
}

void solve(int x, int p)
{
	vector<int> infec;

	int maior = -1;

	for(auto v: grafo[x])
	{
		if(v == p) continue;

		solve(v, x);

		if(!doente[v]) Tempo[x][0] = min(Tempo[x][0], Tempo[v][0] - 1);

		else infec.push_back(Tempo[v][1]);
	}

	sort(infec.begin(), infec.end());

	for(auto v: infec) if(v < Tempo[x][0] && Viz[x]) maior = v, Viz[x] --;

	Reset(x);

	propag(x, p, maior);

}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(int i = 1; i <= n; i++) cin>>Viz[i]>>Tempo[i][0];

	for(int i = 1, a, b; i < n; i++) cin>>a>>b, grafo[a].push_back(b), grafo[b].push_back(a);

	solve(1, -1);

	cout<<resp<<"\n";
}