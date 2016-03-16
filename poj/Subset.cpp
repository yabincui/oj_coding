#include <stdio.h>
#include <stdint.h>

#include <algorithm>
#include <utility>
using namespace std;

struct Node {
  int64_t sum;
  int num;
} nodes[1 << 20];

int N;
int64_t s[35];

bool compareSum(const Node& n1, const Node& n2) {
  if (n1.sum != n2.sum) {
    return n1.sum < n2.sum;
  }
  return n1.num < n2.num;
}

bool compareNodeSum(const Node& n, const int64_t& value) {
  return n.sum < value;
}

int64_t Abs(int64_t num) {
  return num < 0 ? -num : num;
}

Node* Min(Node* p, Node* q) {
  return p < q ? p : q;
}

Node* Max(Node* p, Node* q) {
  return p < q ? q : p;
}

int64_t bestSum;
int bestNum;

void getResult2() {
  int n2 = N / 2;
  int n1 = N - n2;
  for (int i = 0; i < (1 << n2); ++i) {
    nodes[i].num = 0;
    nodes[i].sum = 0;
    for (int j = 0; j < n2; ++j) {
      if (i & (1 << j)) {
        nodes[i].sum += s[n1 + j];
        nodes[i].num++;
      }
    }
  }
  Node* nodes_end = nodes + (1 << n2);
  sort(nodes, nodes_end, compareSum);
  for (int i = 0; i < (1 << n2); ++i) {
    if (i > 0 && nodes[i].sum == nodes[i - 1].sum && nodes[i - 1].num != 0) {
      nodes[i].num = nodes[i - 1].num;
    }
  }

  bestSum = -1;
  bestNum = 0;
  for (int i = 0; i < (1 << n1); ++i) {
    int64_t sum = 0;
    int num = 0;
    for (int j = 0; j < n1; ++j) {
      if (i & (1 << j)) {
        sum += s[j];
        num++;
      }
    }
    int64_t value = -sum;
    Node* it = lower_bound(nodes, nodes_end, value, compareNodeSum);
    int64_t sum1 = Abs(sum);
    int num1 = num;
    for (Node* p = Max(it - 1, nodes); p <= Min(nodes_end - 1, it + 1); ++p) {
      int64_t sum2 = Abs(sum + p->sum);
      int num2 = num + p->num;
      if (num2 != 0) {
        if (num1 == 0 || sum1 > sum2 || (sum1 == sum2 && num1 > num2)) {
          sum1 = sum2;
          num1 = num2;
        }
      }
    }
    sum = sum1;
    num = num1;
    if (num == 0) {
      continue;
    }
    if (bestSum == -1 || (bestSum > sum) || (bestSum == sum && bestNum > num)) {
      bestSum = sum;
      bestNum = num;
    }
  }
}

void checkValue(int64_t sum, int num) {
  if (num == 0) {
    return;
  }
  sum = Abs(sum);
  if (bestSum == -1 || bestSum > sum || (bestSum == sum && bestNum > num)) {
    bestSum = sum;
    bestNum = num;
  }
}

void getResult3() {
  int n2 = N / 2;
  int n1 = N - n2;
  bestSum = -1;
  bestNum = 0;
  for (int i = 0; i < (1 << n2); ++i) {
    nodes[i].num = 0;
    nodes[i].sum = 0;
    for (int j = 0; j < n2; ++j) {
      if (i & (1 << j)) {
        nodes[i].sum += s[n1 + j];
        nodes[i].num++;
      }
    }
    checkValue(nodes[i].sum, nodes[i].num);
  }
  Node* nodes_end = nodes + (1 << n2);
  sort(nodes, nodes_end, compareSum);
  for (int i = 0; i < (1 << n2); ++i) {
    if (i > 0 && nodes[i].sum == nodes[i - 1].sum) {
      nodes[i].num = nodes[i - 1].num;
    }
  }

  for (int i = 0; i < (1 << n1); ++i) {
    int64_t sum = 0;
    int num = 0;
    for (int j = 0; j < n1; ++j) {
      if (i & (1 << j)) {
        sum += s[j];
        num++;
      }
    }
    int64_t value = -sum;
    Node* it = lower_bound(nodes, nodes_end, value, compareNodeSum);
    if (it != nodes_end) {
      int64_t sum2 = Abs(sum + it->sum);
      int num2 = num + it->num;
      checkValue(sum2, num2);
    }
    if (it != nodes) {
      --it;
      int64_t sum2 = Abs(sum + it->sum);
      int num2 = num + it->num;
      checkValue(sum2, num2);
    }
  }
}

void getResult4() {
  int n2 = N / 2;
  int n1 = N - n2;
  bestSum = -1;
  bestNum = 0;
  for (int i = 0; i < (1 << n2); ++i) {
    nodes[i].num = 0;
    nodes[i].sum = 0;
    for (int j = 0; j < n2; ++j) {
      if (i & (1 << j)) {
        nodes[i].sum += s[n1 + j];
        nodes[i].num++;
      }
    }
    checkValue(nodes[i].sum, nodes[i].num);
  }
  Node* nodes_end = nodes + (1 << n2);
  sort(nodes, nodes_end, compareSum);
  for (int i = 0; i < (1 << n2); ++i) {
    if (i > 0 && nodes[i].sum == nodes[i - 1].sum) {
      nodes[i].num = nodes[i - 1].num;
    }
  }

  for (int i = 0; i < (1 << n1); ++i) {
    int64_t sum = 0;
    int num = 0;
    for (int j = 0; j < n1; ++j) {
      if (i & (1 << j)) {
        sum += s[j];
        num++;
      }
    }
    int64_t value = -sum;
    Node* it = lower_bound(nodes, nodes_end, value, compareNodeSum);
    int64_t sum1 = Abs(sum);
    int num1 = num;
    if (it != nodes_end) {
      int64_t sum2 = Abs(sum + it->sum);
      int num2 = num + it->num;
      /*
      if (num2 != 0) {
        if (num1 == 0 || sum1 > sum2 || (sum1 == sum2 && num1 > num2)) {
          sum1 = sum2;
          num1 = num2;
        }
      }
      */
      checkValue(sum2, num2);
    }
    if (it != nodes) {
      --it;
      int64_t sum2 = Abs(sum + it->sum);
      int num2 = num + it->num;
      /*
      if (num2 != 0) {
        if (num1 == 0 || sum1 > sum2 || (sum1 == sum2 && num1 > num2)) {
          sum1 = sum2;
          num1 = num2;
        }
      }
      */
      checkValue(sum2, num2);
    }
    /*
    sum = sum1;
    num = num1;
    if (num == 0) {
      continue;
    }
    if (bestSum == -1 || (bestSum > sum) || (bestSum == sum && bestNum > num)) {
      bestSum = sum;
      bestNum = num;
    }
    */
  }
}

int main() {
  freopen("Subset.in", "r", stdin);
  while (scanf("%d", &N) == 1 && N != 0) {
    for (int i = 0; i < N; ++i) {
      scanf("%lld", &s[i]);
    }
    getResult2();
    printf("%lld %d\n", bestSum, bestNum);
  }
  return 0;
}
