#include <stdio.h>

#include <algorithm>
using namespace std;

struct Node {
  int w;
  int s;
} nodes[50000];

int N;

bool compareNode(const Node& n1, const Node& n2) {
  int max1 = max(-n1.s, n1.w - n2.s);
  int max2 = max(-n2.s, n2.w - n1.s);
  return max1 < max2;
}

bool compareNode2(const Node& n1, const Node& n2) {
  return n1.w + n1.s < n2.w + n2.s;
}

int getMinRisk() {
  //sort(nodes, nodes + N, compareNode2);
  sort(nodes, nodes + N, compareNode);
  int res = -1000000000;
  int prev = 0;
  for (int i = 0; i < N; ++i) {
    res = max(res, prev - nodes[i].s);
    prev += nodes[i].w;
  }
  return res;
}


bool compareNodeByStrength(const Node& n1, const Node& n2) {
  return n1.s < n2.s;
}

bool isOk(int limit) {
  int last_weight = 0;
  for (int i = 0; i < N; ++i) {
    last_weight += nodes[i].w;
  }
  int end = N - 1;
  while (end >= 0) {
    int k = -1;
    for (int i = end; i >= 0; --i) {
      if (last_weight - nodes[i].w <= nodes[i].s + limit) {
        k = i;
        break;
      }
    }
    if (k == -1) {
      return false;
    }
    for (int i = k; i <= end; ++i) {
      last_weight -= nodes[i].w;
    }
    end = k - 1;
  }
  return true;
}

int getMinRisk2() {
  sort(nodes, nodes + 1, compareNodeByStrength);
  int low = -1000000000;
  int high = 1000000000;
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    if (isOk(mid)) {
      high = mid;
    } else {
      low = mid;
    }
  }
  if (isOk(low)) {
    return low;
  }
  return high;
}

int main() {
  freopen("CowAcrobats.in", "r", stdin);
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &nodes[i].w, &nodes[i].s);
  }
  int result = getMinRisk();
  int result2 = getMinRisk2();
  if (result != result2) {
    while (true);
    printf("result1 = %d, result2 = %d\n", result, result2);
    return 1;
  }
  printf("%d\n", result);
  return 0;
}
