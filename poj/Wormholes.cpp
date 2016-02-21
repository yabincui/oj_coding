#include <stdio.h>
#include <string.h>

#include <algorithm>
using namespace std;

int N, M, W;
int dist[500][500];

struct Path {
  int a, b, d;
} path[5200];

#define INF 100000000

bool isReachable() {
  // Go N steps, and see if there is negative dist[i][i].
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      dist[i][j] = INF;
    }
    dist[i][i] = 0;
  }
  for (int step = 0; step < N; ++step) {
    for (int i = 0; i < 2 * M + W; ++i) {
      for (int j = 0; j < N; ++j) {
        dist[j][path[i].b] = min(dist[j][path[i].b], dist[j][path[i].a] + path[i].d);
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    if (dist[i][i] < 0) {
      return true;
    }
  }
  return false;
}

bool isReachable2() {
  // Using flood.
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      dist[i][j] = INF;
    }
    dist[i][i] = 0;
  }
  for (int i = 0; i < 2 * M + W; ++i) {
    dist[path[i].a][path[i].b] = min(dist[path[i].a][path[i].b], path[i].d);
  }
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (k == i || k == j) {
          continue;
        }
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
      if (dist[i][i] < 0) {
        return true;
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    if (dist[i][i] < 0) {
      return true;
    }
  }
  return false;
}

bool isReachable3() {
  // Using bellman ford.
  int d[N];
  memset(d, 0, sizeof(d));
  for (int step = 0; step < N; ++step) {
    bool change = false;
    for (int i = 0; i < 2 * M + W; ++i) {
      if (d[path[i].b] > d[path[i].a] + path[i].d) {
        d[path[i].b] = d[path[i].a] + path[i].d;
        change = true;
      }
    }
    if (!change) {
      return false;
    }
  }
  bool change = false;
  for (int i = 0; i < 2 * M + W; ++i) {
    if (d[path[i].b] > d[path[i].a] + path[i].d) {
      change = true;
      break;
    }
  }
  return change;
}

int main() {
  freopen("Wormholes.in", "r", stdin);
  int F;
  scanf("%d", &F);
  while (F-- > 0) {
    scanf("%d%d%d", &N, &M, &W);
    int k = 0;
    for (int i = 0; i < M + W; ++i) {
      int a, b, d;
      scanf("%d%d%d", &a, &b, &d);
      a--;
      b--;
      if (i >= M) {
        d = -d;
      }
      path[k].a = a;
      path[k].b = b;
      path[k].d = d;
      k++;
      if (i < M) {
        path[k].a = b;
        path[k].b = a;
        path[k].d = d;
        k++;
      }
    }
    bool result = isReachable3();
    printf("%s\n", result ? "YES" : "NO");
  }
  return 0;
}
