// POJ 3713

#include <stdio.h>
#include <string.h>

#include <vector>
using namespace std;

int N, M;

vector<pair<int, int> > edges;

/*
struct Edge {
  int to;
  int cap;
  int reverse_index;
};

vector<Edge> nodes[1000];
bool used[1000];

void connectNode(int a, int b) {
  int a_index = nodes[a].size();
  int b_index = nodes[b].size();
  Edge edge;
  edge.to = b;
  edge.cap = 1;
  edge.reverse_index = b_index;
  nodes[a].push_back(edge);
  edge.to = a;
  edge.cap = 0;
  edge.reverse_index = a_index;
  nodes[b].push_back(edge);
}

void buildGraph() {
  for (int i = 0; i < N * 2; ++i) {
    nodes[i].clear();
  }
  for (int i = 0; i < edges.size(); ++i) {
    int a = edges[i].first;
    int b = edges[i].second;
    connectNode(a * 2 + 1, b * 2);
    connectNode(b * 2 + 1, a * 2);
  }
  for (int i = 0; i < N; ++i) {
    int a = i * 2;
    int b = i * 2 + 1;
    connectNode(a, b);
  }
}

bool findFlow(int start, int end) {
  if (start == end) {
    return true;
  }
  used[start] = true;
  for (int i = 0; i < nodes[start].size(); ++i) {
    Edge& edge = nodes[start][i];
    if (used[edge.to] || edge.cap == 0) {
      continue;
    }
    if (findFlow(edge.to, end)) {
      edge.cap--;
      nodes[edge.to][edge.reverse_index].cap++;
      return true;
    }
  }
  return false;
}

// assume it is transive, like A has three path to B, B has three path to C, then A has
// three path to C. But this is not true as you can't have all three path from A to C
// go through B.
// The three path can't share the same node, not the edge, so I need to split one node
// into an in-node and an out-node.
void solve_wrong() {
  for (int start = 0; start < N - 1; ++start) {
    int end = start + 1;
    int start_node = start * 2 + 1;
    int end_node = end * 2;
    buildGraph();
    for (int i = 0; i < 3; ++i) {
      memset(used, 0, sizeof(used));
      if (!findFlow(start_node, end_node)) {
        //printf("can't find path from %d to %d at %d\n", start, end, i);
        printf("NO\n");
        return;
      }
    }
  }
  printf("YES\n");
}

*/

enum State {
  NotAccessed,
  Accessing,
  Accessed,
};

struct Node {
  State state;
  int lowest_accessible;
  int depth;
  vector<int> neighbors;
} nodes[500];

bool has_cut_point;

void dfs(int current, int depth) {
  nodes[current].lowest_accessible = nodes[current].depth = depth;
  nodes[current].state = Accessing;
  int subtree_count = 0;
  for (int i = 0; i < nodes[current].neighbors.size(); ++i) {
    int next = nodes[current].neighbors[i];
    if (nodes[next].state == Accessed) {
      continue;
    } else if (nodes[next].state == Accessing) {
      nodes[current].lowest_accessible = min(nodes[current].lowest_accessible,
                                             nodes[next].depth);
    } else if (nodes[next].state == NotAccessed) {
      dfs(next, depth + 1);
      subtree_count++;
      if (depth != 0 && nodes[next].lowest_accessible >= nodes[current].depth) {
        has_cut_point = true;
      } else if (depth == 0 && subtree_count > 1) {
        has_cut_point = true;
      }
      nodes[current].lowest_accessible = min(nodes[current].lowest_accessible,
                                             nodes[next].lowest_accessible);
    }
  }
  nodes[current].state = Accessed;
}

bool connected() {
  vector<int> v;
  bool marked[N];
  memset(marked, false, sizeof(marked));
  v.push_back(0);
  marked[0] = true;
  for (int i = 0; i < v.size(); ++i) {
    int a = v[i];
    for (int j = 0; j < nodes[a].neighbors.size(); ++j) {
      int b = nodes[a].neighbors[j];
      if (!marked[b]) {
        marked[b] = true;
        v.push_back(b);
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    if (!marked[i]) {
      return false;
    }
  }
  return true;
}

// Remove a node, and see if there is a cut node in the graph.
void solve() {
  for (int i = 0; i < N; ++i) {
    nodes[i].neighbors.clear();
  }
  for (int i = 0; i < edges.size(); ++i) {
    nodes[edges[i].first].neighbors.push_back(edges[i].second);
    nodes[edges[i].second].neighbors.push_back(edges[i].first);
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      nodes[j].state = NotAccessed;
    }
    nodes[i].state = Accessed; // Delete i.
    int root = (i == 0) ? 1 : 0;
    has_cut_point = false;
    dfs(root, 0);
    if (has_cut_point) {
      printf("NO\n");
      return;
    }
    for (int j = 0; j < N; ++j) {
      if (nodes[j].state != Accessed) {
        printf("NO\n");
        return;
      }
    }
  }
  printf("YES\n");
}

bool hit[500][500];

int main() {
  freopen("TransferringSylla.in", "r", stdin);
  while (true) {
    if (scanf("%d%d", &N, &M) != 2 || N == 0) {
      break;
    }
    if (N <= 3) {
      while (true);
    }
    memset(hit, 0, sizeof(hit));
    edges.resize(M);
    for (int i = 0; i < M; ++i) {
      scanf("%d%d", &edges[i].first, &edges[i].second);
      int a = edges[i].first;
      int b = edges[i].second;
      if (hit[a][b]) {
        while (true);
      }
      hit[a][b] = hit[b][a] = true;
    }
    solve();
  }
  return 0;
}
