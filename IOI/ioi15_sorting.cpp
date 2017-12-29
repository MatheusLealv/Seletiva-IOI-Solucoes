#include <bits/stdc++.h>
#define N 1000050
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

int n, v[N], k, A[N], B[N], save[N], idx[N];

vector<pii> ans;

bool check(int m)
{	
	//cout<<"CHECK: ("<<m<<")\n";

	ans.clear();

	for(int i = 0; i <= n; i++) v[i] = save[i];

	vector<pii> greedy;

	for(int i = 0; i < m; i++) swap(v[A[i]], v[B[i]]);

	for(int i = 0; i < n; i++)
	{
		while(v[i] != i)
		{
			//swap(v[i], v[v[i]]);

			greedy.push_back(pii(v[i], v[v[i]]));

			swap(v[i], v[v[i]]);
		}
	}

	while(greedy.size() < m) greedy.push_back(pii(0, 0));

	if(greedy.size() > m) return false;

	for(int i = 0; i <= n; i++) v[i] = save[i];

	for(int i = 0; i < n; i++) idx[v[i]] = i;

	for(int i = 0; i < m; i++)
	{
		int x = A[i], y = B[i];

		swap(idx[v[x]], idx[v[y]]);

		swap(v[x], v[y]);

		int a = greedy[i].f, b = greedy[i].s;

		ans.push_back(pii(idx[a], idx[b]));

		swap(v[idx[a]], v[idx[b]]);

		swap(idx[a], idx[b]);
	}

	return true;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(int i = 0; i < n; i++) cin>>v[i], save[i] = v[i];

	cin>>k;

	for(int i = 0; i < k; i++) cin>>A[i]>>B[i];

	int ini = 0, fim = k - 1, mid, best;

	while(fim >= ini)
	{
		mid = (ini + fim)/2;

		if(check(mid))
		{
			best = mid;

			fim = mid - 1;
		}
		else ini = mid + 1;
	}

	check(best);

	cout<<ans.size()<<"\n";

	for(int i = 0; i < ans.size(); i++)
	{
		cout<<ans[i].f<<" "<<ans[i].s<<"\n";
	}
}