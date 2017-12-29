#include <bits/stdc++.h>
#define N 2050
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

int n, m, v[N], vaga[N], w[N], ans, ini[N], fim[N];

int avaible[N];

vector<int> fila;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>m;

	for(int i = 1; i <= n; i++) cin>>v[i];

	for(int i = 1; i <= m; i++) cin>>w[i];

	for(int i = 1; i <= n; i++) avaible[i] = 0;

	for(int i = 1; i <= 2*m; i++)
	{
		int id;

		cin>>id;

		if(id > 0) fila.push_back(id);

		if(id > 0) ini[id] = i;
		else fim[-id] = i;
	}

	for(int i = 0; i < fila.size(); i++)
	{
		int id = fila[i]; bool menor = 0; int prox = 0x3f3f3f3f, ji;

		for(int j = 1; j <= n; j++)
		{
			if(avaible[j] <= ini[id])
			{
				avaible[j] = fim[id];
				ans += v[j]*w[id];
				menor = 1;
				break;
			}

			if(avaible[j] < prox)
			{
				prox = avaible[j];
				ji = j;
			}
		}

		if(!menor)
		{
			ans += w[id]*v[ji];
			avaible[ji] = fim[id];
		}
	}

	cout<<ans<<"\n";
}