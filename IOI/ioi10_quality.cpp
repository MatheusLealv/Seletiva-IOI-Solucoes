#include <bits/stdc++.h>
#define f first
#define s second
#define N 3005
#define gc getchar_unlocked
using namespace std;
typedef pair<int, int> pii;

int n, m, r, c, mat[N][N], bit[N][N];

int sum(int xi, int yi, int xii, int yii)
{
	return bit[xii][yii] - bit[xi - 1][yii] - bit[xii][yi - 1] + bit[xi - 1][yi - 1];
}

pii v[N*N];

pii verif(int x, int y)
{
	bool A = false, B = false;

	for(int i = 1; i <= r; i++)
	{
		for(int j = 1; j <= c; j++)
		{
			int xf = i + n - 1, yf = j + m - 1;

			if(xf <= 0 || yf <= 0 || xf > r || yf > c ) continue;

			int S = sum(i, j, xf, yf);
		
			if(S == (n*m - 1)/2 && (i <= x && x <= xf && j <= y && y <= yf)) A = true;

			if(S > (n*m - 1)/2) B = true;
		}
	}

	return pii(A, B);
}

inline int input()
{
	int a=0, x=gc(), sign=1;
	for(;x<'0'||x>'9';x=gc()) if(x == '-') sign=-1;
	for(;x>='0'&&x<='9';x=gc()) a = (a<<3) + (a<<1) + x-'0';
	return a*sign;
}

int main()
{
	r = input(), c = input(), n = input(), m = input();

	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++)
			mat[i][j] = input(), v[mat[i][j] - 1] = pii(i, j);

	int ini = 0, fim = r*c - 1, mid, best = 2000000000;

	while(fim >= ini)
	{
		mid = (ini + fim)/2;

		memset(bit, 0, sizeof bit);

		for(int i = 0; i < mid; i++)
		{
			pii val = v[i];

			bit[val.f][val.s] = 1;
		}

		for(int i = 1; i <= r; i++)
			for(int j = 1; j <=c ; j++)
				bit[i][j] += bit[i - 1][j] + bit[i][j - 1] - bit[i - 1][j - 1];

		pii V = verif(v[mid].f, v[mid].s);

		if(V.f && V.s)
		{
			best = min(best, mid);

			fim = mid - 1;
		}

		else if(V.f && !V.s)
		{
			best = min(best, mid);

			ini = mid + 1;
		}

		else if(!V.f && V.s) fim = mid - 1;

		else ini = mid + 1;
	}

	cout<<best + 1<<"\n";
}