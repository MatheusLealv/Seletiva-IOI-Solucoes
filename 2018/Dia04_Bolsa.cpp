#include <bits/stdc++.h>
#define N 1000050
#define inf 2000000000
#define f first
#define s second
#define mid ((a + b)/2)
#define l (2*nod)
#define r (2*nod + 1)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct ss {
	int x, id, tip;
};

bool cmp(ss A, ss B){
	if(A.x != B.x) return A.x < B.x;
	return A.tip < B.tip;
}

int n, m, k, c[N], t[N], par[N], q, x[N], y[N], ini[N];

ll ans[N], tree[4*N];

void upd(int nod, int a, int b, int i, ll x)
{
	if(i < a or i > b) return;

	if(a == b)
	{
		tree[nod] = min(tree[nod], x);

		return;
	}

	upd(l, a, mid, i, x), upd(r, mid + 1, b, i, x);

	tree[nod] = min(tree[l], tree[r]);
}

ll query(int nod, int a, int b, int i, int j)
{
	if(j < a or i > b) return inf;

	if(i <= a and j >= b) return tree[nod];

	return min(query(l, a, mid, i, j), query(r, mid + 1, b, i, j));
}

vector<int> pos[N];

vector<ss> sweep;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>m>>k;

	for(int i = 1; i <= m; i++) cin>>c[i];

	for(int i = 1; i <= n; i++)
	{
		cin>>t[i];

		pos[t[i]].push_back(i);
	}

	for(int i = 1; i <= m; i++)
	{
		for(int j = 0; j < (int)pos[i].size(); j++)
		{
			if(j + k - 1 >= pos[i].size()) break;

			int p1 = pos[i][j], p2 = pos[i][j + k - 1];

			ini[p2] = p1;

			sweep.push_back({p2, i, 0});
		}
	}

	for(int i = 0; i < 4*N; i++) tree[i] = inf;

	cin>>q;

	for(int i = 1; i <= q; i++)
	{
		cin>>x[i]>>y[i];

		sweep.push_back({y[i], i, 1});
	}

	sort(sweep.begin(), sweep.end(), cmp);

	for(auto T: sweep)
	{
		if(T.tip == 0) upd(1, 1, n, ini[T.x], c[T.id]);

		else ans[T.id] = query(1, 1, n, x[T.id], y[T.id]);
	}

	for(int i = 1; i <= q; i++) cout<<(ans[i] < inf ? ans[i]*k : -1)<<"\n";
}