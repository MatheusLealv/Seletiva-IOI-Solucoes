#include "cave.h"
#include <bits/stdc++.h>
using namespace std;

int N, idx[5050], tip[5050];

int ans[5050], cnt = 0, state[5050], save[5050], id[5050], block[5050];

void inverte(int a, int b)
{
	for(int i = a; i <= b; i++)
	{
		if(!block[i]) ans[i] = !ans[i];
	}
}

void exploreCave(int n)
{
	N = n;

	for(int i = 0; i < n; i++) ans[i] = save[i] = 1;

	for(int porta = 0; porta < n; porta ++)
	{
		int ste = tryCombination(ans);

		int ini = 0, fim = n - 1, mid, best;

		bool A = false;

		while(fim >= ini)
		{
			mid = (ini + fim)/2;

			inverte(ini, mid);

			int p = tryCombination(ans);

			inverte(ini, mid);

			if( (ste != porta && p == porta) || (ste == porta && p != porta) )
			{
				fim = mid - 1;

				if(ste != porta && p == porta) A = true;

				best = mid;
			}
			else ini = mid + 1;
		}

		if(A == true)
		{
			block[best] = 1;

			id[best] = porta;
		}
		else
		{
			block[best] = 1;

			id[best] = porta;

			ans[best] = !ans[best];
		}
	}

	answer(ans, id);
}