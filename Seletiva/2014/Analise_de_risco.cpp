#include <bits/stdc++.h>
#define N 100050
#define mid ((a + b)/2)
using namespace std;
typedef long long ll;
int A, B, n, v[N], tree[4*N];

int mdc(int a, int b)
{
	if(!a) return b;

	return b == 0 ? a : mdc(b, a%b);
}

int dp[N*10][30];

inline void build()
{
  for(int i = 0; i < n; i++) dp[i][0] = v[i];

  for(int j = 1; j <= 19; j++)
      for(int i = 0; i < n; i++)
           dp[i][j] = mdc(dp[i][j - 1], dp[ i + (1<<(j - 1)) ][j - 1]);
}

inline int query(int l, int r)
{
	if(l == r) return v[l];

	int exp = 31-__builtin_clz(r-l);

	return mdc(dp[l][exp], dp[r - (1<<exp) + 1][exp]);
}

inline ll solve(int x = B)
{
	ll ans = 0;

	for(int i = 0; i < n; i++)
	{
		x = B;

		while(x >= 1)
		{
			int ini = i, fim = n - 1, meio, best = -1;

			while(fim >= ini)
			{
				meio = (ini + fim)/2;

				if(query(i, meio) <= x)
				{
					best = meio;

					fim = meio - 1;
				}
				else ini = meio + 1;
			}

			if(best == -1) break;

			ini = max(best, i), fim = n - 1;

			int best2 = -1, sla = 0;

			if(best != -1) sla = query(i, best);

			while(fim >= ini && sla)
			{
				meio = (ini + fim)/2;

				int c = query(i, meio);

				if(c == sla)
				{
					best2 = meio;

					ini = meio + 1;
				}
				else fim = meio - 1;
			}

			if(best != -1)
			{
				if(A <= sla && sla <= B) ans += ((ll)(best2 - best + 1))*((ll)(B - sla + 1));

				else ans += ((ll)(best2 - best + 1))*((ll)(B - A + 1));
			}

			else break;

			x = sla - 1;
		}
	}

	return ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>A>>B;

	for(int i = 0; i < n; i++) cin>>v[i];

	build();

	cout<<solve()<<"\n";
}