#include <stdio.h>
#include <string.h>

int s[20];

void flipNode(int t[20], int i) {
  if (i > 0) {
    t[i-1] = 1 - t[i-1];
  }
  t[i] = 1 - t[i];
  if (i < 19) {
    t[i+1] = 1 - t[i+1];
  }
}

int getResult() {
  int min_count = -1;
  for (int init = 0; init < 2; ++init) {
    int t[20];
    memcpy(t, s, sizeof(t));
    int count = 0;
    if (init) {
      count++;
      flipNode(t, 0);
    }
    for (int i = 1; i < 20; ++i) {
      if (t[i-1]) {
        flipNode(t, i);
        count++;
      }
    }
    if (t[19] == 1) {
      continue;
    }
    if (min_count == -1 || min_count > count) {
      min_count = count;
    }
  }
  return min_count;
}

int main() {
  freopen("TheWaterBowls.in", "r", stdin);
  for (int i = 0; i < 20; ++i) {
    scanf("%d", &s[i]);
  }
  int result = getResult();
  printf("%d\n", result);
  return 0;
}
