// POJ 2914
#include <stdint.h>

#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

#define MY_INT64_MAX    0x7FFFFFFFFFFFFFFFLL

using namespace std;

int N, M;

struct Edge {
  int to;
  int64_t cap;
  int rev;
};

vector<Edge> nodes[500];

void addEdge(int a, int b, int cap) {
  int a_index = nodes[a].size();
  int b_index = nodes[b].size();
  Edge e;
  e.to = b;
  e.cap = cap;
  e.rev = b_index;
  nodes[a].push_back(e);
  e.to = a;
  e.rev = a_index;
  nodes[b].push_back(e);
}

int level[500];
int iter[500];
vector<Edge> aug_nodes[500];

void bfsLevel(int source) {
  memset(level, -1, sizeof(level));
  level[source] = 0;
  queue<int> q;
  q.push(source);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (int i = 0; i < aug_nodes[cur].size(); ++i) {
      Edge& e = aug_nodes[cur][i];
      if (level[e.to] < 0 && e.cap > 0) {
        level[e.to] = level[cur] + 1;
        q.push(e.to);
      }
    }
  }
}

int64_t dfsAugPathByLevel(int source, int target, int64_t cap_limit) {
  if (source == target) {
    return cap_limit;
  }
  for (int& i = iter[source]; i < aug_nodes[source].size(); ++i) {
    Edge& e = aug_nodes[source][i];
    if (e.cap > 0 && level[e.to] > level[source]) {
      int64_t used = dfsAugPathByLevel(e.to, target, min(cap_limit, e.cap));
      if (used > 0) {
        e.cap -= used;
        aug_nodes[e.to][e.rev].cap += used;
        return used;
      }
    }
  }
  return 0;
}

int64_t getMaxFlow(int source, int target) {
  for (int i = 0; i < N; ++i) {
    aug_nodes[i] = nodes[i];
  }
  int64_t flow = 0;
  while (true) {
    bfsLevel(source);
    if (level[target] < 0) {
      break;
    }
    memset(iter, 0, sizeof(iter));
    int64_t f;
    while ((f = dfsAugPathByLevel(source, target, INT_MAX)) > 0) {
      flow += f;
    }
  }
  return flow;
}

bool connected() {
  for (int i = 0; i < N; ++i) {
    aug_nodes[i] = nodes[i];
  }
  bfsLevel(0);
  for (int i = 0; i < N; ++i) {
    if (level[i] == -1) {
      //printf("level[%d] = %d\n", i, level[i]);
      return false;
    }
  }
  return true;
}

// getMinimum Cut by BFS + DFS
int64_t getMinCut() {
  if (!connected()) {
    //printf("not connected\n");
    return 0;
  }
  int source = 0;
  int64_t result = -1;
  for (int target = 1; target < N; ++target) {
    int64_t max_flow = getMaxFlow(source, target);
    if (result == -1 || result > max_flow) {
      result = max_flow;
    }
  }
  return result;
}

int neighbor[500][500];
bool visited[500];
int64_t w[500];
int v[500];

// getMinimum Cut by Stoer Wagner.
int64_t getMinCutStoerWagner() {
  if (!connected()) {
    //printf("not connected\n");
    return 0;
  }
  memset(neighbor, 0, sizeof(neighbor));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < nodes[i].size(); ++j) {
      neighbor[i][nodes[i][j].to] += nodes[i][j].cap;
    }
  }
  for (int i = 0; i < N; ++i) {
    v[i] = i;
  }
  int64_t min_cut = MY_INT64_MAX;
  int n = N;
  while (n > 1) {
    memset(w, 0, sizeof(w));
    memset(visited, false, sizeof(visited));
    int prev = 0;
    for (int i = 1; i < n; ++i) {
      int k = -1;
      for (int j = 1; j < n; ++j) {
        if (!visited[j]) {
          w[v[j]] += neighbor[v[prev]][v[j]];
          if (k == -1 || w[v[j]] > w[v[k]]) {
            k = j;
          }
        }
      }
      visited[k] = true;
      if (i == n - 1) {
        int s = v[prev];
        int t = v[k];
        //printf("prev = %d, k = %d, s = %d, t = %d, w[t] = %d\n",
        //    prev, k, s, t, w[t]);
        min_cut = min(min_cut, w[t]);
        for (int j = 0; j < n; ++j) {
          neighbor[s][v[j]] += neighbor[t][v[j]];
          neighbor[v[j]][s] += neighbor[v[j]][t];
        }
        v[k] = v[--n];
      }
      prev = k;
    }
  }
  return min_cut;
}

int main() {
  freopen("MinimumCut.in", "r", stdin);
  while (scanf("%d%d", &N, &M) == 2 && N != 0) {
    for (int i = 0; i < N; ++i) {
      nodes[i].clear();
    }
    for (int i = 0; i < M; ++i) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      addEdge(a, b, c);
    } 
    int64_t min_cut = getMinCutStoerWagner();
    printf("%lld\n", min_cut);
  }
  return 0;
}
