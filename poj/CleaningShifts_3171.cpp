// POJ 3171

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <climits>
using namespace std;

int N, M, E;

struct Cow {
  int T1, T2, S;
} cows[10000];

bool compareEnd(const Cow& c1, const Cow& c2) {
  return c1.T2 < c2.T2;
}

void shift() {
  E -= M - 1;
  for (int i = 0; i < N; ++i) {
    cows[i].T1 -= M - 1;
    cows[i].T2 -= M - 1;
  }
}

// Use combination of dynamic programming and segment tree.
uint64_t seg_tree[1 << 19];

void UpdateSmallValue(int root, int l, int r, int target, uint64_t value) {
  while (l != r) {
    if (seg_tree[root] > value) {
      seg_tree[root] = value;
    }
    int m = (l + r) / 2;
    if (target <= m) {
      r = m;
      root = root * 2 + 1;
    } else {
      l = m + 1;
      root = root * 2 + 2;
    }
  }
  if (seg_tree[root] > value) {
    seg_tree[root] = value;
  }
  //printf("seg_tree[%d] = %llu, value = %llu\n", root, seg_tree[root], value);
}

uint64_t GetMin(int root, int l, int r, int begin, int end) {
  if (l >= begin && r <= end) {
    return seg_tree[root];
  }
  if (l > end || r < begin) {
    return ULLONG_MAX;
  }
  int m = (l + r) / 2;
  return min(GetMin(root * 2 + 1, l, m, begin, end),
             GetMin(root * 2 + 2, m + 1, r, begin, end));
}

void solve() {
  shift();
  sort(cows, cows + N, compareEnd);
  memset(seg_tree, -1, sizeof(seg_tree));
  int p = 1;
  while (p <= E) {
    p *= 2;
  }
  UpdateSmallValue(0, 0, p - 1, 0, 0);
  for (int i = 0; i < N; ++i) {
    uint64_t min_value = GetMin(0, 0, p - 1, cows[i].T1 - 1, cows[i].T2 - 1);
    //printf("GetMin(%d, %d) = %llu\n", cows[i].T1 - 1, cows[i].T2 - 1, min_value);
    if (min_value != ULLONG_MAX) {
      UpdateSmallValue(0, 0, p - 1, cows[i].T2, min_value + cows[i].S);
    }
  }
  uint64_t result = GetMin(0, 0, p - 1, E, E);
  if (result == ULLONG_MAX) {
    printf("-1\n");
  } else {
    printf("%llu\n", result);
  }
}

int main() {
  freopen("CleaningShifts_3171.in", "r", stdin);
  scanf("%d%d%d", &N, &M, &E);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d%d", &cows[i].T1, &cows[i].T2, &cows[i].S);
  }
  solve();
  return 0;
}
