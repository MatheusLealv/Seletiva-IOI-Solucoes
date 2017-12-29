#include <bits/stdc++.h>
#define int long long
#define N 110
#define mod 1000000007
using namespace std;

int n, k, h, ch[N][N], dp[N][N], fat[N];

int v[N], Alt[N];

struct node
{
	int val, qtd, H;

	node *l, *r;

	node(int x = 0, int hi = 0){val = x, H = hi, qtd = 0, l = r = NULL;}
};

node* root = NULL;

void Insert(node *&root, int x, int dist)
{
	if(!root) root = new node(x, dist);
	else
	{
		if(x > root->val) Insert(root->r, x, dist + 1);

		else Insert(root->l, x, dist + 1);
	} 
}

void dfs(node *root)
{
	if(!root) return;

	Alt[root->val] = root->H;

	dfs(root->l), dfs(root->r);
}

set<pair<node*, int> > folha;

int cont[N][5];

void add(node *&root, int x)
{
	if(!root) return;

	if(x < root->val)
	{
		if(root->l) add(root->l, x);

		else cont[root->val][0] ++;
	}

	else
	{
		if(root->r) add(root->r, x);

		else cont[root->val][1] ++;
	}
}

int choose(int a, int b)
{
	if(a == b || b == 0) return 1;

	if(b == 1) return a;

	if(b > a) return 0;

	if(ch[a][b] != -1) return ch[a][b];

	return ch[a][b] = (choose(a - 1, b - 1) + choose(a - 1, b))%mod;
}

int F(int n, int h)
{
	if(n < 0 || h < 0) return 0;

	if(n == 0) return 1;

	if(dp[n][h] != -1) return dp[n][h];

	int sum = 0;

	for(int i = 1; i <= n; i++)
	{
		int A = (F(i - 1, h - 1)*F(n - i, h - 1)) % mod;

		sum = (sum + (A*choose(n - 1, i - 1))%mod )%mod;
	}

	return dp[n][h] = sum%mod;
}

int g(int n, int h)
{
	return (mod + F(n, h) - F(n, h - 1))%mod;
}

vector< pair<node*, int> > lista;

bool used[N];

int Pow(int x, int p)
{
	if(p == 0) return 1;

	int ans = Pow(x, p/2);

	if(p%2 == 0) return (ans*ans)%mod;

	return (x*((ans*ans)%mod))%mod;
}

int quant = 0;

vector<int> tot;

int choose_Supremo()
{
	int num = fat[quant], den = 1;

	for(int i = 0; i < tot.size(); i++)
	{
		den = (den*fat[tot[i]])%mod;
	}

	return (num*Pow(den, mod - 2))%mod;
}

int ANIDO_LINDO(int h, int q, int i, int id)
{
	return ( (F(cont[v[i]][id], h - Alt[v[i]]) * choose (n - k - q, cont[v[i]][id]))%mod);
}

int solve(int n, int k, int hi)
{
	if(k == 0) return F(n, hi);

	int resp = 1, q = 0;

	for(int i = 1; i <= k ;i++)
	{
		resp = (resp * ANIDO_LINDO(hi, q, i, 0))%mod;

		q += cont[v[i]][0];

		resp = (resp * ANIDO_LINDO(hi, q, i, 1))%mod;

		q += cont[v[i]][1];
	}

	return resp;
}

 main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>n>>k>>h;

    for(int i = 1, x; i <= k; i++)
    {
        cin>>x;

        Insert(root, x, 1);

        used[x] = 1;

        v[i] = x;
    }

    fat[0] = 1;

    for(int i = 1; i < N; i++) fat[i] = (i*fat[i - 1])%mod;

    memset(ch, -1, sizeof ch);

    memset(dp, -1, sizeof dp);

	for(int i = 1; i <= n; i++)  if(!used[i]) add(root, i);

	dfs(root);

    cout<<(solve(n, k, h) - solve(n, k, h - 1) + mod)%mod<<"\n";
}