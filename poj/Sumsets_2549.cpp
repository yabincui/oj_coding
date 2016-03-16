#include <stdio.h>

#include <algorithm>
#include <climits>
#include <map>
using namespace std;

int n;
int s[1000];

int getResult() {
  map<int, int> m;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (i == j) {
        continue;
      }
      m[s[i] + s[j]]++;
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    int d = s[i];
    bool ok = false;
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      int c = s[j];
      map<int, int>::iterator it = m.find(d - c);
      if (it == m.end()) {
        continue;
      }
      // a + b + c = d
      // c == a || c == b?
      if (it->second == 1 && m.find(d - c - c) != m.end()) {
        continue;
      }
      // d = a, b + c == 0, b = -c
      if (it->second == 1 && m.find(-c) != m.end()) {
        continue;
      }
      ok = true;
      break;
    }
    if (ok) {
      return i;
    }
  }
  return -1;
}

int s2[1000000];

int getResult2() {
  int n2 = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      s2[n2++] = s[i] + s[j];
    }
  }
  s2[n2] = INT_MAX;
  sort(s2, s2 + n2);
  for (int i = n - 1; i >= 0; --i) {
    int d = s[i];
    bool ok = false;
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      int c = s[j];
      int* it = lower_bound(s2, s2 + n2, d - c);
      if (*it != d - c) {
        continue;
      }
      bool single = !(*(it + 1) == d - c);
      // a + b + c = d
      // c == a?
      if (single && *lower_bound(s2, s2 + n2, d - c - c) == d - c - c) {
        continue;
      }
      // d = a, b = -c
      if (single && *lower_bound(s2, s2 + n2, -c) == -c) {
        continue;
      }
      ok = true;
      break;
    }
    if (ok) {
      return i;
    }
  }
  return -1;
}

struct Node {
  int value;
  int i, j;
};

bool compareNode(const Node& n1, const Node& n2) {
  return n1.value < n2.value;
}

Node nodes[1000000];
int getResult3() {
  int n2 = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      nodes[n2].value = s[i] + s[j];
      nodes[n2].i = i;
      nodes[n2].j = j;
      n2++;
    }
  }
  nodes[n2].value = INT_MAX;
  sort(nodes, nodes + n2, compareNode);
  for (int i = n - 1; i >= 0; --i) {
    int d = s[i];
    bool ok = false;
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      int c = s[j];
      int key = d - c;
      Node node;
      node.value = key;
      Node* it = lower_bound(nodes, nodes + n2, node, compareNode);
      for (; it->value == key; ++it) {
        if (it->i == i || it->i == j || it->j == i || it->j == j) {
          continue;
        }
        ok = true;
        break;
      }
      if (ok) {
        break;
      }
    }
    if (ok) {
      return i;
    }
  }
  return -1;
}

int main() {
  freopen("Sumsets_2549.in", "r", stdin);
  while (scanf("%d", &n) == 1 && n != 0) {
    for (int i = 0; i < n; ++i) {
      scanf("%d", &s[i]);
    }
    sort(s, s+n);
    int index = getResult3();
    if (index == -1) {
      printf("no solution\n");
    } else {
      printf("%d\n", s[index]);
    }
  }
  return 0;
}
