#include <stdio.h>

#include <algorithm>
using namespace std;

int N, K;

struct Node {
  int no;
  int v, w;
  double comp;
} nodes[100000];

int keep[100000];

bool compNode(const Node& n1, const Node& n2) {
  return n1.comp > n2.comp;
}

bool isOk(double c) {
  for (int i = 0; i < N; ++i) {
    nodes[i].comp = nodes[i].v - nodes[i].w * c;
  }
  sort(nodes, nodes + N, compNode);
  double sum_v = 0.0;
  double sum_w = 0.0;
  for (int i = 0; i < K; ++i) {
    sum_v += nodes[i].v;
    sum_w += nodes[i].w;
  }
  return sum_v / sum_w >= c;
}

void getMaxResult() {
  double low = 0.0;
  double high = 1000000;
  for (int i = 0; i < 100; ++i) {
    double mid = (low + high) / 2.0;
    if (isOk(mid)) {
      low = mid;
    } else {
      high = mid;
    }
  }
  for (int i = 0; i < K; ++i) {
    keep[i] = nodes[i].no;
  }
  sort(keep, keep + K);
}

int main() {
  freopen("KBest.in", "r", stdin);
  while (scanf("%d%d", &N, &K) == 2 && N != 0) {
    for (int i = 0; i < N; ++i) {
      scanf("%d%d", &nodes[i].v, &nodes[i].w);
      nodes[i].no = i + 1;
    }
    getMaxResult();
    for (int i = 0; i < K; ++i) {
      printf("%d%c", keep[i], (i == K - 1) ? '\n' : ' ');
    }
  }
  return 0;
}
