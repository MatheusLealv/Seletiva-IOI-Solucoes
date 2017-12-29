#include <bits/stdc++.h>
#define N 1040
using namespace std;
int bit[N][N], n, q;

void upd(int x, int y, int v)
{
	for(int i = x; i < N; i += (i&-i))
		for(int j = y; j< N; j += (j&-j))
			bit[i][j] += v;
}

int query(int x, int y)
{
	int sum = 0;
	for(int i = x; i > 0; i -= (i&-i))
		for(int j = y; j > 0; j -= (j&-j))
			sum += bit[i][j];

	return sum;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	while(1)
	{
		cin>>q;
		if(q == 0) cin>>n;
		if(q == 1)
		{
			int x, y, v;
			cin>>x>>y>>v;
			x++, y++;
			upd(x, y, v);
		}
		if(q == 2)
		{
			int xi, yi, xii, yii, resp;
			cin>>xi>>yi>>xii>>yii;
			xi ++, yi++, xii++, yii++;
			resp = query(xii, yii) - query(xii, yi - 1) - query(xi - 1, yii) + query(xi - 1, yi - 1);
			cout<<resp<<"\n";
		}
		if(q == 3) break;
	}

}