#include <bits/stdc++.h>
#define N 100050
#define logn 20
#define l (2*nod)
#define r (2*nod + 1)
#define mid ((a + b)/2)
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

int n, q, nivel[N], anc[N][logn], dp[N][logn], sub[N], inf = 2000000000;

int ini[N], t[N], fim[N], tempo;

vector<int> grafo[N];

void dfs(int x, int p)
{
	ini[x] = ++tempo;

	t[ini[x]] = x;

	anc[x][0] = p;

	nivel[x] = nivel[p] + 1;

	vector<int> melhor;

	for(auto v: grafo[x])
	{
		if(v == p) continue;

		dfs(v, x);

		melhor.push_back(sub[v]);
	}

	sort(melhor.rbegin(), melhor.rend());

	for(auto v: grafo[x])
	{
		if(v == p) continue;

		int tmp;

		if(melhor[0] == sub[v]) tmp = (melhor.size() > 1 ? melhor[1] + 1 : 0);

		else tmp = melhor[0] + 1;

		dp[v][0] = tmp - nivel[x] + inf;
	}

	sub[x] = (melhor.empty() ? 0 : melhor[0] + 1);

	fim[x] = tempo;
}

int LCA(int u, int v)
{
	if(nivel[u] < nivel[v]) swap(u, v);

	for(int j = logn - 1; j >= 0; j--)
		if(nivel[u] - (1<<j) >= nivel[v])
			u = anc[u][j];

	if(u == v) return u;

	for(int j = logn - 1; j >= 0; j--)
		if(anc[u][j] != -1 and anc[u][j] != anc[v][j])
			u = anc[u][j], v = anc[v][j];

	return anc[u][0];
}

inline int dist(int &u, int &v)
{
	return nivel[u] + nivel[v] - 2*nivel[LCA(u, v)];
}

int tree[4*N];

inline int caso1(int &root, int &x)
{
	int opt = -1, u = x;

	for(int j = logn - 1; j >= 0; j--)
	{
		int v = anc[u][j];

		if(v == -1) continue;

		if(nivel[x] - nivel[v] < (nivel[v] - nivel[root])) u = v;
	}

	opt = sub[u] + nivel[u] - nivel[root];

	opt = max(opt, nivel[anc[u][0]] - nivel[root]);

	return 2*opt;	
}

inline int caso2(int root, int x)
{
	int u = root, opt = -1;

	for(int j = logn - 1; j >= 0; j--)
	{
		int v = anc[u][j];

		if(v == -1) continue;

		if((nivel[root] - nivel[v]) <= (nivel[v] - nivel[x])) u = v;
	}

	int y = u;

	for(int j = logn - 1; j >= 0; j--)
	{
		int v = anc[u][j];

		if(v == -1) continue;

		opt = max(opt, dp[u][j]);
	}

	if(opt > -1) opt += -inf + nivel[root];

	opt = max(opt, dist(anc[y][0], root));

	return 2*max(0, opt);
}

inline int caso3(int &root, int &x, int &L)
{
	int u = x;

	for(int j = logn - 1; j >= 0; j--)
	{
		int v = anc[u][j];

		if(v == -1) continue;

		int dist_root_v = nivel[root] + nivel[v] - 2*nivel[L];

		int dist_x_v = nivel[x] - nivel[v];

		if(dist_x_v < dist_root_v) u = v;
	}

	int opt = sub[u] + nivel[u] + nivel[root] - 2*nivel[L];

	opt = max(opt, dist(anc[u][0], root));

	return 2*opt;
}

inline int caso4(int &root, int &x, int &L)
{
	int u = root;

	for(int j = logn - 1; j >= 0; j--)
	{
		int v = anc[u][j];

		if(v == -1) continue;

		int dist_x_v = nivel[x] + nivel[v] - 2*nivel[L];

		int dist_root_v = nivel[root] - nivel[v];

		if(dist_x_v >= dist_root_v) u = v;
	}

	int y = u, opt = -1;

	for(int j = logn - 1; j >= 0; j--)
	{
		int v = anc[u][j];

		if(v == -1) continue;

		opt = max(opt, dp[u][j]);
	}

	if(opt > -1) opt += -inf + nivel[root];

	opt = max(opt, dist(anc[y][0], root));

	return 2*opt;
}

inline int solve(int &root, int &u)
{
	int L = LCA(root, u);

	if(L == root) return caso1(root, u);

	if(L == u) return caso2(root, u);

	if(nivel[root] <= nivel[u]) return caso3(root, u, L);

	return caso4(root, u, L);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>q;

	for(int i = 1, a, b; i < n; i++)
	{
		cin>>a>>b;

		grafo[a].push_back(b);

		grafo[b].push_back(a);
	}

	memset(anc, -1, sizeof anc);

	memset(dp, -1, sizeof dp);

	dfs(1, 1);

	for(int j = 1; j < logn; j++)
	{
		for(int i = 1; i <= n; i++)
		{
			if(anc[i][j - 1] == -1) continue;

			anc[i][j] = anc[anc[i][j - 1]][j - 1];

  			dp[i][j] = dp[i][j - 1];

  			if(anc[i][j] != -1) dp[i][j] = max(dp[i][j], dp[ anc[i][j - 1] ][j - 1]);
		}
	}

	for(int i = 1; i <= q; i++)
	{
		int root, x, u, opt = -1;

		cin>>root>>x;

		cout<<solve(root, x)<<"\n";
	}
}