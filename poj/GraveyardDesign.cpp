#include <stdint.h>
#include <stdio.h>

#include <vector>
#include <utility>
using namespace std;

int main() {
  freopen("GraveyardDesign.in", "r", stdin);
  int64_t N;
  scanf("%lld", &N);
  vector<int> start_v;
  vector<int> end_v;
  int start = 1, end = 0;
  int limit = 10000001;
  int64_t sum = 0;
  while (end <= limit) {
    while (sum < N && end <= limit) {
      sum += (int64_t)end * end;
      end++;
    }
    if (sum == N) {
      start_v.push_back(start);
      end_v.push_back(end);
    }
    sum -= (int64_t)start * start;
    start++;
  }
  printf("%zu\n", start_v.size());
  for (int i = 0; i < start_v.size(); ++i) {
    int start = start_v[i];
    int end = end_v[i];
    printf("%d", end - start);
    while (start != end) {
      printf(" %d", start++);
    }
    printf("\n");
  }
  return 0;
}
