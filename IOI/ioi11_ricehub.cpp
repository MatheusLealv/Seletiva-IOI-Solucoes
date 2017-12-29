#include <bits/stdc++.h>
#define N 1000060
using namespace std;
typedef long long ll;

ll n, L, x[N], r[N], l[N], k, resp = 1;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>L>>k;

	for(ll i = 1; i <= n; i++) cin>>x[i];

	sort(x + 1, x + n + 1);

	for(ll i = 1; i <= n; i++) r[i] = r[i - 1] + x[i];

	for(ll i = 1; i <= n; i++)
	{
		ll ini = i, fim = n, mid, ans = 1;

		while(fim >= ini)
		{
			mid = (ini + fim)/2;

			ll sumA = -(r[(i + mid)/2] - r[i - 1] - (((i + mid)/2) - i + 1)*x[(i + mid)/2]);

			ll sumB = r[mid] - r[(i + mid)/2] - (mid - ((i + mid)/2))*x[(i + mid)/2];

			ll dr = sumA + sumB;

			if(dr > k)
			{
				fim = mid - 1;
			}
			else
			{
				ans = max(ans, mid - i + 1);

				ini = mid + 1;
			}
		}

		resp = max(resp, ans);
	}

	cout<<resp<<"\n";
}