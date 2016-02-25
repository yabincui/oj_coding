#include <stdio.h>
#include <string.h>

int N;
int m[100][100];

int getMinCost() {
  bool visited[100];
  memset(visited, false, sizeof(visited));
  int total_cost = 0;
  int cost[100];
  memset(cost, -1, sizeof(cost));
  cost[0] = 0;
  for (int t = 0; t < N; ++t) {
    int k = -1;
    for (int i = 0; i < N; ++i) {
      if (!visited[i] && cost[i] != -1 && (k == -1 || cost[i] < cost[k])) {
        k = i;
      }
    }
    visited[k] = true;
    total_cost += cost[k];
    for (int i = 0; i < N; ++i) {
      if (!visited[i] && (cost[i] == -1 || cost[i] > m[i][k])) {
        cost[i] = m[i][k];
      }
    }
  }
  return total_cost;
}

int main() {
  freopen("AgriNet.in", "r", stdin);
  while (scanf("%d", &N) == 1 && N != 0) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        scanf("%d", &m[i][j]);
      }
    }
    int result = getMinCost();
    printf("%d\n", result);
  }
}
