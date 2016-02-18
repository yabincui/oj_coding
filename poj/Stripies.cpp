#include <stdio.h>

#include <cmath>
#include <queue>

using namespace std;

int N;
int S[100];

int main() {
  freopen("Stripies.in", "r", stdin);
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &S[i]);
  }
  priority_queue<double> q;
  for (int i = 0; i < N; ++i) {
    q.push(S[i]);
  }
  while (q.size() > 1) {
    double a = q.top(); q.pop();
    double b = q.top(); q.pop();
    double res = 2 * sqrt(a * b);
    q.push(res);
  }
  printf("%.3f\n", q.top());
  return 0;
}
