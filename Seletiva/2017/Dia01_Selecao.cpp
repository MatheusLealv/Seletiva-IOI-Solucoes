#include <bits/stdc++.h>
#define N 1000050
using namespace std;
typedef long long ll;

ll n, k, A[N], B[N], pref[N][2];

ll Ax, Bx, Cx, Mx, Ay, By, Cy, My;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>k;

	cin>>Ax>>Bx>>Cx>>Mx>>Ay>>By>>Cy>>My;

	A[1] = Ax;

	B[1] = Ay;

	for(int i = 2; i <= n; i++) A[i] = (Bx + Cx * A[i - 1]) % Mx;

	for(int i = 2; i <= n; i++) B[i] = (By + Cy * B[i - 1]) % My;

	sort(A + 1, A + n + 1);

	sort(B + 1, B + n + 1);

	ll ini = 0, fim = 100000000, mid, best;

	while(fim >= ini)
	{
		mid = (ini + fim)/2;

		ll ptr = n, ans = 0;

		for(int i = 1; i <= n; i++)
		{
			while(ptr >= 1 and B[ptr] + A[i] > mid) ptr --;

			ans += max(ptr, 0LL);
		}

		if(ans < k)  ini = mid + 1;

		else best = mid, fim = mid - 1;
	}

	cout<<best<<"\n";
}