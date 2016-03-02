#include <stdio.h>
#include <string.h>

#include <queue>

using namespace std;

bool is_prime[10000];

void init() {
  memset(is_prime, true, sizeof(is_prime));
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i < 10000; ++i) {
    if (is_prime[i]) {
      for (int j = i + i; j < 10000; j += i) {
        is_prime[j] = false;
      }
    }
  }
}

bool visited[10000];

int main() {
  freopen("PrimePath.in", "r", stdin);
  init();
  int tests;
  scanf("%d", &tests);
  while (--tests >= 0) {
    int a, b;
    scanf("%d%d", &a, &b);
    queue<int> q;
    memset(visited, false, sizeof(visited));
    q.push(a);
    visited[a] = true;
    bool found = false;
    int step;
    for (step = 0; !q.empty(); step++) {
      size_t size = q.size();
      while (size-- > 0) {
        int n = q.front(); q.pop();
        if (n == b) {
          found = true;
          break;
        }
        for (int i = 1; i <= 1000; i *= 10) {
          for (int j = 0; j < 10; ++j) {
            if (i == 1000 && j == 0) {
              continue;
            }
            int d = (n / i) % 10;
            if (d == j) {
              continue;
            }
            int next = n + (j - d) * i;
            if (is_prime[next] && !visited[next]) {
              visited[next] = true;
              q.push(next);
            }
          }
        }
      }
      if (found) {
        break;
      }
    }
    if (!found) {
      printf("Impossible\n");
    } else {
      printf("%d\n", step);
    }
  }
  return 0;
}
