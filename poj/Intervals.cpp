// POJ 1201

#include <stdint.h>
#include <stdio.h>

#include <algorithm>
using namespace std;

int N;

struct Range {
  int a, b, c;
} ranges[50000];

bool compareRangeByB(const Range& r1, const Range& r2) {
  return r1.b < r2.b;
}

struct SegmentTreeNode {
  int element_value;
  int sum;
} seg_tree[1 << 18];

int getRangeSum(int root, int l, int r, int start, int end) {
  if (l == r) {
    if (l >= start && r <= end) {
      return seg_tree[root].sum;
    }
    return 0;
  }
  if (l >= start && r <= end) {
    return seg_tree[root].sum;
  }
  if (r < start || l > end) {
    return 0;
  }
  int m = (l + r) / 2;
  int left = root * 2 + 1;
  int right = root * 2 + 2;
  if (seg_tree[root].element_value != 0) {
    int t = seg_tree[root].element_value;
    seg_tree[root].element_value = 0;
    seg_tree[left].element_value = t;
    seg_tree[left].sum = t * (m - l + 1);
    seg_tree[right].element_value = t;
    seg_tree[right].sum = t * (r - m);
  }
  int result = getRangeSum(left, l, m, start, end);
  result += getRangeSum(right, m + 1, r, start, end);
  return result;
}

void setRangeValue(int root, int l, int r, int start, int end, int value) {
  if (l == r) {
    if (l >= start && l <= end) {
      seg_tree[root].element_value = value;
      seg_tree[root].sum = value;
    }
    return;
  }
  if (r < start || l > end) {
    return;
  }
  if (l >= start && r <= end) {
    seg_tree[root].element_value = value;
    seg_tree[root].sum = value * (r - l + 1);
    return;
  }
  int m = (l + r) / 2;
  int left = root * 2 + 1;
  int right = root * 2 + 2;
  if (seg_tree[root].element_value != 0) {
    int t = seg_tree[root].element_value;
    seg_tree[root].element_value = 0;
    seg_tree[left].element_value = t;
    seg_tree[left].sum = t * (m - l + 1);
    seg_tree[right].element_value = 0;
    seg_tree[right].sum = t * (r - m);
  }
  setRangeValue(left, l, m, start, end, value);
  setRangeValue(right, m + 1, r, start, end, value);
  seg_tree[root].sum = seg_tree[left].sum + seg_tree[right].sum;
}

void fillRange(int start, int end, int add_count, int p) {
  // Use greedy to fill as right side as possible.
  int low = start;
  int high = end - add_count + 1;
  //printf("start = %d, end = %d, add_count = %d, low = %d, high = %d\n",
  //        start, end, add_count, low, high);
  while (low < high) {
    int mid = (low + high) / 2;
    int sum = getRangeSum(0, 0, p - 1, mid, end);
    int slots = end - mid + 1;
    if (slots - sum == add_count) {
      //printf("slots = %d, sum = %d, add_count = %d, mid = %d\n", slots, sum, add_count, mid);
      low = high = mid;
      break;
    }
    if (slots - sum > add_count) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  //printf("set range value (%d, %d)\n", low, end);
  setRangeValue(0, 0, p - 1, low, end, 1);
}

// Use greedy + SegmentTree + binary search.
void solve() {
  sort(ranges, ranges + N, compareRangeByB);
  int p = 1;
  while (p <= 50000) {
    p *= 2;
  }
  int result = 0;
  for (int i = 0; i < N; ++i) {
    int a = ranges[i].a;
    int b = ranges[i].b;
    int c = ranges[i].c;
    int sum = getRangeSum(0, 0, p - 1, a, b);
    if (sum >= c) {
      continue;
    }
    fillRange(a, b, c - sum, p);
    result += c - sum;
    //printf("c = %d, sum = %d, result = %d\n", c, sum, result);
  }
  printf("%d\n", result);
}

int main() {
  freopen("Intervals.in", "r", stdin);
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d%d", &ranges[i].a, &ranges[i].b, &ranges[i].c);
  }
  solve();
  return 0;
}
