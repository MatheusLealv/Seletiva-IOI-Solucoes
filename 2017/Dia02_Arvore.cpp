#include <bits/stdc++.h>
#define gc getchar_unlocked
#define N 500011
#define log 19
#define mid ((a + b)/2)
using namespace std;

int n, v[N], cnt, q, nivel[N], pai[N], anc[N][log], start[N];

vector<int> val, grafo[N];

map<int, int> mapa;

inline int scan()
{
	int a = 0, x = gc(), sign = 1;

	for(;x < '0' || x > '9'; x = gc())if(x == '-') sign =-1;

	for(;x >= '0' && x <= '9'; x = gc()) a = (a<<3) + (a<<1) + x - '0';

	return a*sign;
}

struct node
{
	int sum;

	node *l, *r;

	node(){sum = 0, l = r = NULL;}
};

node *version[N];

void build(node *root, int a, int b)
{
	if(a == b) root->sum = 0;
	else
	{
		root->l = new node(), root->r = new node();

		build(root->l, a, mid), build(root->r, mid + 1, b);

		root->sum = root->l->sum + root->r->sum;
	}
}

void update(node *prev, node *root, int a, int b, int i)
{
	if(a == b)
	{
		root->sum = prev->sum + 1;

		return;
	}

	if(i <= mid)
	{
		root->r = prev->r;

		if(!root->l) root->l = new node();

		update(prev->l, root->l, a, mid, i);
	}

	else
	{
		root->l = prev->l;

		if(!root->r) root->r = new node();

		update(prev->r, root->r, mid + 1, b, i);
	}

	root->sum = root->l->sum + root->r->sum;
}

int query(node *A, node *B, node *LCA, int Ancestor, int a, int b, int k)
{
	if(a == b) return a;

	int qtdA = A->l->sum, qtdB = B->l->sum, qtdC = LCA->l->sum, dx = (a <= v[Ancestor] && v[Ancestor] <= mid ? 1 : 0);

	int cont = qtdA + qtdB - 2*qtdC + dx;

	if(cont >= k) return query(A->l, B->l, LCA->l, Ancestor, a, mid, k);

	return query(A->r, B->r, LCA->r, Ancestor, mid + 1, b, k - cont);
}

void dfs(int x, int p)
{
	version[x] = new node();

	update(version[p], version[x], 1, n, v[x]);

	for(int i = 0; i < grafo[x].size(); i++)
	{
		int v = grafo[x][i];

		if(v == p) continue;

		anc[v][0] = x, nivel[v] = nivel[x] + 1;

		dfs(v, x);
	}
}

void compress()
{
	sort(val.begin(), val.end());

	for(int i = 0; i < val.size(); i++) if(!mapa[val[i]]) mapa[val[i]] = ++cnt, start[mapa[val[i]]] = val[i];

	for(int i = 1; i <= n; i++) v[i] = mapa[v[i]];
}

int lca(int u, int v)
{
	if(nivel[v] > nivel[u]) swap(u, v);

	for(int i = log - 1; i >= 0; i--)
		if(nivel[u] - (1<<i) >= nivel[v])
			u = anc[u][i];

	if(u == v) return u;

	for(int i = log - 1; i >= 0; i--)
		if(anc[u][i] != -1 && anc[u][i] != anc[v][i])
			u = anc[u][i], v = anc[v][i];

	return anc[u][0];
}


void Init()
{
	version[0] = new node();

	build(version[0], 1, n);

	nivel[0] = 0;

	memset(anc, -1, sizeof anc);

	anc[1][0] = 1;

	dfs(1, 0);

	for(int j = 1; j < log; j++)
		for(int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	n = scan(), q = scan();

	for(int i = 1; i <= n; i++) v[i] = scan(), val.push_back(v[i]);

	compress();

	for(int i = 1, a, b; i < n; i++)
		a = scan(), b = scan(), grafo[a].push_back(b), grafo[b].push_back(a);

	Init();

	while(q--)
	{
		int i, j, k;

		k = scan(), i = scan(), j = scan();

		int LCA = lca(i, j);

		cout<<start[query(version[i], version[j], version[lca(i, j)], LCA, 1, n, k)]<<"\n";
	}
}