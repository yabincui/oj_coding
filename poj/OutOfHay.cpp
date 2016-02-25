#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

int N, M;

int set[2000];

struct Path {
  int a, b, l;
} path[10000];

bool comparePath(const Path& p1, const Path& p2) {
  return p1.l < p2.l;
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

int getMinLength() {
  sort(path, &path[M], comparePath);
  memset(set, -1, sizeof(set));
  int max_length = 0;
  for (int i = 0; i < M; ++i) {
    int root1 = findRoot(path[i].a);
    int root2 = findRoot(path[i].b);
    if (root1 != root2) {
      set[root1] = root2;
      max_length = path[i].l;
    }
  }
  return max_length;
}

int main() {
  freopen("OutOfHay.in", "r", stdin);
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; ++i) {
    scanf("%d%d%d", &path[i].a, &path[i].b, &path[i].l);
    path[i].a--;
    path[i].b--;
  }
  int result = getMinLength();
  printf("%d\n", result);
  return 0;
}
