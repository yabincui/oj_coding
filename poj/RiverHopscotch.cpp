#include <stdio.h>

#include <algorithm>
using namespace std;

int L, N, M;
int D[50000];

bool isOk(int limit) {
  int prev = 0;
  int removeCount = 0;
  for (int i = 0; i < N && removeCount <= M; ++i) {
    if (D[i] - prev < limit) {
      removeCount++;
    } else {
      prev = D[i];
    }
  }
  return removeCount <= M;
}

int solve1() {
  int low = 0;
  int high = L;
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
  freopen("RiverHopscotch.in", "r", stdin);
  scanf("%d%d%d", &L, &N, &M);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &D[i]);
  }
  sort(D, D + N);
  int result = solve1();
  printf("%d\n", result);
  return 0;
}
