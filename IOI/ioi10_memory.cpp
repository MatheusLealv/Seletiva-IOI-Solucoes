#include <bits/stdc++.h>
using namespace std;

#include "memory.h"

int n, save[100][2];

void play()
{
	memset(save, -1, sizeof save);

	for(int i = 1; i <= 50; i++)
	{
		char c = faceup(i);

		if(save[c][0] == -1) save[c][0] = i;

		else save[c][1] = i;
	}

	for(int i = 65; i <= 89; i++)
	{
		faceup(save[i][0]);

		faceup(save[i][1]);
	}
}