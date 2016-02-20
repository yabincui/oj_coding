#include <stdio.h>
#include <string.h>

int N, D;

struct Computer {
  int x, y;
} computers[1001];

bool ok[1001];
int set[1001];

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

void unionSet(int p, int q) {
  int root1 = findRoot(p);
  int root2 = findRoot(q);
  if (root1 != root2) {
    set[root1] = root2;
  }
}

void repair(int p) {
  if (ok[p]) {
    return;
  }
  ok[p] = true;
  for (int i = 0; i < N; ++i) {
    if (i == p || !ok[i]) {
      continue;
    }
    int dx = computers[i].x - computers[p].x;
    int dy = computers[i].y - computers[p].y;
    if (dx * dx + dy * dy <= D * D) {
      unionSet(i, p);
    }
  }
}

bool isConnected(int p, int q) {
  return (p == q) || (ok[p] && ok[q] && findRoot(p) == findRoot(q));
}

int main() {
  freopen("WirelessNetwork.in", "r", stdin);
  scanf("%d%d", &N, &D);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &computers[i].x, &computers[i].y);
  }
  memset(ok, false, sizeof(ok));
  memset(set, -1, sizeof(set));
  char op[10];
  while (scanf("%s", op) == 1) {
    int p, q;
    if (op[0] == 'O') {
      scanf("%d", &p);
      repair(p-1);
    } else if (op[0] == 'S') {
      scanf("%d%d", &p, &q);
      bool result = isConnected(p-1, q-1);
      printf("%s\n", result ? "SUCCESS" : "FAIL");
    }
  }
  return 0;
}
