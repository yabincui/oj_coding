#include <stdint.h>
#include <stdio.h>

int64_t N, M;

int64_t getValue(int64_t i, int64_t j) {
  return i * i + 100000 * i + j * j - 100000 * j + i * j;
}

int64_t getBeforeInColumn(int64_t limit, int64_t j) {
  int64_t low = 1;
  int64_t high = N;
  while (low + 1 < high) {
    int64_t mid = (low + high) / 2;
    if (getValue(mid, j) < limit) {
      low = mid;
    } else {
      high = mid;
    }
  }
  if (getValue(high, j) < limit) {
    return high;
  }
  if (getValue(low, j) < limit) {
    return low;
  }
  return 0;
}

int64_t getBefore(int64_t limit) {
  int64_t result = 0;
  for (int64_t j = 1; j <= N; ++j) {
    int64_t count = getBeforeInColumn(limit, j);
    result += count;
  }
  return result;
}

int64_t getMth() {
  int64_t low = -100000LL * 100000LL;
  int64_t high = 5 * 100000LL * 100000LL;
  while (low + 1 < high) {
    int64_t mid = (low + high) / 2;
    int64_t before = getBefore(mid);
    if (before <= M - 1) {
      low = mid;
    } else {
      high = mid;
    }
  }
  if (getBefore(high) <= M - 1) {
    return high;
  }
  return low;
}

int main() {
  freopen("Matrix.in", "r", stdin);
  int tests;
  scanf("%d", &tests);
  for (int i = 0; i < tests; ++i) {
    scanf("%lld%lld", &N, &M);
    int64_t result = getMth();
    printf("%lld\n", result);
  }
  return 0;
}
