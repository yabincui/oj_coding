#include <stdio.h>
#include <algorithm>

using namespace std;

int N, C;
int X[100000];

bool isOk(int limit) {
  int prev = X[0];
  int count = 1;
  for (int i = 1; i < N && count < C; ++i) {
    if (X[i] - prev >= limit) {
      prev = X[i];
      count++;
    }
  }
  return count == C;
}

int getMaxDistance() {
  sort(X, X + N);
  int low = 0, high = X[N - 1] - X[0];
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    if (isOk(mid)) {
      low = mid;
    } else {
      high = mid;
    }
  }
  if (isOk(high)) {
    return high;
  }
  return low;
}

int main() {
  freopen("AggressiveCows.in", "r", stdin);
  scanf("%d%d", &N, &C);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &X[i]);
  }
  int result = getMaxDistance();
  printf("%d\n", result);
  return 0;
}
