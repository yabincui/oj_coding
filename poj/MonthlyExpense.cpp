#include <stdio.h>

int N, M;
int money[100000];

bool isOk(int limit) {
  int count = 1;
  int cur = 0;
  for (int i = 0; i < N && count <= M; ++i) {
    if (money[i] > limit) {
      return false;
    }
    if (cur + money[i] > limit) {
      count++;
      cur = money[i];
    } else {
      cur += money[i];
    }
  }
  return count <= M;
}

int getMinSum() {
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
  freopen("MonthlyExpense.in", "r", stdin);
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &money[i]);
  }
  int result = getMinSum();
  printf("%d\n", result);
  return 0;
}
