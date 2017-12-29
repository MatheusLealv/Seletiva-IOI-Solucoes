#include <bits/stdc++.h>
#define N 5000050
using namespace std;

int save = 0, menorque = (1e9) + 10, maiorque = -(1e9) - 10, n, A;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	int ant = 0;

	for(int i = 1; i <= n; i++)
	{
		cin>>A;

		A *= 2;

		save = A - save;

		if(i %2 == 0) menorque = min(menorque, (save - ant)/2);

		else maiorque = max(maiorque, (ant - save)/2);

		ant = save;
	}

	cout<<max(0, menorque - maiorque + 1)<<"\n";
}