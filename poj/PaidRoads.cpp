// POJ 3411
#include <stdio.h>
#include <string.h>

#include <algorithm>
using namespace std;

int N, M;

struct Road {
  int a, b, c, P, R;
} roads[10];

int dp[1 << 10][10];

void solve() {
  memset(dp, -1, sizeof(dp));
  dp[1 << 0][0] = 0;
  for (int i = 1; i < (1 << N); ++i) {
    for (int loop = 0; loop < N; ++loop) {
    for (int j = 0; j < N; ++j) {
      if (dp[i][j] == -1) {
        continue;
      }
      for (int r = 0; r < M; ++r) {
        if (roads[r].a == j) {
          int next = i | (1 << roads[r].b);
          int cost = roads[r].R;
          if (i & (1 << roads[r].c)) {
            cost = min(cost, roads[r].P);
          }
          cost += dp[i][j];
          if (dp[next][roads[r].b] == -1 || dp[next][roads[r].b] > cost) {
            dp[next][roads[r].b] = cost;
            //printf("dp[%d][%d] = %d\n", next, roads[r].b, dp[next][roads[r].b]);
          }
        }
      }
    }
    }
  }
  int result = -1;
  for (int i = 0; i < (1 << N); ++i) {
    int t = dp[i][N - 1];
    if (t != -1) {
      if (result == -1 || result > t) {
        result = t;
      }
    }
  }
  if (result == -1) {
    printf("impossible\n");
  } else {
    printf("%d\n", result);
  }
}

int main() {
  freopen("PaidRoads.in", "r", stdin);
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; ++i) {
    scanf("%d%d%d%d%d", &roads[i].a, &roads[i].b, &roads[i].c, &roads[i].P, &roads[i].R);
    roads[i].a--;
    roads[i].b--;
    roads[i].c--;
  }
  solve();
  return 0;
}
