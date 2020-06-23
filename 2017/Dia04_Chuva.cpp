#include <bits/stdc++.h>
#define N 1002
#define K 250
#define f first
#define s second
#define gc getchar_unlocked
#define mid ((a + b)/2)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

inline int scan()
{
	int n = 0, x = gc(), s = 1;

	for (;x<'0'||x>'9';x=gc()) if(x=='-') s=-1;
	for (;x>='0'&&x<='9';x=gc()) n = (n<<3) + (n<<1) + x-'0';
	return n;
}

int n, m, k, mat[N][N], x[K], y[K], dp[N][N];

int q, dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

bitset<K> tree[3*N][3*N], nulo, val[N][N];

bitset<K> sum1d(int bloco, int i, int j, int nod = 1, int a = 0, int b = n - 1)
{
	if(i > b || j < a) return nulo;

	if(i <= a && b <= j) return tree[bloco][nod];

	return (sum1d(bloco, i, j, 2*nod, a, mid) | sum1d(bloco, i, j, 2*nod + 1, mid + 1, b));
}

bitset<K> sum2d(int xi, int xii, int yi, int yii, int nod = 1, int a = 0, int b = m - 1)
{
	if(yi > b || yii < a) return nulo;

	if(yi <= a && yii >= b) return sum1d(nod, xi, xii);

	return (sum2d( xi, xii, yi, yii, 2*nod, a, mid) | sum2d(xi, xii, yi, yii, 2*nod + 1, mid + 1, b));
}

void atualiza(int bloco, int nod = 1, int a = 0, int b = n - 1)
{
	tree[bloco][nod] = (tree[2*bloco][nod] | tree[2*bloco + 1][nod]);

	if(a == b) return;

	atualiza(bloco, 2*nod, a, mid), atualiza(bloco, 2*nod + 1, mid + 1, b);
}

void buildX(int nod, int bloco, int a, int b, int y)
{
	if(a == b)
	{
		tree[bloco][nod] = val[a][y];

		return;
	}

	buildX(2*nod, bloco, a, mid, y), buildX(2*nod + 1, bloco, mid + 1, b, y);

	tree[bloco][nod] = (tree[bloco][2*nod] | tree[bloco][2*nod + 1]);
}

void build2d(int bloco, int a, int b)
{
	if(a == b)
	{
		buildX(1, bloco, 0, n - 1, a);

		return;
	}

	build2d(2*bloco, a, mid), build2d(2*bloco + 1, mid + 1, b);

	atualiza(bloco);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	n = scan(); m = scan(); k = scan();

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			mat[i][j] = scan();

	for(int i = 0; i < k; i++)
	{		
		x[i] = scan(); y[i] = scan();

		val[x[i]-1][y[i]-1][i] = 1;

		dp[x[i]][y[i]] = i+1;

		queue<pii> fila;

		fila.push({x[i], y[i]});

		while(!fila.empty())
		{
			int x = fila.front().f, y = fila.front().s;

			fila.pop();

			for(int p = 0; p < 4; p++)
			{
				int a = x + dx[p], b = y + dy[p];

				if(dp[a][b] == i +1 or (mat[x][y] > mat[a][b])) continue;

				dp[a][b] = i + 1;

				val[a-1][b-1][i] = 1;

				fila.push({a, b});
			}
		}
	}

	build2d(1, 0, m - 1);

	q = scan();

	for(int i = 1, xi, yi, xii, yii, tot; i <= q; i++)
	{
		tot = k;

		xi = scan(); yi = scan(); xii = scan(); yii = scan();

		cout<<sum2d(xi-1, xii-1, yi-1, yii-1).count()<<"\n";
	}
}