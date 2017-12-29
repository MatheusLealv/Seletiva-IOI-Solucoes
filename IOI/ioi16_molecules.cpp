#include <bits/stdc++.h>
#define N 1000050
#define f first
#define s second

using namespace std;
typedef pair<int, int> pii;

int n, l, r;

void find_subset (int l, int r, vector<int> w)
{
	vector<int> ans;

	vector<pii> v;

	int a = -1, b = -1;

	long long sum[N];

	for(int i = 0; i < w.size(); i++)
	{
		v.push_back(pii(w[i], i));
	}

	sort(v.begin(), v.end());

	for(int i = 0; i < v.size(); i++)
	{
		sum[i] =  (i > 0 ? v[i].f + sum[i - 1]: v[i].f);
	}

	for(int i = 0; i < v.size(); i++)
	{
		int ini = i, fim = v.size() - 1, mid;

		while(fim >= ini)
		{
			mid = (ini + fim)/2;

			long long ds = i > 0 ? sum[i - 1]: 0LL;

			if(sum[mid] - ds > r)
			{
				fim = mid - 1;
			}
			else if(sum[mid] - ds < l)
			{
				ini = mid + 1;
			}
			else 
			{
				a = i, b = mid;
				break;
			}
		}
	}

	if(a != -1) for(int i = a; i <= b; i++) ans.push_back(v[i].s);

	cout<<ans.size()<<"\n";

	for(int i = 0; i < ans.size(); i++) cout<<ans[i]<<" \n"[i == ans.size() - 1];
}

vector<int> w;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	
	cin>>n>>l>>r;

	for(int i = 1, x; i <= n; i++) cin>>x, w.push_back(x);

	find_subset(l, r, w);
}