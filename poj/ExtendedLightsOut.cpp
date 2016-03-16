#include <stdio.h>
#include <string.h>

#define M 5
#define N 6

int s[M][N];
int answer[M][N];

void flipNode(int grid[M][N], int r, int c) {
  int dr[5] = {-1, 1, 0, 0, 0};
  int dc[5] = {0, 0, -1, 1, 0};
  for (int i = 0; i < 5; ++i) {
    int nr = r + dr[i];
    int nc = c + dc[i];
    if (nr < 0 || nr >= M || nc < 0 || nc >= N) {
      continue;
    }
    grid[nr][nc] = 1 - grid[nr][nc];
  }
}

void getResult() {
  for (int init = 0; init < (1 << N); init++) {
    int flip[M][N];
    memset(flip, 0, sizeof(flip));
    int grid[M][N];
    memcpy(grid, s, sizeof(s));
    for (int i = 0; i < N; ++i) {
      if (init & (1 << i)) {
        flip[0][i] = 1;
        flipNode(grid, 0, i);
      }
    }
    for (int i = 1; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        if (grid[i-1][j]) {
          flip[i][j] = 1;
          flipNode(grid, i, j);
        }
      }
    }
    bool ok = true;
    for (int i = 0; i < N; ++i) {
      if (grid[M-1][i] == 1) {
        ok = false;
        break;
      }
    }
    if (!ok) {
      continue;
    }
    memcpy(answer, flip, sizeof(flip));
    return;
  }
  while (true);
}

int main() {
  freopen("ExtendedLightsOut.in", "r", stdin);
  int test;
  scanf("%d", &test);
  for (int t = 1; t <= test; ++t) {
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        scanf("%d", &s[i][j]);
      }
    }
    getResult();
    printf("PUZZLE #%d\n", t);
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        printf("%d%c", answer[i][j], (j != N - 1) ? ' ' : '\n');
      }
    }
  }
  return 0;
}
