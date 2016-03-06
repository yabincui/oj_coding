#include <stdio.h>

#include <algorithm>
#include <cmath>
using namespace std;

int N, K;

struct Node {
  int a, b;
  double comp;
} nodes[1000];

bool compNode(const Node& n1, const Node& n2) {
  return n1.comp > n2.comp;
}

bool isOk(double c) {
  for (int i = 0; i < N; ++i) {
    nodes[i].comp = nodes[i].a - nodes[i].b * c;
  }
  sort(nodes, nodes + N, compNode);
  long long sum_a = 0;
  long long sum_b = 0;
  for (int i = 0; i < N - K; ++i) {
    sum_a += nodes[i].a;
    sum_b += nodes[i].b;
  }
  return (double)sum_a / sum_b >= c;
}

int getMax() {
  double low = 0;
  double high = 1.0;
  //while (high - low > 1e-6) {
  for (int i = 0; i < 100; ++i) {
    double mid = (low + high) / 2.0;
    if (isOk(mid)) {
      low = mid;
    } else {
      high = mid;
    }
  }
  return (int)round(high * 100);
}

int main() {
  freopen("DroppingTests.in", "r", stdin);
  while (scanf("%d%d", &N, &K) == 2 && !(N == 0 && K == 0)) {
    for (int i = 0; i < N; ++i) {
      scanf("%d", &nodes[i].a);
    }
    for (int i = 0; i < N; ++i) {
      scanf("%d", &nodes[i].b);
    }
    int result = getMax();
    printf("%d\n", result);
  }
  return 0;
}
