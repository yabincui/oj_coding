#include <stdio.h>

#include <algorithm>
using namespace std;

int N;
int X[100000];

int getCountBiggerThan(int value, int start, int end) {
  int low = start;
  int high = end - 1;
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    if (X[mid] > value) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  int ret = 0;
  if (X[high] > value) {
    ret = end - high;
  }
  if (X[low] > value) {
    ret = end - low;
  }
  //printf("getCountBiggerThan(value %d, start %d, end %d), ret = %d\n",
  //    value, start, end, ret);
  return ret;
}

int getBefore(int limit) {
  int before_count = 0;
  for (int i = 1; i < N; ++i) {
    int a = X[i] - limit;
    int count = getCountBiggerThan(a, 0, i);
    before_count += count;
  }
  //printf("getBefore(%d) = %d\n", limit, before_count);
  return before_count;
}

int getMedian() {
  sort(X, X + N);
  int low = 0;
  int high = X[N-1] - X[0];
  int all = N * (N - 1) / 2;
  int half;
  if (all % 2 == 0) {
    half = all / 2 - 1;
  } else {
    half = all / 2;
  }
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    int before = getBefore(mid);
    if (before <= half) {
      low = mid;
    } else {
      high = mid;
    }
  }
  int before = getBefore(high);
  if (before <= half) {
    return high;
  }
  return low;
}

int main() {
  freopen("Median.in", "r", stdin);
  while (scanf("%d", &N) == 1 && N != 0) {
    for (int i = 0; i < N; ++i) {
      scanf("%d", &X[i]);
    }
    int result = getMedian();
    printf("%d\n", result);
  }
  return 0;
}
