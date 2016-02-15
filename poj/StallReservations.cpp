#include <stdio.h>

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int N;

struct Node {
  int origin_index;
  int start;
  int end;
};

Node nodes[50000];

int stalls[50000];

bool compareStart(const Node& n1, const Node& n2) {
  return n1.start < n2.start;
}

struct Stall {
  int index;
  int free_start;
};

class CompareStallStart {
 public:
  bool operator()(const Stall& s1, const Stall& s2) {
    return s1.free_start > s2.free_start;
  }
};

int getStalls() {
  priority_queue<Stall, vector<Stall>, CompareStallStart> q;
  int stall_count = 0;
  for (int i = 0; i < N; ++i) {
    if (!q.empty() && q.top().free_start <= nodes[i].start) {
      Stall stall = q.top();
      q.pop();
      stall.free_start = nodes[i].end + 1;
      q.push(stall);
      stalls[nodes[i].origin_index] = stall.index;
    } else {
      Stall stall;
      stall.index = ++stall_count;
      stall.free_start = nodes[i].end + 1;
      q.push(stall);
      stalls[nodes[i].origin_index] = stall.index;
    }
  }
  return stall_count;
}

int main() {
  freopen("StallReservations.in", "r", stdin);
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    nodes[i].origin_index = i;
    scanf("%d%d", &nodes[i].start, &nodes[i].end);
  }
  sort(nodes, &nodes[N], compareStart);
  int result = getStalls();
  printf("%d\n", result);
  for (int i = 0; i < N; ++i) {
    printf("%d\n", stalls[i]);
  }
  return 0;
}
