#include <stdio.h>
#include <string.h>

int N, M;
int set[200001];

const int REV_BASE = 100000;

int findRoot(int a) {
  int root = a;
  while (set[root] != -1) {
    root = set[root];
  }
  while (a != root) {
    int p = set[a];
    set[a] = root;
    a = p;
  }
  return root;
}

void unionSet(int a, int b) {
  int root1 = findRoot(a);
  int root2 = findRoot(b);
  if (root1 != root2) {
    set[root1] = root2;
  }
}

int main() {
  freopen("FindThemCatchThem.in", "r", stdin);
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; ++t) {
    memset(set, -1, sizeof(set));
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
      char s[10];
      int a, b;
      scanf("%s%d%d", s, &a, &b);
      if (s[0] == 'D') {
        unionSet(a, b + REV_BASE);
        unionSet(a + REV_BASE, b);
      } else if (s[0] == 'A') {
        if (findRoot(a) == findRoot(b)) {
          printf("In the same gang.\n");
        } else if (findRoot(a) == findRoot(b + REV_BASE)) {
          printf("In different gangs.\n");
        } else {
          printf("Not sure yet.\n");
        }
      }
    }
  }

  return 0;
}
