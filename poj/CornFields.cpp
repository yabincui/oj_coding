// POJ 3254
#include <stdio.h>
#include <string.h>

#include <utility>
using namespace std;

int M, N;
int field[12][12];

int dp[2][1 << 12];

#define MOD 100000000

void solve() {
  int *cur = dp[0];
  int *next = dp[1];
  cur[0] = 1;
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      memset(next, 0, sizeof(dp[0]));
      for (int used = 0; used < (1 << N); ++used) {
        if (field[i][j] == 0 || (j > 0 && (used & (1 << (j - 1)))) ||
              (i > 0 && (used & (1 << j)))) {
          next[used & ~(1 << j)] = (next[used & ~(1 << j)] + cur[used]) % MOD; 
        } else {
          // can use or not use.
          next[used & ~(1 << j)] = (next[used & ~(1 << j)] + cur[used]) % MOD;
          next[used | (1 << j)] = (next[used | (1 << j)] + cur[used]) % MOD;
        }
      }
      swap(cur, next);
    }
  }
  int result = 0;
  for (int i = 0; i < (1 << N); ++i) {
    result = (result + cur[i]) % MOD;
  }
  printf("%d\n", result);
}

int main() {
  freopen("CornFields.in", "r", stdin);
  scanf("%d%d", &M, &N);
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &field[i][j]);
    }
  }
  solve();
  return 0;
}
