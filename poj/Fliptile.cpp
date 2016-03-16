#include <stdio.h>
#include <string.h>

int M, N;

int s[15][15];

int best[15][15];
int bestCount;

void flipNode(int grid[15][15], int r, int c) {
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
  for (int init = 0; init < (1 << N); ++init) {
    int grid[15][15];
    int flip[15][15];
    memcpy(grid, s, sizeof(s));
    memset(flip, 0, sizeof(flip));
    for (int i = 0; i < N; ++i) {
      if (init & (1 << i)) {
        flip[0][i] = 1;
        flipNode(grid, 0, i);
      }
    }
    for (int i = 1; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        if (grid[i-1][j] == 1) {
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
    int flip_count = 0;
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        if (flip[i][j]) {
          flip_count++;
        }
      }
    }
    int compare = 0;
    if (bestCount == -1 || bestCount > flip_count) {
      compare = -1;
    } else if (bestCount < flip_count) {
      compare = 1;
    }
    for (int i = 0; i < M && compare == 0; ++i) {
      for (int j = 0; j < N && compare == 0; ++j) {
        if (best[i][j] != flip[i][j]) {
          compare = (best[i][j] > flip[i][j]) ? -1 : 1;
        }
      }
    }
    if (compare < 0) {
      bestCount = flip_count;
      memcpy(best, flip, sizeof(flip));
    }
  }
}

int main() {
  freopen("Fliptile.in", "r", stdin);
  scanf("%d%d", &M, &N);
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &s[i][j]);
    }
  }
  bestCount = -1;
  getResult();
  if (bestCount == -1) {
    printf("IMPOSSIBLE\n");
  } else {
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        printf("%d%c", best[i][j], (j != N - 1) ? ' ' : '\n');
      }
    }
  }
  return 0;
}
