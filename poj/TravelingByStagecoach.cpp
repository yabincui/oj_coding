// POJ 2686
#include <stdio.h>
#include <string.h>

int N, M, P, A, B;

int tickets[8];

int road[31][31];

double dp[1 << 8][31];

// dp[S][k] = min(dp[S | ticket][j] + road[j][k]).
void solve() {
  for (int i = 0; i < (1 << N); ++i) {
    for (int j = 1; j <= M; ++j) {
      dp[i][j] = -1;
    }
  }
  dp[(1 << N) - 1][A] = 0;
  // O(2^N * M * M * N) = O(N * 2^N * M^2) = O(8 * 256 * 900)
    for (int i = (1 << N); i > 0; --i) {
      for (int j = 1; j <= M; ++j) {
        if (dp[i][j] < 0) {
          continue;
        }
        for (int k = 1; k <= M; ++k) {
          if (road[k][j] == -1) {
            continue;
          }
          for (int t = 0; t < N; ++t) {
            if (i & (1 << t)) {
              double add = (double)road[k][j] / tickets[t];
              double tmp = add + dp[i][j];
              double old = dp[i & ~(1 << t)][k];
              if (old < 0 || old > tmp) {
                dp[i & ~(1 << t)][k] = tmp;
              }
            }
          }
        }
      }
    }
  double min_time = -1;
  for (int i = 0; i < (1 << N); ++i) {
    if (dp[i][B] > 0) {
      if (min_time < 0 || dp[i][B] < min_time) {
        min_time = dp[i][B];
      }
    }
  }
  if (min_time < 0) {
    printf("Impossible\n");
  } else {
    printf("%f\n", min_time);
  }
}

int main() {
  freopen("TravelingByStagecoach.in", "r", stdin);
  while (scanf("%d%d%d%d%d", &N, &M, &P, &A, &B) == 5 && N != 0) {
    for (int i = 0; i < N; ++i) {
      scanf("%d", &tickets[i]);
    }
    memset(road, -1, sizeof(road));
    for (int i = 0; i < P; ++i) {
      int x, y, z;
      scanf("%d%d%d", &x, &y, &z);
      if (road[x][y] == -1 || road[x][y] > z) {
        road[x][y] = road[y][x] = z;
      }
    }
    solve();
  }
  return 0;
}
