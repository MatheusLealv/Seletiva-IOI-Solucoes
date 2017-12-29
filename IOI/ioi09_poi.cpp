#include <bits/stdc++.h>
#define N 2100
using namespace std;

int n, t, p, v[N];

struct al
{
	vector<int> solved;
	int id, pont;
};

al A[N];

bool comp(al A, al B)
{
	if(A.pont != B.pont) return A.pont > B.pont;

	if(A.solved.size() != B.solved.size()) return A.solved.size() > B.solved.size();

	return A.id < B.id;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>t>>p;

	for(int i = 1; i <= t; i++) v[i] = n;

	for(int i = 1; i <= n; i++)
	{
		A[i].id = i, A[i].pont = 0;

		for(int k = 1; k <= t; k++)
		{
			int x;

			cin>>x;

			if(x)
			{
				A[i].solved.push_back(k);

				v[k]--;
			}
		}
	}

	for(int i = 1; i <= n; i++)
	{
		for(int k = 0; k < (int) A[i].solved.size(); k++)
		{
			A[i].pont += v[A[i].solved[k]];
		}
	}

	sort(A + 1, A + n + 1, comp);

	for(int i = 1; i <= n; i++)
	{
		if(A[i].id == p)
		{
			cout<<A[i].pont<<" "<<i<<"\n";
			break;
		}
	}

}