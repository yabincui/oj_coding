#include <stdio.h>

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int N, T;

struct Node {
  int start;
  int end;
};

Node nodes[25000];

bool compareStart(const Node& n1, const Node& n2) {
  return n1.start < n2.start;
}

class CompareEnd {
 public:
  bool operator()(const Node& n1, const Node& n2) {
    return n1.end < n2.end;
  }
};

int getMinCows() {
  priority_queue<Node, vector<Node>, CompareEnd> q;
  int cur_t = 1;
  int cow_count = 0;
  int node_index = 0;
  while (cur_t <= T) {
    while (node_index < N && nodes[node_index].start <= cur_t) {
      q.push(nodes[node_index++]);
    }
    if (q.empty()) {
      return -1;
    }
    Node node = q.top();
    q.pop();
    cur_t = node.end + 1;
    cow_count++;
  }
  return cow_count;
}

int main() {
  freopen("CleaningShifts.in", "r", stdin);
  scanf("%d%d", &N, &T);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &nodes[i].start, &nodes[i].end);
  }
  sort(nodes, &nodes[N], compareStart);
  int result = getMinCows();
  printf("%d\n", result);
  return 0;
}
