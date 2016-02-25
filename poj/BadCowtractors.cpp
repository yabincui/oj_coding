#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

int N, M;

struct Path {
  int a, b, c;
} paths[20000];

int set[1000];

bool comparePath(const Path& p1, const Path& p2) {
  return p1.c > p2.c;
}

int findRoot(int p) {
  int root = p;
  while (set[root] != -1) {
    root = set[root];
  }
  while (p != root) {
    int t = set[p];
    set[p] = root;
    p = t;
  }
  return root;
}

int getMaxCost() {
  memset(set, -1, sizeof(set));
  int total_cost = 0;
  sort(paths, &paths[M], comparePath);
  for (int i = 0; i < M; ++i) {
    int root1 = findRoot(paths[i].a);
    int root2 = findRoot(paths[i].b);
    if (root1 != root2) {
      total_cost += paths[i].c;
      set[root1] = root2;
    }
  }
  int root = findRoot(0);
  for (int i = 1; i < N; ++i) {
    if (root != findRoot(i)) {
      return -1;
    }
  }
  return total_cost;
}

int main() {
  freopen("BadCowtractors.in", "r", stdin);
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; ++i) {
    scanf("%d%d%d", &paths[i].a, &paths[i].b, &paths[i].c);
    paths[i].a--;
    paths[i].b--;
  }
  int result = getMaxCost();
  printf("%d\n", result);
  return 0;
}
