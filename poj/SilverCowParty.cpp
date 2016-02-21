#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

int N, M, X;

int cost[1000][1000];
bool visited[1000];
int distToParty[1000];
int distFromParty[1000];

int getMaxTime() {
  memset(distToParty, -1, sizeof(distToParty));
  distToParty[X] = 0;
  memset(visited, false, sizeof(visited));
  for (int t = 0; t < N; ++t) {
    int k = -1;
    for (int i = 0; i < N; ++i) {
      if (!visited[i] && distToParty[i] != -1 && (k == -1 || distToParty[i] < distToParty[k])) {
        k = i;
      }
    }
    visited[k] = true;
    for (int i = 0; i < N; ++i) {
      if (!visited[i] && cost[i][k] != -1) {
        int c = distToParty[k] + cost[i][k];
        if (distToParty[i] == -1 || distToParty[i] > c) {
          distToParty[i] = c;
        }
      }
    }
  }

  memset(distFromParty, -1, sizeof(distFromParty));
  distFromParty[X] = 0;
  memset(visited, false, sizeof(visited));
  for (int t = 0; t < N; ++t) {
    int k = -1;
    for (int i = 0; i < N; ++i) {
      if (!visited[i] && distFromParty[i] != -1 && (k == -1 || distFromParty[i] < distFromParty[k])) {
        k = i;
      }
    }
    visited[k] = true;
    for (int i = 0; i < N; ++i) {
      if (!visited[i] && cost[k][i] != -1) {
        int c = distFromParty[k] + cost[k][i];
        if (distFromParty[i] == -1 || distFromParty[i] > c) {
          distFromParty[i] = c;
        }
      }
    }
  }
  int result = 0;
  for (int i = 0; i < N; ++i) {
    int sum = distFromParty[i] + distToParty[i];
    result = max(result, sum);
  }
  return result;
}

int main() {
  freopen("SilverCowParty.in", "r", stdin);
  scanf("%d%d%d", &N, &M, &X);
  X--;
  memset(cost, -1, sizeof(cost));
  for (int i = 0; i < M; ++i) {
    int a, b, t;
    scanf("%d%d%d", &a, &b, &t);
    a--;
    b--;
    if (cost[a][b] == -1 || cost[a][b] > t) {
      cost[a][b] = t;
    }
  }
  int result = getMaxTime();
  printf("%d\n", result);
  return 0;
}
