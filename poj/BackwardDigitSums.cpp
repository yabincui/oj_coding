#include <stdio.h>
#include <string.h>

int N, sum;
int s[10];
bool used[11];
bool found;

void calculate() {
  int t[10];
  memcpy(t, s, sizeof(s));
  for (int count = N; count > 1; --count) {
    for (int i = 0; i < count - 1; ++i) {
      t[i] += t[i + 1];
    }
  }
  if (t[0] == sum) {
    found = true;
  }
}

void permute(int index) {
  if (index == N) {
    calculate();
    return;
  }
  for (int i = 1; i <= N; ++i) {
    if (!used[i]) {
      used[i] = true;
      s[index] = i;
      permute(index + 1);
      if (found) break;
      used[i] = false;
    }
  }
}

int main() {
  freopen("BackwardDigitSums.in", "r", stdin);
  scanf("%d%d", &N, &sum);
  found = false;
  memset(used, false, sizeof(used));
  permute(0);
  for (int i = 0; i < N; ++i) {
    printf("%d%c", s[i], (i == N - 1) ? '\n' : ' ');
  }
  return 0;
}
