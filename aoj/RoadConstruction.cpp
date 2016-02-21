#include <stdio.h>
#include <string.h>

#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int other;
  int d;
  int c;

  Edge(int other, int d, int c) {
    this->other = other;
    this->d = d;
    this->c = c;
  }
};

struct Node {
  vector<Edge> edges;
} nodes[10000];

int N, M;

struct Pos {
  int id;
  int dist;
  int cost;

  Pos(int id, int dist, int cost) {
    this->id = id;
    this->dist = dist;
    this->cost = cost;
  }
};

bool visited[10000];
int dist[10000];
int cost[10000];

typedef bool (*compFuncType)(const Pos&, const Pos&);

bool comparePos(const Pos& p1, const Pos& p2) {
  if (p1.dist != p2.dist) {
    return p1.dist > p2.dist;
  }
  return p1.cost > p2.cost;
}

int getMinCost() {
  memset(visited, false, sizeof(visited));
  memset(dist, -1, sizeof(dist));
  dist[0] = 0;
  memset(cost, -1, sizeof(cost));
  cost[0] = 0;
  priority_queue<Pos, vector<Pos>, compFuncType> q(comparePos);
  q.push(Pos(0, 0, 0));
  int total_cost = 0;
  while (!q.empty()) {
    Pos p = q.top(); q.pop();
    if (visited[p.id]) {
      continue;
    }
    visited[p.id] = true;
    total_cost += p.cost;
    //printf("connect %d, add cost %d\n", p.id, p.cost);
    for (size_t i = 0; i < nodes[p.id].edges.size(); ++i) {
      Edge& edge = nodes[p.id].edges[i];
      if (!visited[edge.other]) {
        int d = dist[p.id] + edge.d;
        int c = edge.c;
        if (dist[edge.other] == -1 || dist[edge.other] > d ||
            (dist[edge.other] == d && cost[edge.other] > c)) {
          dist[edge.other] = d;
          cost[edge.other] = c;
          q.push(Pos(edge.other, d, c));
        }
      }
    }
  }
  return total_cost;
}

int main() {
  freopen("RoadConstruction.in", "r", stdin);
  while (scanf("%d%d", &N, &M) == 2 && !(N == 0 && M == 0)) {
    for (int i = 0; i < N; ++i) {
      nodes[i].edges.clear();
    }
    for (int i = 0; i < M; ++i) {
      int u, v, d, c;
      scanf("%d%d%d%d", &u, &v, &d, &c);
      u--;
      v--;
      nodes[u].edges.push_back(Edge(v, d, c));
      nodes[v].edges.push_back(Edge(u, d, c));
    }
    int result = getMinCost();
    printf("%d\n", result);
  }
  return 0;
}
