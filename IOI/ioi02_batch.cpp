#include <bits/stdc++.h>
#define int long long
#define N 10005
#define a first
#define b second
using namespace std;

typedef pair<int, int> pii;

int n, T[N], F[N], sumT[N], sumF[N], k, dp[N], r;

vector<int> f;

vector<pii> linha;

inline int Fi(int x, int id)
{
	return -linha[id].a*x + linha[id].b;
}

inline bool bad(pii C, pii B, pii A)
{
	return ( (B.b - A.b)*(A.a - C.a) < (C.b - A.b)*(A.a - B.a));
}

inline void addline(pii l)
{
	int p = linha.size();

	if(p < 2) linha.push_back(l);
	else
	{
		while(p >= 2 && bad(linha[p - 2], linha[p - 1], l))
		{
			p--;
			linha.pop_back();
		}
		linha.push_back(l);
	}
}

inline int query(int x)
{

	int p = linha.size();

	if(r >= p) r = p - 1;

	while(r < p - 1 && Fi(x, r) > Fi(x, r + 1)) r++;

	return Fi(x, r);
}

inline pii getline(int j)
{
	return pii(sumT[j], sumF[n]*sumT[j] + dp[j + 1]);
}

main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>k;

	for(int i = 1; i <= n; i++) cin>>T[i]>>F[i];

	for(int i = 1; i <= n; i++) sumT[i] = sumT[i - 1] + T[i], sumF[i] = sumF[i - 1] + F[i];

	dp[n + 1] = 0;

	for(int i = n; i >= 1; i--)
	{
		addline(getline(i));

		dp[i] = query(sumF[i - 1]) + (k - sumT[i - 1])*(sumF[n] - sumF[i - 1]);
	}

	cout<<dp[1]<<"\n";
}