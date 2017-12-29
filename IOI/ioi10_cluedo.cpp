#include <bits/stdc++.h>

using namespace std;

#include "cluedo.h"


void Solve()
{
	int a = 1, b = 1, c = 1;

	int p = Theory(a, b, c);

	while(p > 0)
	{
		if(p == 1) a++;

		if(p == 2) b++;

		if(p == 3) c++;

		p = Theory(a, b, c);	
	}
}