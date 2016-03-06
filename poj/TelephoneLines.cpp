#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <vector>
using namespace std;

int N, P, K;

struct Node {
  int a, b, l;
} nodes[10000];

struct Vetex {
  vector<int> costs;
  vector<int> neighbors;
} vertexes[1001];

bool isOk(int limit) {
  for (int i = 1; i <= N; ++i) {
    vertexes[i].costs.clear();
    vertexes[i].neighbors.clear();
  }
  for (int i = 0; i < P; ++i) {
    int cost = (nodes[i].l <= limit ? 0 : 1);
    int a = nodes[i].a;
    int b = nodes[i].b;
    //printf("connect [%d, %d] %d\n", a, b, cost);
    vertexes[a].costs.push_back(cost);
    vertexes[a].neighbors.push_back(b);
    vertexes[b].costs.push_back(cost);
    vertexes[b].neighbors.push_back(a);
  }
  bool visited[1001];
  int dist[1001];
  memset(visited, false, sizeof(visited));
  memset(dist, -1, sizeof(dist));
  dist[1] = 0;
  while (true) {
    int k = -1;
    for (int i = 0; i < N; ++i) {
      if (!visited[i] && dist[i] != -1 && (k == -1 || dist[i] < dist[k])) {
        k = i;
      }
    }
    if (k == -1) {
      break;
    }
    visited[k] = true;
    for (int i = 0; i < vertexes[k].neighbors.size(); ++i) {
      int c = vertexes[k].costs[i] + dist[k];
      int next = vertexes[k].neighbors[i];
      if (!visited[next] && (dist[next] == -1 || dist[next] > c)) {
        dist[next] = c;
        //printf("dist[%d] = %d\n", next, c);
        if (next == N && dist[next] <= K) {
          //printf("isOk(%d) = true\n", limit);
          return true;
        }
      }
    }
  }
  //printf("isOk(%d) = false\n", limit);
  return false;
}

int getMinCost() {
  int low = 0;
  int high = 1000000;
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    if (isOk(mid)) {
      high = mid;
    } else {
      low = mid;
    }
  }
  int length = -1;
  if (isOk(low)) {
    length = low;
  } else if (isOk(high)) {
    length = high;
  }
  if (length != -1 && length <= K) {
    length = 0;
  }
  return length;
}

int main() {
  freopen("TelephoneLines.in", "r", stdin);
  scanf("%d%d%d", &N, &P, &K);
  for (int i = 0; i < P; ++i) {
    scanf("%d%d%d", &nodes[i].a, &nodes[i].b, &nodes[i].l);
  }
  int result = getMinCost();
  printf("%d\n", result);
  return 0;
}
