#include <stdio.h>

#include <set>

using namespace std;

int m[5][5];

set<int> hit_set;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void permute(int r, int c, int index, int value) {
  if (index == 6) {
    hit_set.insert(value);
    return;
  }
  for (int d = 0; d < 4; ++d) {
    int nr = r + dr[d];
    int nc = c + dc[d];
    if (nr >= 0 && nr < 5 && nc >= 0 && nc < 5) {
      permute(nr, nc, index + 1, value * 10 + m[nr][nc]);
    }
  }
}

int getCount() {
  hit_set.clear();
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      permute(i, j, 1, m[i][j]);
    }
  }
  return hit_set.size();
}

int main() {
  freopen("Hopscotch.in", "r", stdin);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      scanf("%d", &m[i][j]);
    }
  }
  int result = getCount();
  printf("%d\n", result);
  return 0;
}
