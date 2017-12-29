#include <bits/stdc++.h>
#define N 1000050
using namespace std;

int n, ini[N], fim[N];

vector<int> pos[N], k, resp;

int A[N], B[N];

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin>>n;

    for(int i = 1; i<=n; i++)  cin>>ini[i];

    for(int i =1; i<n; i++) cin>>fim[i];

    for(int i = 1; i<n; i++)
    {
        if(fim[i] == ini[i] || fim[i] == ini[i] - 1)
        pos[ini[i]].push_back(fim[i]);

        if(fim[i] == ini[i + 1] || fim[i] == ini[i + 1] - 1)
            pos[ini[i + 1]].push_back(fim[i]);
    }

    bool zero = false;

    for(int i = 1; i<=n; i++)
    {
        if(pos[i].size() == 0)
        {
            zero = true;
            k.push_back(i);
        }

        if(zero) continue;

        for(int j = 0; j<pos[i].size(); j++)
        {
            if(pos[i][j] == i) A[i] ++;
            if(pos[i][j] == i - 1) B[i]++;
        }
    }

    for(int i = 1; i <= n; i++) A[i] += A[i - 1], B[i] += B[i - 1];

    for(int i = 1; i<=n; i++) if(B[n] - B[i] == n - i && A[i - 1] == i - 1) resp.push_back(i);

    if(!zero)

    for(int i = 0; i<resp.size(); i++) cout<<resp[i]<<" ";

    else for(int i = 0; i<k.size(); i++) cout<<k[i]<<" ";

    cout<<"\n";
}