#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int N;
int S[350];
int T[350];

int main() {
  freopen("CowBowling.in", "r", stdin);
  scanf("%d", &N);
  memset(S, 0, sizeof(S));
  memset(T, 0, sizeof(T));
  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j < i; ++j) {
      scanf("%d", &T[j]);
      int add = 0;
      if (j > 0) {
        add = max(add, S[j - 1]);
      }
      if (j < i - 1) {
        add = max(add, S[j]);
      }
      T[j] += add;
    }
    memcpy(S, T, sizeof(S));
  }
  int result = 0;
  for (int i = 0; i < N; ++i) {
    result = max(result, S[i]);
  }
  printf("%d\n", result);
  return 0;
}
