#include <bits/stdc++.h>
#define int long long
#define mp make_pair
#define N 100010
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

int n, d, ans, T, limite, b;

int bit[250][250][250];

inline int get_hash(int x, int y, int z)
{
	return (x - 1)*y + (y - 1)*z + z - 1;
}

inline void upd3d(int x, int y, int z, int val)
{
	for(int i = x; i < 250; i += (i&-i))
	{
		for(int j = y; j < 250; j += (j&-j))
		{
			for(int k = z; k < 250; k += (k&-k))
			{
				bit[i][j][k] += val;
			}
		}
	}
}

inline int query(int x, int y, int z)
{
	int sum = 0;

	x = min(x, 249LL);

	y = min(y, 249LL);

	z = min(z, 249LL);

	for(int i = x; i > 0; i -= (i&-i))
	{
		for(int j = y; j > 0; j -= (j&-j))
		{
			for(int k = z; k > 0; k -= (k&-k))
			{
				sum += bit[i][j][k];
			}
		}
	}

	return sum;
}

inline int query3d(int xi, int yi, int zi, int xii, int yii, int zii)
{
	if(xii < xi) swap(xi, xii);

	if(yii < yi) swap(yi, yii);

	if(zii < zi) swap(zi, zii);

	int esq = query(xii, yii, zii) - query(xi - 1, yii, zii) - query(xii, yi - 1, zii) + query(xi - 1, yi - 1, zii);

	int dir = query(xii, yii, zi - 1) - query(xi - 1, yii, zi - 1) - query(xii, yi - 1, zi - 1) + query(xi - 1, yi - 1, zi - 1);

	return esq - dir;
 }

struct point
{
	int x, y, z;

	int A, B, C, D;

	point(int a = 0, int b = 0, int c = 0)
	{
		x = a, y = b, z = c;

		A = x + y + z;

		B = x + y - z;

		C = x - y + z;

		D = x - y - z;
	}

	bool operator <(const point &p) const
	{
		return A < p.A;
	}
};

point v[N];

inline int solve_3D()
{
	sort(v + 1, v + n + 1);

	int ini = 1, ans = 0;

	for(int i = 1; i <= n; i++)
	{
		while(ini < i && abs(v[i].A - v[ini].A) > d)
		{
			upd3d(v[ini].B, v[ini].C, v[ini].D, -1);

			ini ++;
		}

		ans += query3d(v[i].B - d, v[i].C - d, v[i].D - d, v[i].B + d, v[i].C + d, v[i].D + d);

		upd3d(v[i].B, v[i].C, v[i].D, 1);
	}

	return ans;
}

inline int solve_1D()
{
	sort(v + 1, v + n + 1);

	int ans = 0, ini = 1;

	deque<int> window;

	for(int i = 1; i <= n; i++)
	{
		while(ini < i && v[i].A - v[ini].A > d)
		{
			window.pop_front();

			ini ++;
		}

		ans += window.size();

		window.push_back(v[i].A);
	}

	return ans;
}

int bit1d[2*75006];

inline void upd2d(int x, int val)
{
	for(int i = x; i < 2*75006 ; i += (i&-i)) bit1d[i] += val;
}

inline int query2d(int a, int b)
{
	int sum = 0;

	a--;

	a = min(a, 2*75006 - 5LL), b = min(b, 2*75006 - 5LL);

	for(int i = b; i > 0; i -= (i&-i)) sum += bit1d[i];

	for(int i = a; i > 0; i -= (i&-i)) sum -= bit1d[i];

	return sum;
}

inline bool cmp(point a, point b)
{
	if(a.C != b.C) return a.C < b.C;

	return a.A < b.A;
}

inline int solve_2D()
{
	sort(v + 1, v + n + 1, cmp);

	int ini = 1, ans = 0;

	for(int i = 1; i <= n; i++)
	{
		while(ini < i && abs(v[i].C - v[ini].C) > d)
		{
			upd2d(v[ini].A, -1);

			ini ++;
		}

		ans += query2d(v[i].A - d, v[i].A + d);

		upd2d(v[i].A, 1);
	}

	return ans;
}

main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>b>>n>>d>>limite;

	for(int i = 1, x, y, z; i <= n; i++)
	{
		cin>>x;

		if(b >= 2) cin>>y;

		else y = 0;

		if(b >= 3) cin>>z;

		else z = 0;

		v[i] = point(x, y, z);	

		if(b == 3)
		{
			v[i].A -= 2;

			v[i].B += limite - 1;

			v[i].C += limite - 1;

			v[i].D += 2*limite;
		}
	}

	if(b == 3) cout<<solve_3D()<<"\n";

	else if(b == 2) cout<<solve_2D()<<"\n";

	else cout<<solve_1D()<<"\n";
}