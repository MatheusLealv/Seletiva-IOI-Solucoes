#include <bits/stdc++.h>
#define N 300010
#define mid ((a + b)/2)
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

int n, k, v[N], L[N], R[N];

vector<int> w[N];

struct node
{
	pii maxr;

	node *l, *r;

	node(){maxr = {0,0}, l = r = NULL;}
};

void build(node *root, int a, int b)
{
	if(a == b)
	{
		root->maxr = {0, 0};

		return;
	}

	root->l = new node(), root->r = new node();

	build(root->l, a, mid), build(root->r, mid + 1, b);
}

void update(node *prev, node *root, int a, int b, int i, int x)
{
	if(i > b || i < a || b < a) return;

	if(a == b)
	{
		root->maxr = {x, i};

		return;
	}

	if(i <= mid)
	{
		root->r = prev->r;

		if(!root->l)root->l = new node();

		update(prev->l, root->l, a, mid, i, x);
	}
	else
	{
		root->l = prev->l;

		if(!root->r)root->r = new node();

		update(prev->r, root->r, mid + 1, b, i, x);
	}

	root->maxr = max(root->l->maxr, root->r->maxr);
}

pii query(node *root, int a, int b, int i, int j)
{
	//cout<<"query "<<i<<" "<<j<<"\n";
	if(j < a || i > b || !root) return {0, 0};

	if(i <= a && j >= b) return root->maxr;

	pii A = {0, 0}, B = {0, 0};

	if(root->l and i <= mid) A = query(root->l, a, mid, i, j);

	if(root->r and j >= mid + 1) B = query(root->r, mid + 1, b, i, j);

	return max(A, B);
}

node *version[N];

struct tnode
{
	tnode *prox[2];

	int opt[2];

	tnode ()
	{
		prox[0] = prox[1] = NULL;

		opt[0] = N;

		opt[1] = 0;
	}

} *trie;

inline void inserir(tnode *root, int x, int j)
{
	for(int i = 30; i >= 0; i--)
	{
		int b = ((x & (1<<i)) ? 1 : 0);

		root->opt[0] = min(root->opt[0], j);

		root->opt[1] = max(root->opt[1], j);
		
		if(!root->prox[b]) root->prox[b] = new tnode();

		root = root->prox[b];
	}

	root->opt[0] = min(root->opt[0], j);

	root->opt[1] = max(root->opt[1], j);
}
// 0 = menor indice, 1 = maior indice
inline int nulo(int tipo)
{
	if(tipo == 0) return N;

	return 0;
}

inline int find(tnode *root, int x, int tipo)
{
	int ans[2] = {N, 0};

	for(int i = 30; i >= 0; i--)
	{
		if(!root) return ans[tipo];

		int bx = ((x & (1<<i)) ? 1 : 0);

		int bk = ((k & (1<<i)) ? 1 : 0);

		if(bk == 1)
		{
			if(root->prox[bx])
			{
				ans[0] = min(ans[0], root->prox[bx]->opt[0]);

				ans[1] = max(ans[1], root->prox[bx]->opt[1]);
			}

			root = root->prox[!bx];
		}
		
		else
		{
			if(!root->prox[bx]) return ans[tipo];

			root = root->prox[bx];
		}
	}

	if(!root) return ans[tipo];

	ans[0] = min(ans[0], root->opt[0]);

	ans[1] = max(ans[1], root->opt[1]);

	return ans[tipo];
}

inline int solve()
{
	vector<pii> lista;

	lista.push_back({1, n});

	int ans = 0;

	while(!lista.empty())
	{
		auto w = lista.back();

		lista.pop_back();

		int ini = w.f, fim = w.s;

		if(fim < ini) continue;

		pii cara = query(version[ini], 1, n, ini, fim);

		if(cara.f > fim)
		{
			lista.push_back({ini, cara.s - 1});

			lista.push_back({cara.s + 1, fim});
		}
		
		else ans = max(ans, fim - ini + 1);
	}

	return ans;
}

void build()
{
	trie = new tnode();

	for(int i = 1; i <= n; i++)
	{
		L[i] = find(trie, v[i], 1);

		w[L[i]].push_back(i);

		inserir(trie, v[i], i);
	}

	trie = new tnode();

	for(int i = n; i >= 1; i--)
	{
		R[i] = find(trie, v[i], 0);

		inserir(trie, v[i], i);

		//cout<<"range "<<i<<" "<<L[i]<<" "<<R[i]<<"\n";
	}

	version[0] = new node();

	build(version[0], 1, n);

	for(int i = 0; i <= n; i++)
	{
		node *atual = version[i];

		for(auto r: w[i])
		{
			node *novo = new node();

			update(atual, novo, 1, n, r, R[r]);

			atual = novo;
		}

		version[i + 1] = atual;
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>k;

	k--;

	for(int i = 1; i <= n; i++) cin>>v[i];

	build();

	cout<<solve()<<"\n";
}
