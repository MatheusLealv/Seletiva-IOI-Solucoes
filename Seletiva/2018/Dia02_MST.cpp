#include <bits/stdc++.h>
#define N 100050
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

int n, m, k, q, pai[N], peso[N];

ll ans;

vector<pair<int, pii> > A;

struct node
{
	ll val;

	int w, sz;

	ll sum;

	node *l, *r;

	node(int x)
	{
		val = sum = x, w = rand(), sz = 1;

		l = r = NULL;
	}
};

node *root = NULL;

inline int Sz(node *root){
	return (root ? root->sz : 0);
}

inline ll Sum(node *root){
	return (root ? root->sum : 0);
}

inline void upd(node *root)
{
	if(!root) return;

	root->sz = Sz(root->l) + Sz(root->r) + 1;

	root->sum = Sum(root->l) + Sum(root->r) + root->val;
}

void Merge(node *&root, node *l, node *r)
{
	if(!l or !r) root = (l ? l: r);

	else
	{
		if(l->w > r->w) Merge(l->r, l->r, r), root = l;

		else Merge(r->l, l, r->l), root = r;

		upd(root);
	}
}

void Split(node *root, node *&l, node *&r, int x)
{
	if(!root) l = r = NULL;

	else
	{
		if(root->val < x) Split(root->r, root->r, r, x), l = root;

		else Split(root->l, l, root->l, x), r = root;

		upd(root);
	}
}

inline void insert(int x)
{
	node *l = NULL, *r = NULL, *novo = new node(x);

	Split(root, l, r, x);

	Merge(l, l, novo);

	Merge(root, l, r);
}

void Remove(node *&root, ll x)
{
	if(root->val == x) Merge(root, root->l, root->r);

	else if(root->val < x) Remove(root->r, x);

	else Remove(root->l, x);

	upd(root);
}

int Find(int x)
{
	if(x == pai[x]) return x;

	return pai[x] = Find(pai[x]);
}

ll kth(node *root, int k)
{
	int p = Sz(root->l) + 1;

	if(p == k) return (Sum(root->l) + root->val);

	if(p > k) return kth(root->l, k);

	return kth(root->r, k - p) + Sum(root->l) + root->val;
}

void join(int a, int b, ll d)
{
	a = Find(a), b = Find(b);

	if(a == b) return;

	ans += d;

	insert(d);

	if(peso[a] < peso[b]) pai[a] = b;

	else if(peso[a] > peso[b]) pai[b] = a;

	else pai[b] = a, peso[a] ++;
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>m>>k>>q;

	for(int i = 1; i <= n; i++) pai[i] = i;

	for(int i = 1, a, b, c; i <= m; i++)
	{
		cin>>a>>b>>c;

		A.push_back({c, {a, b}});
	}

	sort(A.begin(), A.end());

	for(auto x: A)
	{
		int u = x.s.f, v = x.s.s;

		ll d = x.f;

		join(u, v, d);
	}

	for(int i = 1; i <= k; i++)
	{
		ll x;

		cin>>x;

		insert(x);
	}

	cout<<kth(root, n - 1)<<"\n";

	for(int i = 1; i <= q; i++)
	{
		int t;

		ll x;

		cin>>t>>x;

		if(t > 0) insert(x);

		else Remove(root, x);

		cout<<kth(root, n - 1)<<"\n";
	}
}