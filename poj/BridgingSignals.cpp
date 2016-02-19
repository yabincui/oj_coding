#include <stdio.h>

int N;
int S[40000];
int L[40000];

int insert(int value, int maxL) {
  int low = 0;
  int high = maxL - 1;
  if (value > L[maxL - 1]) {
    L[maxL] = value;
    return maxL + 1;
  }
  while (low < high) {
    int mid = (low + high) / 2;
    if (value > L[mid]) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  L[high] = value;
  return maxL;
}

int getLongest() {
  int maxL = 1;
  L[0] = S[0];
  for (int i = 1; i < N; ++i) {
    maxL = insert(S[i], maxL);
  }
  return maxL;
}

int main() {
  freopen("BridgingSignal.in", "r", stdin);
  int test_count;
  scanf("%d", &test_count);
  for (int i = 0; i < test_count; ++i) {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
      scanf("%d", &S[i]);
    }
    int result = getLongest();
    printf("%d\n", result);
  }
  return 0;
}
