#include <stdio.h>

char map[20][20];
int W, H;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int getReachableCount(int r, int c) {
  int result = 0;
  for (int d = 0; d < 4; ++d) {
    int nr = r + dr[d];
    int nc = c + dc[d];
    if (nr >= 0 && nr < H && nc >= 0 && nc < W && map[nr][nc] == '.') {
      result++;
      map[nr][nc] = '#';
      result += getReachableCount(nr, nc);
    }
  }
  return result;
}

int main() {
  freopen("RedAndBlack.in", "r", stdin);
  while (scanf("%d%d", &W, &H) == 2 && W != 0 && H != 0) {
    int startR, startC;
    for (int i = 0; i < H; ++i) {
      for (int j = 0; j < W; ++j) {
        char c;
        do {
          c = getchar();
        } while (c != '.' && c != '#' && c != '@');
        map[i][j] = c;
        if (c == '@') {
          startR = i;
          startC = j;
        }
      }
    }
    int result = getReachableCount(startR, startC) + 1;
    printf("%d\n", result);
  }
  return 0;
}
