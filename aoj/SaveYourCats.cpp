#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>

using namespace std;

int N, M;

struct Edge {
  int na, nb;  // Edge connects node a, node b, index in nodes.
  double cost;
};


vector<Edge> edges;  // M

struct To {
  int dx;
  int dy;
  int place;
  int edge;
  int other_node;
};

struct Node {
  int x, y;
  vector<To> to;  // sorted edges.
};

vector<Node> nodes;  // N

unordered_map<int, int> node_pos_map;

bool compareEdge(const Edge& e1, const Edge& e2) {
  return e1.cost < e2.cost;
}

/*
places:

  6  7   0
 5 __| __  1
   4 |  2
     3
*/

int getPlace(int dx, int dy) {
  if (dx > 0) {
    if (dy > 0) {
      return 0;
    } else if (dy == 0) {
      return 1;
    } else {
      return 2;
    }
  } else if (dx == 0) {
    if (dy < 0) {
      return 3;
    } else {
      return 7;
    }
  } else {
    if (dy < 0) {
      return 4;
    } else if (dy == 0) {
      return 5;
    } else {
      return 6;
    }
  }
}

bool compareTo(const To& t1, const To& t2) {
  if (t1.place != t2.place) {
    return t1.place < t2.place;
  }
  double k1 = (double)t1.dy / t1.dx;
  double k2 = (double)t2.dy / t2.dx;
  return k1 > k2;
}

void constructTo() {
  for (int i = 0; i < M; ++i) {
    int a = edges[i].na;
    int b = edges[i].nb;
    To to;
    to.dx = nodes[b].x - nodes[a].x;
    to.dy = nodes[b].y - nodes[a].y;
    to.place = getPlace(to.dx, to.dy);
    to.edge = i;
    to.other_node = b;
    nodes[a].to.push_back(to);
    to.dx = -to.dx;
    to.dy = -to.dy;
    to.place = getPlace(to.dx, to.dy);
    to.other_node = a;
    nodes[b].to.push_back(to);
  }
  for (int i = 0; i < N; ++i) {
    sort(nodes[i].to.begin(), nodes[i].to.end(), compareTo);
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < nodes[i].to.size(); ++j) {
      int other = nodes[i].to[j].other_node;
      node_pos_map[(i << 16) | other] = j;
    }
  }
}

vector<int> set;  // used for union set, 2 * M

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
  //printf("unionSet(%d, %d)\n", p, q);
  int root1 = findRoot(p);
  int root2 = findRoot(q);
  if (root1 != root2) {
    set[root1] = root2;
  }
}

void visitAllSides() {
  vector<bool> visited(2 * M, false);
  for (int side = 0; side < 2 * M; ++side) {
    if (visited[side]) {
      continue;
    }
    int edge = side / 2;
    int start, prev, cur;
    if (side % 2 == 0) {
      start = prev = edges[edge].na;
      cur = edges[edge].nb;
    } else {
      start = prev = edges[edge].nb;
      cur = edges[edge].na;
    }
    int prev_side = side;
    while (!visited[prev_side]) {
      visited[prev_side] = true;
      int pos = node_pos_map[(cur << 16) | prev];
      int next_pos = pos - 1;
      if (next_pos == -1) {
        next_pos = nodes[cur].to.size() - 1;
      }
      const To& to = nodes[cur].to[next_pos];
      int next_edge = to.edge;
      int next_side = (cur == edges[next_edge].na) ? next_edge * 2 : next_edge * 2 + 1;
      unionSet(prev_side, next_side);
      prev = cur;
      cur = (cur == edges[next_edge].na) ? edges[next_edge].nb : edges[next_edge].na;
      prev_side = next_side;
    }
  }
}

double getMinLength() {
  sort(edges.begin(), edges.end(), compareEdge);
  constructTo();
  set.clear();
  set.resize(2 * M, -1);
  //printf("visitAllSides\n");
  visitAllSides();
  //printf("getMinLength\n");
  double total_length = 0.0;
  for (int i = 0; i < M; ++i) {
    int root1 = findRoot(i * 2);
    int root2 = findRoot(i * 2 + 1);
    if (root1 != root2) {
      //printf("union(%d, %d), cost %lf\n", i * 2, i * 2 + 1, edges[i].cost);
      total_length += edges[i].cost;
      set[root1] = root2;
    }
  }
  return total_length;
}

int main() {
  freopen("SaveYourCats.in", "r", stdin);
  while (scanf("%d%d", &N, &M) == 2 && !(N == 0 && M == 0)) {
    nodes.clear();
    nodes.resize(N);
    for (int i = 0; i < N; ++i) {
      scanf("%d%d", &nodes[i].x, &nodes[i].y);
    }
    edges.clear();
    edges.resize(M);
    for (int i = 0; i < M; ++i) {
      int a, b;
      scanf("%d%d", &a, &b);
      a--;
      b--;
      edges[i].na = a;
      edges[i].nb = b;
      edges[i].cost = sqrt((nodes[a].x - nodes[b].x) * (nodes[a].x - nodes[b].x) +
                           (nodes[a].y - nodes[b].y) * (nodes[a].y - nodes[b].y));
    }
    double result = getMinLength();
    printf("%f\n", result);
  }
  return 0;
}
