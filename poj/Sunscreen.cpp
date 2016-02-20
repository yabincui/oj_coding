#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

int C, L;

struct Cow {
  int minf;
  int maxf;
} cows[2500];

struct Screen {
  int f;
  int count;
} screen[2500];

bool dp[2500];

bool compareCow(const Cow& c1, const Cow& c2) {
  if (c1.maxf != c2.maxf) {
    return c1.maxf < c2.maxf;
  }
  return c1.minf < c2.minf;
}

bool compareScreen(const Screen& s1, const Screen& s2) {
  return s1.f < s2.f;
}

int getMaxCount() {
  memset(dp, false, sizeof(dp));
  for (int i = 0; i < L; ++i) {
    int count = screen[i].count;
    for (int j = 0; j < C && count > 0; ++j) {
      if (!dp[j] && cows[j].minf <= screen[i].f && cows[j].maxf >= screen[i].f) {
        dp[j] = true;
        --count;
      }
    }
  }
  int count = 0;
  for (int i = 0; i < C; ++i) {
    if (dp[i]) {
      count++;
    }
  }
  return count;
}

int main() {
  freopen("Sunscreen.in", "r", stdin);
  scanf("%d%d", &C, &L);
  for (int i = 0; i < C; ++i) {
    scanf("%d%d", &cows[i].minf, &cows[i].maxf);
  }
  for (int i = 0; i < L; ++i) {
    scanf("%d%d", &screen[i].f, &screen[i].count);
  }
  sort(cows, &cows[C], compareCow);
  sort(screen, &screen[L], compareScreen);
  int result = getMaxCount();
  printf("%d\n", result);
  return 0;
}
