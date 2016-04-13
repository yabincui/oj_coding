// POJ 2836
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <utility>
using namespace std;

int N;
pair<int, int> points[15];

int prebuild_mask[15][15];
int prebuild_area[15][15];

int dp[1 << 15];


void solve() {
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      int x1 = points[i].first;
      int y1 = points[i].second;
      int x2 = points[j].first;
      int y2 = points[j].second;
      if (points[i].first == points[j].first) {
        x2 = x1 + 1;
      } else if (points[i].second == points[j].second) {
        y2 = y1 + 1;
      }
      int xmin = min(x1, x2);
      int ymin = min(y1, y2);
      int xmax = max(x1, x2);
      int ymax = max(y1, y2);
      int area = (xmax - xmin) * (ymax - ymin);
      int mask = 0;
      for (int k = 0; k < N; ++k) {
        if (points[k].first >= xmin && points[k].first <= xmax &&
            points[k].second >= ymin && points[k].second <= ymax) {
          mask |= (1 << k);
        }
      }
      prebuild_mask[i][j] = mask;
      prebuild_area[i][j] = area;
//      printf("prebuild_mask[%d][%d] = %d, %d\n", i, j, mask, area);
    }
  }

  memset(dp, -1, sizeof(dp));
  dp[0] = 0;
  for (int i = 0; i < (1 << N); ++i) {
    if (dp[i] == -1) {
      continue;
    }
    for (int j = 0; j < N; ++j) {
      for (int k = j + 1; k < N; ++k) {
        int area = prebuild_area[j][k] + dp[i];
        int ni = i | prebuild_mask[j][k];
        if (dp[ni] == -1 || dp[ni] > area) {
          dp[ni] = area;
          //printf("dp[%d] = %d\n", ni, area);
        }
      }
    }
  }
  printf("%d\n", dp[(1 << N) - 1]);
}

int main() {
  freopen("RectangularCovering.in", "r", stdin);
  while (scanf("%d", &N) == 1 && N != 0) {
    for (int i = 0; i < N; ++i) {
      scanf("%d%d", &points[i].first, &points[i].second);
    }
    solve();
  }
  return 0;
}
