#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>

using namespace std;

int N, M;
int dist[300][300];

int findMinDist() {
  // Flood.
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = i + 1; j < N; ++j) {
        if (k == i || k == j) {
          continue;
        }
        if (dist[i][k] != -1 && dist[k][j] != -1) {
          int d = dist[i][k] + dist[k][j];
          if (dist[i][j] == -1 || dist[i][j] > d) {
            dist[i][j] = dist[j][i] = d;
            //printf("dist[%d][%d] = %d\n", i, j, d);
          }
        }
      }
    }
  }
  int sum[N];
  for (int i = 0; i < N; ++i) {
    sum[i] = 0;
    for (int j = 0; j < N; ++j) {
      if (i == j) {
        continue;
      }
      sum[i] += dist[i][j];
    }
    //printf("sum[%d] = %d\n", i, sum[i]);
  }
  int min_sum = sum[0];
  for (int i = 1; i < N; ++i) {
    min_sum = min(min_sum, sum[i]);
  }
  double result = min_sum * 100.0 / (N - 1);
  return (int)result;
}

int main() {
  freopen("SixDegreesOfCowvinBacon.in", "r", stdin);
  scanf("%d%d", &N, &M);
  memset(dist, -1, sizeof(dist));
  for (int i = 0; i < M; ++i) {
    int count;
    scanf("%d", &count);
    int S[count];
    for (int j = 0; j < count; ++j) {
      scanf("%d", &S[j]);
      S[j]--;
    }
    for (int j = 0; j < count; ++j) {
      for (int k = j + 1; k < count; ++k) {
        dist[S[j]][S[k]] = dist[S[k]][S[j]] = 1;
        //printf("dist[%d][%d] = dist[%d][%d] = %d\n", S[j], S[k], S[k], S[j], dist[S[j]][S[k]]);
      }
    }
  }
  int result = findMinDist();
  printf("%d\n", result);
  return 0;
}
