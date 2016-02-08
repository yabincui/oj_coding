#include <stdio.h>
#include <limits.h>

#include <algorithm>
using namespace std;

int N, ML, MD;

struct Edge {
  int a, b, d;
};

int dists[1002];
Edge likeEdges[10001];
Edge dislikeEdges[10001];

const int INF = INT_MAX;

int getMaxDist() {
  for (int i = 1; i <= N; ++i) {
    dists[i] = INF;
  }
  dists[1] = 0;
  for (int t = 0; t <= N; ++t) {
    for (int i = 1; i < N; ++i) {
      if (dists[i + 1] < dists[i]) {
        dists[i] = dists[i + 1];
      }
    }
    for (int i = 0; i < ML; ++i) {
      Edge& edge = likeEdges[i];
      if (dists[edge.a] != INF) {
        dists[edge.b] = min(dists[edge.b], dists[edge.a] + edge.d);
      }
    }
    for (int i = 0; i < MD; ++i) {
      Edge& edge = dislikeEdges[i];
      if (dists[edge.b] != INF) {
        dists[edge.a] = min(dists[edge.a], dists[edge.b] - edge.d);
      }
    }
  }
  if (dists[1] < 0) {
    return -1;
  }
  if (dists[N] == INF) {
    return -2;
  }
  return dists[N];
}

int main() {
  freopen("Layout.in", "r", stdin);
  scanf("%d%d%d", &N, &ML, &MD);
  for (int i = 0; i < ML; ++i) {
    scanf("%d%d%d", &likeEdges[i].a, &likeEdges[i].b, &likeEdges[i].d);
  }
  for (int i = 0; i < MD; ++i) {
    scanf("%d%d%d", &dislikeEdges[i].a, &dislikeEdges[i].b, &dislikeEdges[i].d);
  }
  int result = getMaxDist();
  printf("%d\n", result);
  return 0;
}
