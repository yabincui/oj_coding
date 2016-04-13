// POJ 2441
#include <stdio.h>
#include <string.h>

#include <vector>
using namespace std;

int N, M;
vector<int> v[20];

int dp[2][1 << 20];

void solve() {
  if (N > M) {
    printf("0\n");
    return;
  }
  dp[0][(1 << M) - 1] = 1;
  int *cur = dp[0];
  int *next = dp[1];
  for (int i = 0; i < N; ++i) {
    memset(next, 0, sizeof(dp[0]));
    for (int j = 1; j < (1 << M); ++j) {
      for (int k = 0; k < v[i].size(); ++k) {
        int used = v[i][k];
        if (j & (1 << used)) {
          next[j & ~(1 << used)] += cur[j];
        }
      }
    }
    swap(cur, next);
  }
  int result = 0;
  for (int i = 0; i < (1 << M); ++i) {
    result += cur[i];
  }
  printf("%d\n", result);
}

int main() {
  freopen("ArrangeTheBulls.in", "r", stdin);
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; ++i) {
    int p;
    scanf("%d", &p);
    for (int j = 0; j < p; ++j) {
      int t;
      scanf("%d", &t);
      v[i].push_back(t - 1);
    }
  }
  solve();
  return 0;
}
