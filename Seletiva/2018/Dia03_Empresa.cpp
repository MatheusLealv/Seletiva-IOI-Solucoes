#include <bits/stdc++.h>
#define N 100050
#define l (2*nod)
#define r ((2*nod) + 1)
#define mid ((a + b)/2)
using namespace std;
typedef long long ll;

struct ss
{
	int f, s, t;
};

bool cmp(ss A, ss B)
{
	if(A.f != B.f) return A.f > B.f;

	if(A.s != B.s) return A.s < B.s;

	return A.t < B.t;
}

vector<ss> val;

int n, pai[N], nivel[N], T[N], opt[N], tree[4*N], cnt, ini[N], fim[N];

ll tot;

void upd(int nod, int a, int b, int i, int x)
{
	if(a == b)
	{
		if(tree[nod]) tree[nod] = min(tree[nod], x);

		else tree[nod] = x;

		return;
	}

	if(i <= mid) upd(l, a, mid, i, x);

	else upd(r, mid + 1, b, i, x);

	tree[nod] = max(tree[l], tree[r]);
}

int query(int nod, int a, int b, int i, int j)
{
	if(j < a or i > b) return 0;

	if(i <= a and j >= b) return tree[nod];

	return max(query(l, a, mid, i, j), query(r, mid + 1, b, i, j));
}

vector<int> grafo[N];

void dfs(int x, int p)
{
	ini[x] = ++cnt;

	nivel[x] = nivel[p] + 1;

	val.push_back({nivel[x], T[x], x});

	for(auto v: grafo[x])
	{
		if(v == p) continue;

		dfs(v, x);
	}

	fim[x] = cnt;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(int i = 2; i <= n; i++)
	{
		cin>>pai[i];

		grafo[i].push_back(pai[i]);

		grafo[pai[i]].push_back(i);
	}

	for(int i = 1; i <= n; i++) cin>>T[i];

	dfs(1, 1);

	sort(val.begin(), val.end(), cmp);

	for(int i = 0; i < val.size(); i++)
	{
		int x = val[i].t;

		ll ans = max(query(1, 1, n, ini[x], fim[x]), opt[nivel[x]]) + 1LL;

		upd(1, 1, n, ini[x], ans);

		opt[nivel[x]] = max((ll)opt[nivel[x]], ans);

		tot += ans;
	}

	cout<<tot<<"\n";
}