#include <stdint.h>
#include <stdio.h>

#include <algorithm>
#include <cstdlib>
using namespace std;

int N, K;
int S[100000];

struct Node {
  int64_t value;
  int pos;
} sum[100001];

int64_t myabs(int64_t a) {
  return a < 0 ? -a : a;
}

bool compareNode(const Node& n1, const Node& n2) {
  return n1.value < n2.value;
}

int getLowerStart(int end, int64_t key) {
  int low = 0;
  int high = N;
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    int64_t value = sum[mid].value;
    if (value > key) {
      high = mid;
    } else {
      low = mid;
    }
  }
  int64_t min_diff;
  int result = -1;
  for (int i = max(0, low - 2); i <= min(high + 2, N); ++i) {
    int64_t diff = myabs(sum[i].value - key);
    if (i != end && (result == -1 || min_diff > diff)) {
      //printf("i = %d, end = %d\n", i, end);
      result = i;
      min_diff = diff;
    }
  }
  return result;
}

void getBest(int64_t sub_sum, int64_t* best_sum, int* best_start, int* best_end) {
  int64_t best_diff = -1;
  for (int end = 0; end <= N; ++end) {
    //printf("getLowerStart(%d, %lld) \n", end, sum[end].value - sub_sum);
    int start = getLowerStart(end, sum[end].value - sub_sum);
    //printf("getLowerStart(%d, %lld) = %d\n", end, sum[end].value - sub_sum, start);
    int64_t diff = myabs(sum[end].value - sum[start].value - sub_sum);
    //printf("start.pos = %d, end.pos = %d, diff = %lld\n", sum[start].pos, sum[end].pos, diff);
    if (end == 0 || diff < best_diff) {
      best_diff = diff;
      *best_sum = myabs(sum[end].value - sum[start].value);
      *best_start = min(sum[end].pos, sum[start].pos) + 1;
      *best_end = max(sum[end].pos, sum[start].pos);
    }
  }
}

int main() {
  freopen("BoundFound.in", "r", stdin);
  while (scanf("%d%d", &N, &K) == 2 && !(N == 0 && K == 0)) {
    for (int i = 0; i < N; ++i) {
      scanf("%d", &S[i]);
    }
    sum[0].pos = 0;
    sum[0].value = 0;
    for (int i = 1; i <= N; ++i) {
      sum[i].pos = i;
      sum[i].value = sum[i - 1].value + S[i - 1];
    }
    sort(sum, sum + N + 1, compareNode);
    for (int i = 0; i <= N; ++i) {
      //printf("sum[%d].value = %lld, pos = %d\n", i, sum[i].value, sum[i].pos);
    }
    for (int i = 0; i < K; ++i) {
      int64_t target;
      scanf("%lld", &target);
      //printf("target = %lld\n", target);
      int64_t best;
      int start, end;
      getBest(target, &best, &start, &end);
      printf("%lld %d %d\n", best, start, end);
    }
  }
  return 0;
}
