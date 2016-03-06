#include <stdio.h>

int N, K;
int A[100000];

bool isOk(int limit) {
  int dry_time = 0;
  for (int i = 0; i < N && dry_time <= limit; ++i) {
    if (A[i] > limit) {
      if (K == 1) {
        return false;
      }
      int need = (int)((double)(A[i] - limit) / (K - 1));
      if ((double)need * (K - 1) < A[i] - limit) {
        need++;
      }
      dry_time += need;
    }
  }
  return dry_time <= limit;
}

int getMinTime() {
  int low = 0;
  int high = 1000000000;
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    if (isOk(mid)) {
      high = mid;
    } else {
      low = mid;
    }
  }
  if (isOk(low)) {
    return low;
  }
  return high;
}

int main() {
  freopen("Drying.in", "r", stdin);
  while (scanf("%d", &N) == 1) {
    for (int i = 0; i < N; ++i) {
      scanf("%d", &A[i]);
    }
    scanf("%d", &K);
    int result = getMinTime();
    printf("%d\n", result);
  }
  return 0;
}
