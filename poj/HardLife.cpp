// POJ 3155
// Maximum density subgraph
// Wrong Answer, but don't know why the last dfs works for h(g) ~= 0, so stops working on it.
//

#include <stdint.h>
#include <string.h>

#include <algorithm>
#include <cstdio>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

#define INF INT_MAX

int N, M;
vector<pair<int, int> > hard_v;

struct Edge {
  int to;
  double cap;
  int rev;
};

vector<Edge> nodes[1000 + 100 + 2];

int source = 1000 + 100;
int target = 1000 + 100 + 1;

int level[2000];
int iter[2000];

void bfsLevel() {
  memset(level, -1, sizeof(level));
  level[source] = 0;
  queue<int> q;
  q.push(source);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (int i = 0; i < nodes[cur].size(); ++i) {
      Edge& e = nodes[cur][i];
      if (e.cap > 0 && level[e.to] < 0) {
        level[e.to] = level[cur] + 1;
        q.push(e.to);
      }
    }
  }
}

double dfsAugPathByLevel(int cur, double cap_limit) {
  if (cur == target) {
    return cap_limit;
  }
  for (int& i = iter[cur]; i < nodes[cur].size(); ++i) {
    Edge& e = nodes[cur][i];
    if (e.cap > 0 && level[e.to] > level[cur]) {
      double used = dfsAugPathByLevel(e.to, min(cap_limit, e.cap));
      if (used != 0) {
        e.cap -= used;
        nodes[e.to][e.rev].cap += used;
        return used;
      }
    }
  }
  return 0;
}

double getMinCut() {
  double flow = 0;
  while (true) {
    bfsLevel();
    if (level[target] < 0) {
      break;
    }
    memset(iter, 0, sizeof(iter));
    double f;
    while ((f = dfsAugPathByLevel(source, INF)) != 0) {
      flow += f;
    }
  }
  return flow;
}

void addEdge(int from, int to, double cap) {
  int a_index = nodes[from].size();
  int b_index = nodes[to].size();
  Edge e;
  e.to = to;
  e.cap = cap;
  e.rev = b_index;
  nodes[from].push_back(e);
  e.to = from;
  e.cap = 0;
  e.rev = a_index;
  nodes[to].push_back(e);
}

double getMaxClosureGraph(double guess) {
  //printf("guess = %f\n", guess);
  for (int i = 0; i < 1000 + 100 + 2; ++i) {
    nodes[i].clear();
  }
  for (int i = 0; i < M; ++i) {
    addEdge(source, i, 1);
    int a = 1000 + hard_v[i].first;
    int b = 1000 + hard_v[i].second;
    addEdge(i, a, INF);
    addEdge(i, b, INF);
  }
  for (int i = 0; i < N; ++i) {
    addEdge(i + 1000, target, guess);
  }
  int sum = M;
  double min_cut = getMinCut();
  //printf("sum = %d, min_cut = %f\n", sum, min_cut);
  return sum - min_cut;
}

bool in_team[2000];

void dfsGraphWrong() {
  memset(in_team, false, sizeof(in_team));
  for (int i = 0; i < nodes[target].size(); ++i) {
    Edge& e = nodes[target][i];
    if (nodes[e.to][e.rev].cap < 1e-6) {
      in_team[e.to - 1000] = true;
    }
  }
  for (int i = 0; i < nodes[source].size(); ++i) {
    Edge& e = nodes[source][i];
    printf("e.to = %d, e.cap = %f\n", e.to, e.cap);
    /*
    if (e.to < M && e.cap < 1 - 1e-6) {
      int use_edge = e.to;
      printf("in_team[%d, %d] = true\n", hard_v[use_edge].first, hard_v[use_edge].second);
      in_team[hard_v[use_edge].first] = true;
      in_team[hard_v[use_edge].second] = true;
    }
    */
  }
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < nodes[i].size(); ++j) {
      Edge& e = nodes[i][j];
      printf("edge %d, e.to = %d, e.cap = %f\n", i, e.to, e.cap);
    }
  }
  for (int i = 1000; i < 1000 + N; ++i) {
    for (int j = 0; j < nodes[i].size(); ++j) {
      Edge& e = nodes[i][j];
      printf("node %d, e.to = %d, e.cap = %f\n", i - 1000, e.to, e.cap);
    }
  }
  for (int i = 0; i < nodes[target].size(); ++i) {
    Edge& e = nodes[target][i];
    printf("target e.to = %d, e.cap = %f\n", e.to, e.cap);
  }
}

void dfsGraph() {
  memset(in_team, false, sizeof(in_team));
  in_team[source] = true;
  queue<int> q;
  q.push(source);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (int i = 0; i < nodes[cur].size(); ++i) {
      Edge& e = nodes[cur][i];
      //printf("cur = %d, to = %d, cap = %f\n", cur, e.to, e.cap);
      if (!in_team[e.to] && e.cap > 1e-6) {
        in_team[e.to] = true;
        q.push(e.to);
      }
    }
  }
}

// Find Maximum density subgraph, change it into the maximum weight closure of a graph.
void solve() {
  if (M == 0) {
    printf("1\n1\n");
    return;
  }
  double guess_low = 0;
  double guess_high = M;
  double step = 1.0 / N / N;
  while (true) {
    //printf("guess_high = %f, guess_low = %f\n", guess_high, guess_low);
    if (guess_high - guess_low < step) {
      break;
    }
    double mid = (guess_high + guess_low) / 2;
    double flow = getMaxClosureGraph(mid);
    //printf("mid = %f, flow = %f\n", mid, flow);
    if (flow < 1e-6) {
      guess_high = mid;
    } else {
      guess_low = mid;
    }
  }
  getMaxClosureGraph(guess_low);
  dfsGraph();
  int count = 0;
  for (int i = 0; i < N; ++i) {
    if (in_team[i + 1000]) {
      count++;
    }
  }
  //printf("guess = %f\n", guess_high);
  printf("%d\n", count);
  for (int i = 0; i < N; ++i) {
    if (in_team[i + 1000]) {
      printf("%d\n", i + 1);
    }
  }
}

int main() {
  freopen("HardLife.in", "r", stdin);
  while (scanf("%d%d", &N, &M) == 2 && N != 0) {
    hard_v.resize(M);
    for (int i = 0; i < M; ++i) {
      int a, b;
      scanf("%d%d", &a, &b);
      hard_v[i].first = a - 1;
      hard_v[i].second = b - 1;
    }
    solve();
  }
  return 0;
}
