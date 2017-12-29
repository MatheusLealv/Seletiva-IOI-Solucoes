#include <bits/stdc++.h>
#define N 100050
using namespace std;
typedef long long ll;

int n, D[N], P[N], B[N];

struct node
{
	int sz, w, qtd2;

	ll sum, qtd, val;

	node *l, *r;

	node(int x = 0, int q = 0)
	{
		w = rand(), val = (ll)x, sz = 1, qtd = qtd2 = (ll)q, sum = (ll)(x*q);

		l = r = NULL;
	}
};

ll s(node *root)
{
	return root ? root->sum : 0;
}

ll qtdi(node *root)
{
	return root ? root->qtd : 0;
}

int sz(node *root)
{
	return root ? root->sz : 0;
}

void upd(node *&root)
{
	if(!root) return;

	root->sz = sz(root->l) + sz(root->r) + 1;

	root->qtd = qtdi(root->l) + qtdi(root->r) + root->qtd2;

	root->sum = s(root->l) + s(root->r) + (ll)((ll)(root->qtd2)*(ll)(root->val));
}

void Merge(node *&root, node *l, node *r)
{
	if(!l || !r) root = l ? l : r;

	else
	{
		if(l->w > r->w) Merge(l->r, l->r, r), root = l;

		else Merge(r->l, l, r->l), root = r;
	}

	upd(root);
}

void Split(node *root, node *&l, node *&r, ll val)
{
	if(!root) l = r = NULL;
	else
	{
		if(root->val < val) Split(root->r, root->r, r, val), l = root;

		else Split(root->l, l, root->l, val), r = root;
	}

	upd(root);
}

node *root = NULL;

void insert(int x, int qtd)
{
	node *l = NULL, *r = NULL, *novo = new node(x, qtd);

	Split(root, l, r, x);

	Merge(l, l, novo);

	Merge(root, l, r);
}

void Split_2(node *root, node *&l, node *&r, ll k)
{
	if(!root) l = r = NULL;
	else
	{
		ll QTD_ESQ = qtdi(root->l);

		if(QTD_ESQ >= k)
		{
			Split_2(root->l, l, root->l, k);

			r = root;
		}
		else
		{
			if(QTD_ESQ + root->qtd2 >= k )
			{
				k -= QTD_ESQ;

				if(k != root->qtd2)
				{
					node *novo = new node(root->val, root->qtd2 - k);

					root->qtd2 = k;

					novo->r = root->r;

					upd(novo);

					r = novo;
				}
				else  r = root->r;

				l = root;

				root->r = NULL;
			}

			else Split_2(root->r, root->r, r,  k - root->qtd2 - QTD_ESQ), l = root;
		}
	}

	upd(root);
}

ll ans = 0;

bool check = true;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(int i = 1; i <= n; i++) cin>>D[i]>>B[i]>>P[i];

	for(int i = 1; i <= n; i++)
	{
		node *l = NULL, *r = NULL;

		Split_2(root, l, r, D[i]);

		root = l;

		insert(P[i], B[i]);

		if(root && root->qtd < D[i])
		{
			ans = -1;

			break;
		}

		if(check)
		{
			node *l = NULL, *r = NULL;

			Split_2(root, l, r, D[i]);

			ll pp = s(l);

			root = r;

			ans += pp;
		}
	}

	cout<<ans<<"\n";
}