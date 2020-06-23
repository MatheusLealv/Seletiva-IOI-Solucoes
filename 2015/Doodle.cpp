#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef pair<pair<int, int>, pair<int, int> > line;

int n, x = 0, y = 0, cont = 0, bit[100050], q;

vector<line> reta, R;
vector<int> X, Y;
map<int, int> compx, compy;

line add(int xi, int yi, int xii, int yii)
{
    return make_pair(make_pair(xi, yi), make_pair(xii, yii));
}

void upd(int i, int v)
{
    for(; i <= cont + 10; i += (i&-i)) bit[i] += v;
}
int query(int i)
{
    int sum = 0;
    for(; i > 0; i -= (i&-i)) sum += bit[i];
    return sum;
}

int resp(int T)
{
    int k = 0;

    vector<line> evento;

    for(int i = 0; i<T; i++)
    {
        if(i%2 == 0)
        {
            int xi = reta[i].f.f, xii = reta[i].s.f, yi = reta[i].f.s;

            if(xii < xi) swap(xi, xii);

            evento.push_back(add(xi, yi, 0, 0));
            evento.push_back(add(xii, yi, 0, 1));
        }
        else
        {
            int xi = reta[i].f.f, yi = reta[i].f.s, yii = reta[i].s.s;
            if(yii < yi) swap(yi, yii);
            evento.push_back(add(xi, yi, yii, 2));
        }
    }

    sort(evento.begin(), evento.end());

    for(int i = 0; i<evento.size(); i++)
    {
        int tipo = evento[i].s.s;
        if(tipo == 0)
        {
            int yi = evento[i].f.s;
            upd(yi, 1);
        }
        if(tipo == 1)
        {
            int yi = evento[i].f.s;
            upd(yi, -1);
        }
        if(tipo == 2)
        {
            int yi = evento[i].f.s, yii = evento[i].s.f;
            k += query(max(yi, yii) - 1) - query(min(yi, yii));
        }
    }

    return k;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n>>q;

    X.push_back(0);
    Y.push_back(0);

    for(int i = 0; i<n; i++)
    {
        int len;
        cin>>len;

        if(i%2 == 0)
        {
            R.push_back(add(x, y, x + len, y));
            x += len;
            X.push_back(x);
        }
        else
        {
            R.push_back(add(x, y, x, y + len));
            y += len;
            Y.push_back(y);
        }
    }

    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());

    for(int i = 0; i<X.size(); i++)
    {
        if(compx[X[i]] == 0)
        {
            compx[X[i]] = ++cont;
        }
    }

    cont = 0;

     for(int i = 0; i<Y.size(); i++)
     {
        if(compy[Y[i]] == 0)
        {
            compy[Y[i]] = ++cont;
        }
     }

     for(int i = 0; i<R.size(); i++)
     {
        if(i%2 == 0)
        {
            int xi = compx[R[i].f.f], xii = compx[R[i].s.f], yi = compy[R[i].f.s];
            reta.push_back(add(xi, yi, xii, yi));
        }
        else
        {
            int xi = compx[R[i].f.f], yi = compy[R[i].f.s], yii = compy[R[i].s.s];
            reta.push_back(add(xi, yi, xi, yii));
        }
     }

    int a = 0, b = n, mid, ITS = 0,TAM = 0;

    while(b >= a)
    {
        mid = (a+b)/2;

        int qtd = resp(mid);

        if(qtd >= q)
        {
            ITS = qtd;
            TAM = mid;
            b = mid - 1;
        }
        else
        {
            if(ITS <= qtd)
            {
                ITS = qtd;
                TAM = mid;
            }

            a = mid + 1;
        }
    }

    cout<<TAM<<" "<<ITS<<"\n";


}