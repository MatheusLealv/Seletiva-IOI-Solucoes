#include <bits/stdc++.h>
#define N 200050
using namespace std;
 
int n, q, pai[N], peso[N], dmin[N][8], dmax[N][8], p[N][3];
 
inline int Find(int x)
{
	if(pai[x] == x) return x;
 
	return Find(pai[x]);
}
 
struct edge{
 
    int a, b, pai_a, pai_b;
 
    int peso_a, peso_b, dminA[8], dminB[8], dmaxA[8], dmaxB[8];
 
    edge(int x, int y){
 
        a = x, b = y;
 
        a = Find(a), b = Find(b);
 
        pai_a = pai[a], pai_b = pai[b];
 
        peso_a = peso[a], peso_b = peso[b];
 
        for(int mask = 0; mask < 8; mask++)
        {
        	dminA[mask] = dmin[a][mask];
        	dmaxA[mask] = dmax[a][mask];
        	dminB[mask] = dmin[b][mask];
        	dmaxB[mask] = dmax[b][mask];
        }
    }
};
 
vector<edge> pilha;
 
inline void join(int a, int b)
{
	edge T = edge(a, b);
 
	pilha.push_back(T);
 
	a = Find(a), b = Find(b);
 
	if(a == b) return;
 
	if(peso[a] < peso[b]) swap(a, b);
 
	for(int mask = 0; mask < 8; mask ++)
	{
		dmin[a][mask] = min(dmin[a][mask], dmin[b][mask]);
 
		dmax[a][mask] = max(dmax[a][mask], dmax[b][mask]);
	}
 
	pai[b] = a;
 
	if(peso[a] == peso[b]) peso[a] ++;
}
 
inline void remove()
{
	if(pilha.empty()) return;
 
	edge last = pilha.back();
 
	pilha.pop_back();
 
	int a = last.a, b = last.b;
 
	pai[a] = last.pai_a, pai[b] = last.pai_b;
 
	peso[a] = last.peso_a, peso[b] = last.peso_b;
 
	for(int mask = 0; mask < 8; mask++)
	{
		dmin[a][mask] = last.dminA[mask];
		dmax[a][mask] = last.dmaxA[mask];
		dmin[b][mask] = last.dminB[mask];
		dmax[b][mask] = last.dmaxB[mask];
	}
}
 
inline int query(int a, int b)
{
	a = Find(a), b = Find(b);
 
	int ans = 0;
 
	for(int mask = 0; mask < 8; mask ++)
			ans = max({ans, dmax[a][mask] - dmin[b][mask], dmax[b][mask] - dmin[a][mask]});
 
	return ans;
}
 
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
 
	cin>>n;
 
	for(int i = 1; i <= n; i++)
	{
		cin>>p[i][0]>>p[i][1]>>p[i][2];
 
		pai[i] = i;
 
		for(int mask = 0; mask < 8; mask ++)
		{
			int sum = 0;
 
			if(mask & 1) sum += p[i][0];
 
			else sum -= p[i][0];
 
			if(mask & 2) sum += p[i][1];
 
			else sum -= p[i][1];
 
			if(mask & 4) sum += p[i][2];
 
			else sum -= p[i][2];
 
			dmin[i][mask] = dmax[i][mask] = sum;
		}
	}
 
	cin>>q;
 
	for(int i = 1, t, a, b; i <= q; i++)
	{
		cin>>t;
 
		if(t != 2) cin>>a>>b;
 
		if(t == 1) join(a, b);
 
		else if(t == 2) remove();
 
		else cout<<query(a, b)<<"\n";
	}
}
