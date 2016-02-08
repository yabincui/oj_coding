#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int dist;
  int other;

  Edge(int dist, int other) {
    this->dist = dist;
    this->other = other;
  }
};

struct Node {
  vector<Edge> edges;
};

vector<Node> nodes;

struct Point {
  int node;
  int relation;
  
  Point(int node, int relation) {
    this->node = node;
    this->relation = relation;
  }
};

struct PointComparator {
  bool operator()(const Point& p1, const Point& p2) {
    return p1.relation < p2.relation;
  }
};

int findMinCostPrime() {
  vector<bool> visited(nodes.size(), false);
  vector<int> relations(nodes.size(), 0);
  priority_queue<Point, vector<Point>, PointComparator> queue;
  for (int i = 0; i < nodes.size(); ++i) {
    queue.push(Point(i, 0));
  }
  int count = 0;
  int cost = 0;
  while (!queue.empty()) {
    Point p = queue.top();
    queue.pop();
    if (visited[p.node]) {
      continue;
    }
    visited[p.node] = true;
    cost += 10000 - p.relation;
    if (++count == nodes.size()) {
      break;
    }
    for (size_t i = 0; i < nodes[p.node].edges.size(); ++i) {
      Edge& edge = nodes[p.node].edges[i];
      if (!visited[edge.other] && relations[edge.other] < edge.dist) {
        relations[edge.other] = edge.dist;
        queue.push(Point(edge.other, edge.dist));
      }
    }
  }
  return cost;
}

int findMinCostPrime2() {
  vector<bool> visited(nodes.size(), false);
  vector<int> relations(nodes.size(), 0);
  priority_queue<Point, vector<Point>, PointComparator> queue;
  int count = 0;
  int cost = 0;
  while (true) {
    if (queue.empty()) {
      for (size_t i = 0; i < nodes.size(); ++i) {
        if (!visited[i]) {
          queue.push(Point(i, 0));
          break;
        }
      }
    }
    Point p = queue.top();
    queue.pop();
    if (visited[p.node]) {
      continue;
    }
    visited[p.node] = true;
    cost += 10000 - p.relation;
    if (++count == nodes.size()) {
      break;
    }
    for (size_t i = 0; i < nodes[p.node].edges.size(); ++i) {
      Edge& edge = nodes[p.node].edges[i];
      if (!visited[edge.other] && relations[edge.other] < edge.dist) {
        relations[edge.other] = edge.dist;
        queue.push(Point(edge.other, edge.dist));
      }
    }
  }
  return cost;
}

struct Point2 {
  int node1;
  int node2;
  int relation;

  Point2(int node1, int node2, int relation) {
    this->node1 = node1;
    this->node2 = node2;
    this->relation = relation;
  }

  Point2() {
  }
};

struct Point2Comparator {
  bool operator()(const Point2& p1, const Point2& p2) {
    return p1.relation < p2.relation;
  }
};

vector<int> union_set;

int findRoot(int p) {
  if (union_set[p] == -1) {
    return p;
  }
  return union_set[p] = findRoot(union_set[p]);
}

bool compPoint2(const Point2& p1, const Point2& p2) {
  return p1.relation > p2.relation;
}

int findMinCostKruskal2() {
  union_set.clear();
  union_set.resize(nodes.size(), -1);
  vector<Point2> v;
  for (size_t i = 0; i < nodes.size(); ++i) {
    for (size_t j = 0; j < nodes[i].edges.size(); ++j) {
      Edge& edge = nodes[i].edges[j];
      if (edge.other <= i) {
        continue;
      }
      v.push_back(Point2(i, edge.other, edge.dist));
    }
  }
  sort(v.begin(), v.end(), compPoint2);
  int cost = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    Point2& p = v[i];
    int root1 = findRoot(p.node1);
    int root2 = findRoot(p.node2);
    if (root1 != root2) {
      cost += 10000 - p.relation;
      union_set[root1] = root2;
    }
  }
  for (size_t i = 0; i < union_set.size(); ++i) {
    if (union_set[i] == -1) {
      cost += 10000;
    }
  }
  return cost;
}

int findMinCostKruskal() {
  union_set.clear();
  union_set.resize(nodes.size(), -1);
  priority_queue<Point2, vector<Point2>, Point2Comparator> queue;
  for (size_t i = 0; i < nodes.size(); ++i) {
    for (size_t j = 0; j < nodes[i].edges.size(); ++j) {
      Edge& edge = nodes[i].edges[j];
      if (edge.other <= i) {
        continue;
      }
      queue.push(Point2(i, edge.other, edge.dist));
    }
  }
  int cost = 0;
  while (!queue.empty()) {
    Point2 p = queue.top();
    queue.pop();
    int root1 = findRoot(p.node1);
    int root2 = findRoot(p.node2);
    if (root1 != root2) {
      cost += 10000 - p.relation;
      union_set[root1] = root2;
    }
  }
  for (size_t i = 0; i < union_set.size(); ++i) {
    if (union_set[i] == -1) {
      cost += 10000;
    }
  }
  return cost;
}

int main1() {
  freopen("Conscription.in", "r", stdin);
  int test_cases;
  scanf("%d", &test_cases);
  for (int test_case = 1; test_case <= test_cases; ++test_case) {
    int N, M, R;
    scanf("%d%d%d", &N, &M, &R);
    nodes.clear();
    nodes.resize(N + M);
    for (int i = 0; i < R; ++i) {
      int x, y, d;
      scanf("%d%d%d", &x, &y, &d);
      nodes[x].edges.push_back(Edge(d, y + N));
      nodes[y+N].edges.push_back(Edge(d, x));
    }
    int result = findMinCostKruskal2();
    printf("%d\n", result);
  }
  return 0;
}

Point2 v[50001];
int union_set2[20001];
int N, M, R;

int findRoot2(int p) {
  if (union_set2[p] == -1) {
    return p;
  }
  return union_set2[p] = findRoot2(union_set2[p]);
}

int findMinCostKruskal3() {
  memset(union_set2, -1, sizeof(union_set2));
  sort(&v[0], &v[R], compPoint2);
  int cost = 0;
  for (size_t i = 0; i < R; ++i) {
    Point2& p = v[i];
    int root1 = findRoot2(p.node1);
    int root2 = findRoot2(p.node2);
    if (root1 != root2) {
      cost += 10000 - p.relation;
      union_set2[root1] = root2;
    }
  }
  for (size_t i = 0; i < N + M; ++i) {
    if (union_set2[i] == -1) {
      cost += 10000;
    }
  }
  return cost;
}



int main() {
  freopen("Conscription.in", "r", stdin);
  int test_cases;
  scanf("%d", &test_cases);
  for (int test_case = 1; test_case <= test_cases; ++test_case) {
    scanf("%d%d%d", &N, &M, &R);
    for (int i = 0; i < R; ++i) {
      scanf("%d%d%d", &v[i].node1, &v[i].node2, &v[i].relation);
      v[i].node2 += N;
    }
    int result = findMinCostKruskal3();
    printf("%d\n", result);
  }
  return 0;
}
