#include <limits.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cstdlib>

using namespace std;


int s[10];
int N;
bool used[10];

int getMinValue(int a, int count) {
  for (int i = 0; i < N && count > 0; ++i) {
    if (!used[i]) {
      used[i] = true;
      a = a * 10 + s[i];
      count--;
    }
  }
  return a;
}

int getMaxValue(int a, int count) {
  for (int i = N - 1; i > 0 && count > 0; --i) {
    if (!used[i]) {
      used[i] = true;
      a = a * 10 + s[i];
      count--;
    }
  }
  return a;
}

int getMinDiff() {
  int min_diff = INT_MAX;
  if (N % 2 == 0) {
    if (N == 2) {
      return s[1] - s[0];
    }
    for (int i = 0; i < N - 1; ++i) {
      memset(used, false, sizeof(used));
      if (s[i] == 0) {
        continue;
      }
      used[i] = used[i + 1] = true;
      int a = getMaxValue(s[i], N / 2 - 1);
      int b = getMinValue(s[i + 1], N / 2 - 1);
      min_diff = min(min_diff, b - a);
    }
  } else {
    memset(used, false, sizeof(used));
    int a;
    if (s[0] == 0) {
      a = s[1];
      used[1] = true;
    } else {
      a = s[0];
      used[0] = true;
    }
    int b = s[N - 1];
    used[N - 1] = true;
    a = getMinValue(a, N / 2);
    b = getMaxValue(b, N / 2 - 1);
    min_diff = a - b;
  }
  return min_diff;
}

int main() {
  freopen("SmallestDifference.in", "r", stdin);
  int test_count;
  scanf("%d", &test_count);
  getchar();
  for (int test = 1; test <= test_count; ++test) {
    N = 0;
    while (true) {
      char c = getchar();
      if (c == '\n') {
        break;
      }
      if (c >= '0' && c <= '9') {
        s[N++] = c - '0';
      }
    }
    int result = getMinDiff();
    printf("%d\n", result);
  }
}
