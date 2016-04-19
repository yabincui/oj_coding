// POJ 1769
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
using namespace std;

int N, M;
struct Sort {
  int start, end;
} s[500000];

// Using dynamic programming. Time limit exceeded.
// dp[i] is the min count to let min value reaching i.
int dp[50001];
void solve() {
  memset(dp, -1, sizeof(dp));
  dp[0] = dp[1] = 0;
  for (int i = 0; i < M; ++i) {
    int min_prev = INT_MAX;
    for (int j = s[i].start; j < s[i].end; ++j) {
      if (dp[j] != -1) {
        min_prev = min(min_prev, dp[j]);
      }
    }
    if (min_prev != INT_MAX) {
      if (dp[s[i].end] == -1 || dp[s[i].end] > min_prev + 1) {
        dp[s[i].end] = min_prev + 1;
      }
    }
  }
  printf("%d\n", dp[N]);
}

// Using segment tree.
int seg_tree[1 << 18];

void UpdateSmallerValue(int root, int l, int r, int target, int value) {
  while (l != r) {
    if (seg_tree[root] > value) {
      seg_tree[root] = value;
    }
    int m = (l + r) / 2;
    if (target <= m) {
      root = root * 2 + 1;
      r = m;
    } else {
      root = root * 2 + 2;
      l = m + 1;
    }
  }
  if (seg_tree[root] > value) {
    seg_tree[root] = value;
  }
}

int GetMin(int root, int l, int r, int begin, int end) {
  if (l == r) {
    if (l >= begin && r <= end) {
      return seg_tree[root];
    }
    return INT_MAX;
  }
  if (l >= begin && r <= end) {
    return seg_tree[root];
  }
  if (l > end || r < begin) {
    return INT_MAX;
  }
  int m = (l + r) / 2;
  int a = GetMin(root * 2 + 1, l, m, begin, end);
  int b = GetMin(root * 2 + 2, m + 1, r, begin, end);
  return min(a, b);
}

void solve2() {
  for (int i = 0; i < (1 << 18); ++i) {
    seg_tree[i] = INT_MAX;
  }
  int p = 1;
  while (p < N) {
    p *= 2;
  }
  UpdateSmallerValue(0, 0, p - 1, 0, 0);
  for (int i = 0; i < M; ++i) {
    int min_value = GetMin(0, 0, p - 1, s[i].start - 1, s[i].end - 2);
    if (min_value != INT_MAX) {
      UpdateSmallerValue(0, 0, p - 1, s[i].end - 1, min_value + 1);
    }
  }
  int result = GetMin(0, 0, p - 1, N - 1, N - 1);
  printf("%d\n", result);
}

int main() {
  freopen("MinimizingMaximizer.in", "r", stdin);
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; ++i) {
    scanf("%d%d", &s[i].start, &s[i].end);
  }
  solve2();
  return 0;
}
