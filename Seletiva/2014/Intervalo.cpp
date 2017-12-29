#include <bits/stdc++.h>
#define int long long
#define N 100050
using namespace std;

struct node
{
	int val, sum, w, sz;
	node *l, *r;
	node(int x){val = sum = x, w = rand(), l = r = NULL, sz = 1;}
};

int n, q;

node *root = NULL;

int Sum(node *root)
{
	return root ? root->sum : 0;
}
int Sz(node *root)
{
	return root ? root->sz : 0;
}

void upd(node *&root)
{
	if(!root) return;

	root->sz = 1 + Sz(root->l) + Sz(root->r);

	root->sum = root->val + Sum(root->l) + Sum(root->r);
}

void Merge(node *&root, node *l, node *r)
{
	if(!l || !r) root = l ? l : r;
	else
	{
		if(l->w > r->w)
		{
			Merge(l->r, l->r, r);
			root = l;
		}
		else
		{
			Merge(r->l, l, r->l);
			root = r;
		}
	}

	upd(root);
}

void Split(node *root, node *&l, node *&r, int idx)
{
	if(!root)
	{
		l = r = NULL;

		return;
	}

	int p = Sz(root->l) + 1;

	if(p < idx)
	{
		Split(root->r, root->r, r, idx - p);
		l = root;
	}
	else
	{
		Split(root->l, l, root->l, idx);
		r = root;
	}

	upd(root);
}

void Insert(int idx, int val)
{
	node *l = NULL, *r = NULL, *novo = new node(val);

	Split(root, l, r, idx + 1);

	Merge(root, novo, r);

	Merge(root, l, root);
}

int query(int a, int b)
{
	node *l = NULL, *r = NULL, *l1 = NULL, *r1 = NULL;

	Split(root, l, r, b + 1);

	Split(l, l1, r1, a);

	int ans = Sum(r1);

	Merge(l, l1, r1);

	Merge(root, l, r);

	return ans;
}

 main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(int i = 1, x; i <= n; i++) cin>>x, Insert(i, x);

	cin>>q;

	for(int i = 1; i <= q; i++)
	{
		char op; int a, b;

		cin>>op>>a>>b;

		if(op == 'I') Insert(a, b);

		else cout<<query(a, b)<<"\n";
	}
}