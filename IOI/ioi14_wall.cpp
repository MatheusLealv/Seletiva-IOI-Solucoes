#include <bits/stdc++.h>
#define inf 2000000000
#define mid ((a + b)/2)
#define N 2000000
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;


int n, q, ans[N];

struct node
{
    int add, remove;

    node(){add = 0, remove = inf;}
};

node tree[4*N];

void join(int nod)
{
    tree[2*nod].remove = min(tree[2*nod].remove, tree[nod].remove);

    tree[2*nod].remove = max(tree[2*nod].remove, tree[nod].add);

    tree[2*nod].add = min(tree[2*nod].add, tree[nod].remove);

    tree[2*nod].add = max(tree[2*nod].add, tree[nod].add);

    tree[2*nod + 1].add = max(tree[2*nod + 1].add, tree[nod].add);

    tree[2*nod + 1].remove = min(tree[2*nod + 1].remove, tree[nod].remove);

    tree[2*nod + 1].remove = max(tree[2*nod + 1].remove, tree[nod].add);

    tree[2*nod + 1].add = min(tree[2*nod + 1].add, tree[nod].remove);

    tree[2*nod + 1].add = max(tree[2*nod + 1].add, tree[nod].add);

    tree[2*nod + 1].add = max(tree[2*nod + 1].add, tree[nod].add);

}

void build(int nod, int a, int b, int i, int j, int h)
{
    if(j < a || i > b) return;

    if(i <= a && j >= b)
    {
        tree[nod].add = max(tree[nod].add, h);

        tree[nod].remove = max(tree[nod].remove, h);

        return;
    }

    join(nod);

    tree[nod].add = 0,  tree[nod].remove = inf;

    build(2*nod, a, mid, i, j, h), build(2*nod + 1, mid + 1, b, i, j, h);
}

void Remove(int nod, int a, int b, int i, int j, int h)
{
    if(j < a || i > b) return;

    if(i <= a && j >= b)
    {
        tree[nod].add = min(tree[nod].add, h);

        tree[nod].remove = min(tree[nod].remove, h);

        return;
    }

    join(nod);

    tree[nod].add = 0, tree[nod].remove = inf;

    Remove(2*nod, a, mid, i, j, h), Remove(2*nod + 1, mid + 1, b, i, j, h);
}

void get_ans(int nod, int a, int b)
{
    if(a == b) ans[a] = tree[nod].add;
    else
    {
        join(nod);

        get_ans(2*nod, a, mid), get_ans(2*nod + 1, mid + 1, b);
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>n>>q;
    
    for(int i = 1; i <= q; i++)
    {
        int t, a, b, c;

        cin>>t>>a>>b>>c;

        if(t == 1) build(1, 0, n, a, b, c);
        else Remove(1, 0, n, a, b, c);
    }

    get_ans(1, 0, n);

    for(int i = 0; i < n; i++) cout<<ans[i]<<"\n";
}
