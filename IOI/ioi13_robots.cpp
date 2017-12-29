#include <bits/stdc++.h>
#define f first
#define s second
#define N 1000050
#define inf 2000000010
using namespace std;
typedef pair<int, int> pii;

int n, m, A, B, weak[N], small[N], used[N];

struct robot
{
  int w, s, id;
};

robot R[N], Ri[N], Rii[N];

inline bool cmp1(robot a, robot b)
{
  return a.w < b.w;
}

inline bool cmp2(robot a, robot b)
{
  return a.s < b.s;
}

inline bool solve(int k)
{
  int j = 1;

  for(int i = 1; i <= n; i++) used[i] = 0;

  priority_queue < pii > pq;

  for(int i = 1; i <= A; i++)
  {
    while(j <= n && Ri[j].w < weak[i])
    {
      pq.push(pii(Ri[j].s, Ri[j].id));

      j ++;
    }

    for(int cnt = 0; cnt < k && !pq.empty(); cnt ++)
    {
      int id = pq.top().s;

      pq.pop();

      used[id] = 1;
    }
  }

  while(!pq.empty()) pq.pop();

  j = 1;

  for(int i = A + 1; i <= A + B; i++)
  {
    while(j <= n && Rii[j].s < small[i])
    {
      if(!used[Rii[j].id]) pq.push(pii(Rii[j].s, Rii[j].id));

      j ++;
    }

    for(int cnt = 0; cnt < k && !pq.empty(); cnt ++)
    {
      int id = pq.top().s;

      pq.pop();

      used[id] = 1;
    }
  }

  bool ok = true;

  for(int i = 1; i <= n; i++) if(!used[i]) ok = false;

  return ok;
}

int putaway(int Ai, int Bi, int T, int X[], int Y[], int W[], int S[])
{
    n = T, A = Ai, B = Bi;

    for(int i = 1; i <= A; i++) weak[i] = X[i - 1];

    for(int i = A + 1; i <= A + B ; i++) small[i] = Y[i - A - 1];

    for(int i = 1; i <= n; i++) R[i].w = W[i - 1], R[i].s = S[i - 1], R[i].id = i;

    for(int i = 1; i <= n; i++) Ri[i] = R[i], Rii[i] = R[i];

    sort(Ri + 1, Ri + n + 1, cmp1);

    sort(Rii + 1, Rii + n + 1, cmp2);

    sort(weak + 1, weak + A + 1);

    sort(small + A + 1, small + A + B + 1);

    int ini = 1, fim = n, mid, best = -1;

    while(fim >= ini)
    {
      mid = (ini + fim)/2;

      if(solve(mid)) fim = mid - 1, best = mid;

      else ini = mid + 1;
    }

    return best;
}

int X[N], Y[N], W[N], S[N], a, b, t;

int main()
{
  scanf("%d %d %d", &a, &b, &t);

  for(int i = 0; i < a; i++) scanf("%d", &X[i]);

  for(int i = 0; i < b; i++) scanf("%d", &Y[i]); 

  for(int i = 0; i < t; i++) scanf("%d %d", &W[i], &S[i]);

  printf("%d\n", putaway(a, b, t, X, Y, W, S));
}