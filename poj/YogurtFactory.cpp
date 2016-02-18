#include <limits.h>
#include <stdio.h>

#include <algorithm>

using namespace std;

int N, S;
int C[10000];
int Y[10000];

long long getMinCost() {
  long long cost = 0;
  long long bestPerUnit = 1000000000;
  for (int i = 0; i < N; ++i) {
    bestPerUnit = min(bestPerUnit + S, (long long)C[i]);
    cost += bestPerUnit * Y[i];
  }
  return cost;
}

int main() {
  freopen("YogurtFactory.in", "r", stdin);
  scanf("%d%d", &N, &S);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &C[i], &Y[i]);
  }
  long long result = getMinCost();
  printf("%lld\n", result);
  return 0;
}
