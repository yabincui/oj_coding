#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <vector>
using namespace std;

int N, Q;
int64_t A[100000];

struct Cmd {
  char op;
  int a, b, c;
} cmds[100000];

#define TREE_NODES (1 << 18)

struct Node {
  int64_t sum;
  int64_t to_add; // value to be added to this node and its subtree.
} nodes[TREE_NODES + 1];

void build(int root, int left, int right) {
  if (left == right) {
    nodes[root].sum = A[left];
  } else {
    int mid = (left + right) / 2;
    build(root * 2 + 1, left, mid);
    build(root * 2 + 2, mid + 1, right);
    nodes[root].sum = nodes[root * 2 + 1].sum + nodes[root * 2 + 2].sum;
  }
  nodes[root].to_add = 0;
}

void update(int root, int left, int right, int a, int b, int add_value) {
  if (left == right) {
    int64_t add = nodes[root].to_add;
    nodes[root].to_add = 0;
    if (left >= a && left <= b) {
      add += add_value;
    }
    nodes[root].sum += add;
  } else if (right < a || left > b) {
    int64_t add = nodes[root].to_add;
    nodes[root].to_add = 0;
    nodes[root].sum += add * (right - left + 1);
    nodes[root * 2 + 1].to_add += add;
    nodes[root * 2 + 2].to_add += add;
  } else if (left >= a && right <= b) {
    int64_t add = nodes[root].to_add + add_value;
    nodes[root].to_add = 0;
    nodes[root].sum += add * (right - left + 1);
    nodes[root * 2 + 1].to_add += add;
    nodes[root * 2 + 2].to_add += add;
  } else {
    nodes[root * 2 + 1].to_add += nodes[root].to_add;
    nodes[root * 2 + 2].to_add += nodes[root].to_add;
    nodes[root].to_add = 0;
    int mid = (left + right) / 2;
    update(root * 2 + 1, left, mid, a, b, add_value);
    update(root * 2 + 2, mid + 1, right, a, b, add_value);
    nodes[root].sum = nodes[root * 2 + 1].sum + nodes[root * 2 + 2].sum;
  }
}

int64_t query(int root, int left, int right, int a, int b) {
  if (left == right) {
    if (left >= a && left <= b) {
      return nodes[root].sum + nodes[root].to_add;
    }
  } else if (right < a || left > b) {
    return 0;
  } else if (left >= a && right <= b) {
    return nodes[root].sum + nodes[root].to_add * (right - left + 1);
  } else {
    nodes[root * 2 + 1].to_add += nodes[root].to_add;
    nodes[root * 2 + 2].to_add += nodes[root].to_add;
    nodes[root].sum += nodes[root].to_add * (right - left + 1);
    nodes[root].to_add = 0;
    int mid = (left + right) / 2;
    return query(root * 2 + 1, left, mid, a, b) + query(root * 2 + 2, mid + 1, right, a, b);
  }
  return 0;
}

// Solved in segment tree. Segment tree records sum of range[a, b]. It uses to_add item
// to remember value to be added at each subtree.
void solve() {
  build(0, 0, N-1);
  for (int i = 0; i < Q; ++i) {
    if (cmds[i].op == 'C') {
      update(0, 0, N-1, cmds[i].a, cmds[i].b, cmds[i].c);
    } else {
      int64_t result = query(0, 0, N-1, cmds[i].a, cmds[i].b);
      printf("%lld\n", result);
    }
  }
}

void update2(int root, int left, int right, int a, int b, int add_value) {
  if (left >= a && right <= b) {
    nodes[root].to_add += add_value;
  } else if (left <= b && right >= a) {
    nodes[root].sum += (min(right, b) - max(left, a) + 1) * add_value;
    int mid = (left + right) / 2;
    update2(root * 2 + 1, left, mid, a, b, add_value);
    update2(root * 2 + 2, mid + 1, right, a, b, add_value);
  }
}

int64_t query2(int root, int left, int right, int a, int b) {
  if (left >= a && right <= b) {
    return nodes[root].sum + nodes[root].to_add * (right - left + 1);
  } else if (left <= b && right >= a) {
    int64_t res = nodes[root].to_add * (min(right, b) - max(left, a) + 1);
    int mid = (left + right) / 2;
    res += query2(root * 2 + 1, left, mid, a, b);
    res += query2(root * 2 + 2, mid + 1, right, a, b);
    return res;
  }
  return 0;
}

// Still in segment tree. Use more concise code.
void solve2() {
  build(0, 0, N-1);
  for (int i = 0; i < Q; ++i) {
    if (cmds[i].op == 'C') {
      update2(0, 0, N-1, cmds[i].a, cmds[i].b, cmds[i].c);
    } else {
      int64_t result = query2(0, 0, N-1, cmds[i].a, cmds[i].b);
      printf("%lld\n", result);
    }
  }
}

int main() {
  freopen("ASimpleProblemWithIntegers.in", "r", stdin);
  scanf("%d%d", &N, &Q);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &A[i]);
  }
  for (int i = 0; i < Q; ++i) {
    do {
      cmds[i].op = getchar();
    } while (cmds[i].op != 'C' && cmds[i].op != 'Q');
    if (cmds[i].op == 'C') {
      scanf("%d%d%d", &cmds[i].a, &cmds[i].b, &cmds[i].c);
    } else {
      scanf("%d%d", &cmds[i].a, &cmds[i].b);
    }
    cmds[i].a--;
    cmds[i].b--;
  }
  solve2();
  return 0;
}
