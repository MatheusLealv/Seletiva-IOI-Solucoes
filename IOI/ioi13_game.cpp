#include <bits/stdc++.h>
#define mid ((a+b)/2)
#define llg long long int
using namespace std;

struct node1d
{
	llg val;
	node1d *l, *r;
	node1d()
	{
		val = 0;
		l = r = NULL;
	}
};

struct node2d
{
	node1d *tree;
	node2d *l, *r;
	node2d()
	{
		tree = new node1d;
		l = r = NULL;
	}
};

llg n, m, q;

llg mdc(llg a, llg b)
{
	if(b == 0) return a;
	if(a == 0) return b;
	return mdc(b, a%b);
}

llg query1d(node1d *nod, llg i, llg j, llg a = 0, llg b = n - 1)
{
	if(i > b || j < a) return 0;
	if(i <= a && j >= b) return nod->val;
	return mdc(((nod->l != NULL)?query1d(nod->l, i, j, a, mid):0), ((nod->r != NULL)?query1d(nod->r, i, j, mid + 1, b):0));
}
llg query2d(node2d *nod, llg xi, llg yi, llg xii, llg yii, llg a = 0, llg b = m - 1)
{
	if(yi > b || yii < a) return 0;
	if(yi <= a && yii >= b) return query1d(nod->tree, xi, xii);

	llg F1 = (nod->l != NULL)? query2d(nod->l, xi, yi, xii, yii, a, mid):0;

	llg F2 = (nod->r != NULL)? query2d(nod->r, xi, yi, xii, yii, mid + 1, b):0;

	return mdc(F1, F2);
}

void atualiza(node1d *nod, node1d *lseg, node1d *rseg, llg x, llg a = 0, llg b = n- 1)
{
	if(lseg == NULL && rseg == NULL) return;

	nod->val = mdc(((lseg != NULL)?lseg->val:0), ((rseg != NULL)?rseg->val:0));

	if(a == b) return;

	if(x <= mid)
	{
		if(nod->l == NULL) nod->l = new node1d;
		atualiza(nod->l, (lseg!= NULL)?lseg->l:NULL, (rseg!= NULL)?rseg->l:NULL, x, a, mid);
		       // atualiza(nod->l,lseg!=NULL?lseg->l:NULL,rseg!=NULL?rseg->l:NULL,x,a, mid);
	}
	else
	{
		if(nod->r == NULL) nod->r = new node1d;
		atualiza(nod->r, (lseg!= NULL)?lseg->r:NULL, (rseg!= NULL)?rseg->r:NULL,x,  mid + 1, b);
	}
}

void upd1d(node1d *nod, llg x, llg v, llg a = 0, llg b = n - 1)
{
	if(x > b || x < a) return;

	if(a == b)
	{
		nod->val = v;
		return;
	}

	if(x <= mid)
	{	
		if(nod->l == NULL) nod->l = new node1d;
		upd1d(nod->l, x, v, a, mid);
	}
	else
	{
		if(nod->r == NULL) nod->r = new node1d;
		upd1d(nod->r, x, v, mid + 1, b);
	}

	nod->val = mdc(((nod->l != NULL)?((nod->l)->val):0), ((nod->r != NULL)?((nod->r)->val):0));
}

void upd2d(node2d *nod, llg x, llg y, llg v, llg a = 0, llg b = m - 1)
{
	if(y > b || y < a) return;

	if(a == b)
	{
		upd1d(nod->tree, x, v);
		return;
	}
	if(y <= mid)
	{
		if(nod->l == NULL) nod->l = new node2d;
		upd2d(nod->l, x, y, v, a, mid);
	}
	else
	{
		if(nod->r == NULL) nod->r = new node2d;
		upd2d(nod->r, x, y, v, mid + 1, b);
	}

    atualiza(nod->tree,nod->l!=NULL?(nod->l)->tree:0,nod->r!=NULL?(nod->r)->tree:0,x);
}

node2d *root = new node2d(); 

void update(llg x, llg y, llg val)
{
	upd2d(root, x, y, val);
}

llg calculate(llg xi, llg yi, llg xii, llg yii)
{
	return query2d(root, xi, yi, xii, yii);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	scanf("%lld %lld %lld", &n, &m, &q);

	while(q--)
	{
		llg t;

		scanf("%lld", &t);

		if(t == 1)
		{
			llg x, y, v;
			
			scanf("%lld %lld %lld", &x, &y, &v);

			update(x, y, v);
		}
		else
		{
			llg xi, yi, xii, yii;

			scanf("%lld %lld %lld %lld", &xi, &yi, &xii, &yii);

			printf("%lld\n", calculate(xi, yi, xii, yii));
		}
	}
}