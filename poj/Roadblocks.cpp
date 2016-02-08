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

const int INF = INT_MAX;

struct Dist {
  int first;
  int second;

  Dist(int first = INF, int second = INF) {
    this->first = first;
    this->second = second;
  }
};

struct Point {
  int index;
  int dist;
  Point(int index = -1, int dist = INF) {
    this->index = index;
    this->dist = dist;
  }
};

struct PointComparator {
  bool operator()(const Point& p1, const Point& p2) {
    return p1.dist > p2.dist;
  }
};

int N;
vector<Node> nodes;

int getSecondShortestPathLength() {
  vector<Dist> v(N + 1);
  v[0].first = 0;
  priority_queue<Point, vector<Point>, PointComparator> queue;
  queue.push(Point(1, 0));
  while (!queue.empty()) {
    Point p = queue.top();
    queue.pop();
    if (p.index == N && p.dist == v[N].second) {
      break;
    }
    if (p.dist > v[p.index].second) {
      continue;
    }
    for (size_t i = 0; i < nodes[p.index].edges.size(); ++i) {
      Edge& edge = nodes[p.index].edges[i];
      int d = p.dist + edge.dist;
      if (d < v[edge.other].first) {
        v[edge.other].second = v[edge.other].first;
        v[edge.other].first = d;
        queue.push(Point(edge.other, d));
      } else if (d < v[edge.other].second) {
        v[edge.other].second = d;
        queue.push(Point(edge.other, d));
      }
    }
  }
  return v[N].second;
}

int main() {
  freopen("Roadblocks.in", "r", stdin);
  int R;
  scanf("%d%d", &N, &R);
  nodes.resize(N + 1);
  for (int i = 0; i < R; ++i) {
    int A, B, D;
    scanf("%d%d%d", &A, &B, &D);
    nodes[A].edges.push_back(Edge(D, B));
    nodes[B].edges.push_back(Edge(D, A));
  }
  int result = getSecondShortestPathLength();
  printf("%d\n", result);
  return 0;
}
