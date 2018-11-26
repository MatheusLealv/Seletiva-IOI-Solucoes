#include <bits/stdc++.h>
#define N 3030
#define f first
#define s second
using namespace std;
typedef long long ll;

int n;

ll inf = 20000000000000000LL;

ll ans = -inf;

struct ss
{
	ll x, y;

	ll v;

} p[N];

bool cmp(ss a, ss b)
{
	if(a.x != b.x) return a.x < b.x;

	return a.y < b.y;
}

int id;

bool cmp2(ss a, ss b)
{
	ll L = a.y * b.x, R = b.y * a.x;

	if(L != R) return L < R;

	return a.y < b.y;
}

ll opt(int id, vector<ss> &val)
{
	if(val.empty()) return -inf;

	ll pref = p[id].v, opt = -inf;

	for(int i = 0; i < val.size(); i++)
	{
		pref += val[i].v;

		opt = max(opt, pref);
	}

	return opt;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(int i = 1; i <= n; i++) cin>>p[i].x>>p[i].y>>p[i].v;

	sort(p + 1, p + n + 1, cmp);

	for(int i = 1; i <= n; i++)
	{
		vector<ss> val;

		vector<ss> vert;

		for(int j = i + 1; j <= n; j++)
		{
			if(p[j].x == p[i].x) vert.push_back({0, 0, p[j].v});

			else val.push_back({p[j].y - p[i].y, p[j].x - p[i].x, p[j].v});
		}

		sort(val.begin(), val.end(), cmp2);

		ans = max(ans, opt(i, vert));

		vector<ss> save;

		for(int j = 0; j < val.size(); j++)
		{
			if(!j)
			{
				save.push_back(val[j]);

				continue;
			}

			ll L = val[j - 1].y*val[j].x, R = val[j].y*val[j - 1].x;

			if(L == R)
			{
				save.push_back(val[j]);

				continue;
			}

			ans = max(ans, opt(i, save));

			save.clear();

			save.push_back(val[j]);
		}

		ans = max(ans, opt(i, save));
	}

	cout<<ans<<"\n";
}