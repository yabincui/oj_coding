#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

struct Node {
  uint64_t x, y, z;
  uint64_t cur;
};

bool has_odd_number;
uint64_t odd_number;
int repeat_time;

class NodeComparator {
 public:
  bool operator()(const Node& n1, const Node& n2) {
    return n1.cur > n2.cur;
  }
};

// Timeout
void checkOddNumber(const vector<Node>& nodes) {
  priority_queue<Node, vector<Node>, NodeComparator> q;
  for (int i = 0; i < nodes.size(); ++i) {
    if (nodes[i].x <= nodes[i].y) {
      Node node = nodes[i];
      node.cur = node.x;
      q.push(node);
    }
  }
  while (q.size() >= 2) {
    uint64_t value = q.top().cur;
    int count = 0;
    while (!q.empty() && q.top().cur == value) {
      //printf("try q.top = %llu\n", q.top().cur);
      Node node = q.top(); q.pop();
      if (node.cur + node.z <= node.y) {
        node.cur += node.z;
        //printf("push cur = %llu\n", node.cur);
        q.push(node);
      }
      count++;
    }
    if (count % 2 == 1) {
      has_odd_number = true;
      odd_number = value;
      repeat_time = count;
      return;
    }
  }
}

bool isOdd(uint64_t limit, const vector<Node>& nodes) {
  uint64_t count = 0;
  for (int i = 0; i < nodes.size(); ++i) {
    if (limit >= nodes[i].x) {
      uint64_t up = (limit > nodes[i].y) ? nodes[i].y : limit;
      count += (up - nodes[i].x) / nodes[i].z + 1;
    }
  }
  return count % 2 == 1;
}

int getValueCount(uint64_t value, const vector<Node>& nodes) {
  int count = 0;
  for (int i = 0; i < nodes.size(); ++i) {
    if (value >= nodes[i].x && value <= nodes[i].y && (value - nodes[i].x) % nodes[i].z == 0) {
      count++;
    }
  }
  return count;
}

// Exactly one number occurs odd time.
void checkOddNumber2(const vector<Node>& nodes) {
  uint64_t low = 0;
  uint64_t high = (1ULL << 32);
  while (low + 1 < high) {
    uint64_t mid = (low + high) / 2;
    if (isOdd(mid, nodes)) {
      high = mid;
    } else {
      low = mid;
    }
  }
  if (isOdd(high, nodes)) {
    has_odd_number = true;
    odd_number = high;
    repeat_time = getValueCount(high, nodes);
  }
  if (isOdd(low, nodes)) {
    has_odd_number = true;
    odd_number = low;
    repeat_time = getValueCount(low, nodes);
  }
}

int main() {
  freopen("Showstopper.in", "r", stdin);
  char buf[120];
  while (fgets(buf, sizeof(buf), stdin) != NULL) {
    vector<Node> nodes;
    uint64_t x, y, z;
    while (sscanf(buf, "%llu%llu%llu", &x, &y, &z) != 3) {
      if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 0;
      }
    }
    while (sscanf(buf, "%llu%llu%llu", &x, &y, &z) == 3) {
      Node node;
      node.x = x; node.y = y; node.z = z;
      nodes.push_back(node);
      if (fgets(buf, sizeof(buf), stdin) == NULL) {
        break;
      }
    }
    has_odd_number = false;
    checkOddNumber2(nodes);
    if (!has_odd_number) {
      printf("no corruption\n");
    } else {
      printf("%llu %d\n", odd_number, repeat_time);
    }
  }
  return 0;
}
