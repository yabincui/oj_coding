#include <stdio.h>
#include <string.h>

#include <algorithm>
using namespace std;

int N, M, R;

struct Edge {
  int x, y, t;
  char type;  // S or L
} edges[10000];

int visitOrder[1000];

// dpWater[i][j] is the min time to move from i to j by water.
int dpWater[200][200];

// dpLand[i][j] is the min time to move from i to j by land.
int dpLand[200][200];

void calculateDp() {
  memset(dpWater, -1, sizeof(dpWater));
  for (int i = 0; i < N; ++i) {
    dpWater[i][i] = 0;
  }
  memset(dpLand, -1, sizeof(dpLand));
  for (int i = 0; i < N; ++i) {
    dpLand[i][i] = 0;
  }
  for (int i = 0; i < M; ++i) {
    int a = edges[i].x;
    int b = edges[i].y;
    if (edges[i].type == 'L') {
      if (dpLand[a][b] == -1 || dpLand[a][b] > edges[i].t) {
        dpLand[a][b] = dpLand[b][a] = edges[i].t;
        //printf("dpLand[%d][%d] = %d\n", a, b, dpLand[a][b]);
      }
    } else {
      if (dpWater[a][b] == -1 || dpWater[a][b] > edges[i].t) {
        dpWater[a][b] = dpWater[b][a] = edges[i].t;
        //printf("dpWater[%d][%d] = %d\n", a, b, dpWater[a][b]);
      }
    }
  }
  // Flood.
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = i + 1; j < N; ++j) {
        if (k == i || k == j) {
          continue;
        }
        if (dpLand[i][k] != -1 && dpLand[k][j] != -1) {
          int t = dpLand[i][k] + dpLand[k][j];
          if (dpLand[i][j] == -1 || dpLand[i][j] > t) {
            dpLand[i][j] = dpLand[j][i] = t;
          }
        }
        if (dpWater[i][k] != -1 && dpWater[k][j] != -1) {
          int t = dpWater[i][k] + dpWater[k][j];
          if (dpWater[i][j] == -1 || dpWater[i][j] > t) {
            dpWater[i][j] = dpWater[j][i] = t;
          }
        }
      }
    }
  }
  /*
  for (int i = 0; i < N; ++i) {
    for (int j = i; j < N; ++j) {
      printf("dpLand[%d][%d] = %d\n", i, j, dpLand[i][j]);
    }
  }
  for (int i = 0; i < N; ++i) {
    for (int j = i; j < N; ++j) {
      printf("dpWater[%d][%d] = %d\n", i, j, dpWater[i][j]);
    }
  }
  */
}

int getMinTime() {
  calculateDp();
  int dp[2][200];
  memset(dp, -1, sizeof(dp));
  dp[0][visitOrder[0]] = 0;
  int *prev = dp[0];
  int *cur = dp[1];
  int source = visitOrder[0];
  for (int i = 1; i < R; ++i) {
    //printf("i = %d\n", i);
    int target = visitOrder[i];
    if (source == target) {
      continue;
    }
    memset(cur, -1, sizeof(dp[0]));
    for (int targetWater = 0; targetWater < N; ++targetWater) {
      for (int sourceWater = 0; sourceWater < N; ++sourceWater) {
        //printf("i = %d, source = %d, target = %d, sourceWater = %d, targetWater = %d\n",
        //        i, source, target, sourceWater, targetWater);
        if (prev[sourceWater] == -1) {
          continue;
        }
        int t = -1;
        if (sourceWater != targetWater) {
          if (prev[sourceWater] == -1 || dpLand[source][sourceWater] == -1 ||
              dpWater[sourceWater][targetWater] == -1 || dpLand[targetWater][target] == -1) {
            continue;
          }
          t = prev[sourceWater] + dpLand[source][sourceWater] +
                  dpWater[sourceWater][targetWater] + dpLand[targetWater][target];
        } else {
          if (prev[sourceWater] == -1 || dpLand[source][target] == -1) {
            continue;
          }
          t = prev[sourceWater] + dpLand[source][target];
        }
        if (cur[targetWater] == -1 || cur[targetWater] > t) {
          cur[targetWater] = t;
          //printf("cur[%d] = %d\n", targetWater, t);
        }
      }
    }
    swap(prev, cur);
    source = target;
  }
  int result = -1;
  for (int i = 0; i < N; ++i) {
    if (prev[i] != -1 && (result == -1 || result > prev[i])) {
      result = prev[i];
    }
  }
  return result;
}

int main() {
  freopen("MrRitoPostOffice.in", "r", stdin);
  //freopen("2200-input.txt", "r", stdin);
  while (scanf("%d%d", &N, &M) == 2 && !(N == 0 && M == 0)) {
    for (int i = 0; i < M; ++i) {
      char buf[10];
      scanf("%d%d%d%s", &edges[i].x, &edges[i].y, &edges[i].t, buf);
      edges[i].x--;
      edges[i].y--;
      edges[i].type = buf[0];
      //printf("edge %d, x %d, y %d, t %d, type %c\n", i, edges[i].x, edges[i].y, edges[i].t, edges[i].type);
    }
    scanf("%d", &R);
    for (int i = 0; i < R; ++i) {
      scanf("%d", &visitOrder[i]);
      visitOrder[i]--;
    }
    int result = getMinTime();
    printf("%d\n", result);
  }
  return 0;
}
