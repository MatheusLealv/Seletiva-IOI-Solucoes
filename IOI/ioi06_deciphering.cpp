#include <bits/stdc++.h>
#define N 3000050
#define prime 1000000007
#define pl 1299827
using namespace std;
typedef long long ll;

int n, m;

ll pref_hash[N], save_hash = 0;

string a, b;

map<ll, ll> dp;

int Pow(ll x, ll p = pl)
{
	if(dp[x] != 0) return dp[x];

	if(p == 0) return 1;

	ll ans = Pow(x, p/2)%prime;

	ans = (ans*ans)%prime;

	if(p %2 == 0) return dp[x] = (ans)%prime;

	return dp[x] = (x*ans)%prime;
}

int getHash()
{
	int resp = 0;

	for(int i = 0; i < n; i++) save_hash = (save_hash + Pow(a[i]))%prime;

	for(int i = 0; i < m; i++) pref_hash[i] = (( i >= 0 ? pref_hash[i - 1]:0) + Pow(b[i]))%prime;

	for(int i = n - 1; i < m; i++)
	{
		int ini = i - n;

		bool add = 1;

		int dq = 0;

		if(ini >= 0) dq = pref_hash[ini];

		if((prime + pref_hash[i] - dq)%prime == save_hash) resp ++;
	}

	return resp;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>m;

	cin>>a>>b;

	cout<<getHash()<<"\n";
}