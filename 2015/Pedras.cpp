#include <bits/stdc++.h>
#define N 100010
using namespace std;

int n, q, v[N], cnt, raiz, L, R, freq[N], best, qtd_resp[N], ans[N];

vector<int> val;

map<int, int> comp;

struct query
{
	int l, r, id;
};

bool compi(query A, query B)
{
	if(A.l/raiz != B.l/raiz) return A.l/raiz < B.l/raiz;

	return A.r < B.r;
}

query Q[N];

void add(int i)
{
	//cout<<"add "<<i<<"\n";

	qtd_resp[freq[v[i]]] --;

	freq[v[i]] ++;

	qtd_resp[freq[v[i]]] ++;

	best = max(best, freq[v[i]]);
}

void remove(int i)
{
	//cout<<"remove "<<i<<"\n";

	qtd_resp[freq[v[i]]] --;

	freq[v[i]] --;

	qtd_resp[freq[v[i]]] ++;

	if(!qtd_resp[best]) best --;
}

int solve(int i)
{
	//cout<<"Query "<<Q[i].l<<" "<<Q[i].r<<"\n";

	while(L < Q[i].l)
	{
		remove(L);
		L++;
	}

	while(L > Q[i].l)
	{
		L--;
		add(L);
	}

	while(R < Q[i].r)
	{
		R++;
		add(R);
	}

	while(R > Q[i].r)
	{
		remove(R);
		R--;
	}

	return best;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>q;

	raiz = sqrt(n);

	for(int i = 1; i <= n; i++) cin>>v[i], val.push_back(v[i]);

	sort(val.begin(), val.end());

	for(int i = 0; i < val.size(); i++)
		if(!comp[val[i]]) comp[val[i]] = ++cnt;

	for(int i = 1; i <= n; i++) v[i] = comp[v[i]];

	for(int i = 1; i <= q; i++) cin>>Q[i].l>>Q[i].r, Q[i].id = i;

	sort(Q + 1, Q + q + 1, compi);

	for(int i = 1; i <= q; i++) ans[Q[i].id] = solve(i);

	for(int i = 1; i <= q; i++) cout<<ans[i]<<"\n";
}