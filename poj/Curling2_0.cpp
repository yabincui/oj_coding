#include <stdio.h>

int map[20][20];
int W, H;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool canReach(int r, int c, int endR, int endC, int last_move) {
  if (last_move == 0) {
    return false;
  }
  for (int i = 0; i < 4; ++i) {
    int nr = r + dr[i];
    int nc = c + dc[i];
    if (nr < 0 || nr >= H || nc < 0 || nc >= W || map[nr][nc] == 1) {
      continue;
    }
    while (nr >= 0 && nr < H && nc >= 0 && nc < W && !(nr == endR && nc == endC) && map[nr][nc] != 1) {
      nr += dr[i];
      nc += dc[i];
    }
    if (nr < 0 || nr >= H || nc < 0 || nc >= W) {
      continue;
    }
    if (nr == endR && nc == endC) {
      return true;
    }
    if (map[nr][nc] == 1) {
      int old = map[nr][nc];
      map[nr][nc] = 0;
      bool ret = canReach(nr - dr[i], nc - dc[i], endR, endC, last_move - 1);
      map[nr][nc] = old;
      if (ret) {
        return true;
      }
    }
  }
  return false;
}

int getMinMove(int startR, int startC, int endR, int endC) {
  for (int move = 1; move <= 10; ++move) {
    if (canReach(startR, startC, endR, endC, move)) {
      return move;
    }
  }
  return -1;
}

int main() {
  freopen("Curling2_0.in", "r", stdin);
  while (scanf("%d%d", &W, &H) == 2 && W != 0 && H != 0) {
    int startR, startC, endR, endC;
    for (int r = 0; r < H; ++r) {
      for (int c = 0; c < W; ++c) {
        scanf("%d", &map[r][c]);
        if (map[r][c] == 2) {
          startR = r;
          startC = c;
        } else if (map[r][c] == 3) {
          endR = r;
          endC = c;
        }
      }
    }
    int result = getMinMove(startR, startC, endR, endC);
    printf("%d\n", result);
  }
  return 0;
}
