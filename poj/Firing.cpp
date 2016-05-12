// POJ 2987
// 最大闭合子图: 算法合集之《最小割模型在信息学竞赛中的应用》.pdf
// I know why the result has the maximum profit (of a subgraph), but I don't know why it has minimum
// nodes in the subgraph.


#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <climits>
#include <queue>
#include <vector>
using namespace std;

struct Edge {
  int toNode;
  int64_t cap;
  int reverseEdge;
};

struct Node {
  vector<Edge> edges;
} nodes[5002];

int source = 5000;
int target = 5001;

int N, M;

bool visited[5002];

#define INF INT_MAX

void addEdge(int from, int to, int64_t cap) {
  int a_index = nodes[from].edges.size();
  int b_index = nodes[to].edges.size();
  Edge edge;
  edge.toNode = to;
  edge.cap = cap;
  edge.reverseEdge = b_index;
  nodes[from].edges.push_back(edge);
  edge.toNode = from;
  edge.cap = 0;
  edge.reverseEdge = a_index;
  nodes[to].edges.push_back(edge);
}

int64_t dfsFindAugPath(int cur, int64_t cap_limit) {
  if (cur == target) {
    return cap_limit;
  }
  visited[cur] = true;
  for (int i = 0; i < nodes[cur].edges.size(); ++i) {
    Edge& edge = nodes[cur].edges[i];
    int next = edge.toNode;
    if (visited[next] || edge.cap == 0) {
      continue;
    }
    int64_t ncap = min(cap_limit, edge.cap);
    int64_t used = dfsFindAugPath(next, ncap);
    if (used > 0) {
      edge.cap -= used;
      nodes[next].edges[edge.reverseEdge].cap += used;
      return used;
    }
  }
  return 0;
}

// Use DFS
int64_t getMaxFlow() {
  int64_t flow = 0;
  while (true) {
    memset(visited, false, sizeof(visited));
    int64_t add = dfsFindAugPath(source, INF);
    if (add == 0) {
      break;
    }
    flow += add;
  }
  return flow;
}

int level[5002];
int iter[5002];

void bfsLevel() {
  memset(level, -1, sizeof(level));
  level[source] = 0;
  queue<int> q;
  q.push(source);
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (int i = 0; i < nodes[node].edges.size(); ++i) {
      Edge& edge = nodes[node].edges[i];
      if (level[edge.toNode] < 0 && edge.cap > 0) {
        level[edge.toNode] = level[node] + 1;
        q.push(edge.toNode);
      }
    }
  }
}

int dfsFindAugPathByLevel(int cur, int64_t cap_limit) {
  if (cur == target) {
    return cap_limit;
  }
  for (int& i = iter[cur]; i < nodes[cur].edges.size(); ++i) {
    Edge& edge = nodes[cur].edges[i];
    int next = edge.toNode;
    if (edge.cap > 0 && level[cur] < level[next]) {
      int64_t ncap = min(cap_limit, edge.cap);
      int64_t used = dfsFindAugPathByLevel(next, ncap);
      if (used > 0) {
        edge.cap -= used;
        nodes[next].edges[edge.reverseEdge].cap += used;
        return used;
      }
    }
  }
  return 0;
}

// Use BFS + DFS
int64_t getMaxFlowBFS() {
  int64_t flow = 0;
  while (true) {
    bfsLevel();
    if (level[target] < 0) {
      break;
    }
    memset(iter, 0, sizeof(iter));
    int64_t f;
    while ((f = dfsFindAugPathByLevel(source, INF)) > 0) {
      flow += f;
    }
  }
  return flow;
}

int dfsFromSource() {
  memset(visited, false, sizeof(visited));
  queue<int> q;
  visited[target] = true;
  q.push(source);
  visited[source] = true;
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (int i = 0; i < nodes[node].edges.size(); ++i) {
      Edge& edge = nodes[node].edges[i];
      if (!visited[edge.toNode] && edge.cap > 0) {
        visited[edge.toNode] = true;
        q.push(edge.toNode);
      }
    }
  }
  int count = 0;
  for (int i = 0; i < source; ++i) {
    if (visited[i]) {
      count++;
    }
  }
  return count;
}

int main() {
  freopen("firing.in", "r", stdin);
  scanf("%d%d", &N, &M);
  int64_t sum = 0;
  for (int i = 0; i < N; ++i) {
    int value;
    scanf("%d", &value);
    if (value > 0) {
      addEdge(source, i, value);
      sum += value;
    } else if (value < 0) {
      addEdge(i, target, -value);
    }
  }
  for (int i = 0; i < M; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--;
    b--;
    addEdge(a, b, INF);
  }
  int64_t max_flow = getMaxFlowBFS();
  int64_t profit = sum - max_flow;
  int count = dfsFromSource();
  printf("%d %lld\n", count, profit);
  return 0;
}
