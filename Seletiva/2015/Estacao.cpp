#include <bits/stdc++.h>
#define N 2*100050
using namespace std;
int n, m, grau[N], save[N], nivel[N];
vector<int> grafo[N], lista, P, I;

int solve()
{
    for(int i = 0; i<lista.size(); i++)
    {
        vector<int> par, impar;

        int x = lista[i];

        for(int j = 0; j<grafo[x].size(); j++)
        {
            int v = grafo[x][j];
            grau[v] --;
            if(grau[v] == 0)
            {
                lista.push_back(v);
                if(v%2 == 0)par.push_back(v);
                else impar.push_back(v);
            }
        }

        if(x%2 == 0)
        {
            if(impar.size() > 0)
            {
                for(int i = 0; i<impar.size(); i++)
                {
                    int k = impar[i];
                    nivel[k] = nivel[x] + 1;
                }
                for(int i = 0; i<par.size(); i++)
                {
                    int k = par[i];
                    nivel[k] = nivel[x] + 2;
                }
            }
        }
        else
        {
            if(par.size() > 0)
            {
                for(int i = 0; i<par.size(); i++)
                {
                    int k = par[i];
                    nivel[k] = nivel[x] + 1;
                }
                for(int i = 0; i<impar.size(); i++)
                {
                    int k = impar[i];
                    nivel[k] = nivel[x] + 2;
                }
            }
        }
    }

    int cont = 2;

    for(int i = 1; i<=2*n; i++)cont = max(cont, nivel[i]);

    return cont;
}
int main()
{
    cin>>n>>m;
    for(int i = 1; i<=m; i++)
    {
        int a, o, b;
        cin>>a>>o>>b;
        if(o == -1) swap(a, b);
        grafo[a].push_back(b);
        grau[b] ++;
        save[b]++;
    }

    for(int i = 1; i<=2*n; i++)
    {
        if(grau[i] == 0 && grafo[i].size() >0)
            lista.push_back(i);
    }


    for(int i = 0; i<lista.size(); i++)
    {
        int x = lista[i];
        if(x%2 == 0) P.push_back(x);
        else I.push_back(x);
    }

    if(I.size() > 0)
    {
        for(int i = 0; i<P.size(); i++) nivel[P[i]] = 2;
        for(int i = 0; i<I.size(); i++) nivel[I[i]] = 1;
    }
    else
        for(int i = 0; i<P.size(); i++)
            nivel[P[i]] = 1;

    int a = solve();

    lista.clear();

    for(int i = 1; i<=2*n; i++) grau[i] = save[i];


    for(int i = 1; i<=2*n; i++)
    {
        if(grau[i] == 0 && grafo[i].size() >0)
            lista.push_back(i);
    }

    if(P.size() > 0)
    {
        for(int i = 0; i<P.size(); i++) nivel[P[i]] = 1;
        for(int i = 0; i<I.size(); i++) nivel[I[i]] = 2;
    }
    else
        for(int i = 0; i<I.size(); i++) nivel[I[i]] = 1;

    int b = solve();

    cout<<min(a, b)<<"\n";
}