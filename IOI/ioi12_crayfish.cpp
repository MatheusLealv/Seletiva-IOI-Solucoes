#include <bits/stdc++.h>
#define N 1000050
#define log 22
using namespace std;

int n;

struct node
{
    char c;

    node *anc[log];

    int sz;

    node()
    {
        for(int i = 0; i < log ; i++) anc[i] = NULL;

        sz = 0;
    }
};

node *tree[N];

void TypeLetter(int tmp, char c)
{
    if(!tree[tmp]) tree[tmp] = new node();

    tree[tmp]->c = c;

    tree[tmp]->anc[0] = tree[tmp - 1];

    for(int i = 1; i < log; i++)
    {
        (tree[tmp]->anc[i]) = (tree[tmp]->anc[i - 1] ? (tree[tmp]->anc[i - 1])->anc[i - 1] : NULL);
    }

    tree[tmp]->sz = tree[tmp - 1]->sz + 1;
}

void UndoCommands(int tmp, int k)
{
    tree[tmp] = tree[tmp - k - 1];
}

char GetLetter(int tmp, int k)
{
    node *root = tree[tmp];

    int up = root->sz - k - 1;

    for(int i = log - 1; i >= 0; i--)
    {
        if(up - (1<<i) >= 0)
        {
            up -= (1<<i);

            root = root->anc[i];
        }
    }

    return root->c;
}

int id = 0;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>n;

    tree[0] = new node();

    while(n--)
    {
        char a, b;

        int c;

        cin>>a;

        if(a == 'T')
        {
            cin>>b;

            TypeLetter(++id, b);
        }

        if(a == 'U')
        {
            cin>>c;

            UndoCommands(++id, c);
        }

        if(a == 'P')
        {
            cin>>c;

            cout<<GetLetter(id, c)<<"\n";
        }
    }
}