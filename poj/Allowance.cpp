#include <limits.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <utility>

using namespace std;

int N, C;
pair<int, int> coins[20];

int getDays() {
  int days = 0;
  sort(coins, &coins[N]);
  while (true) {
    int solution[20];
    int last = C;
    memset(solution, 0, sizeof(solution));
    for (int i = N - 1; i >= 0 && last > 0; --i) {
      int count = min(coins[i].second, last / coins[i].first);
      last -= count * coins[i].first;
      solution[i] = count;
    }
    //printf("last = %d\n", last);
    if (last > 0) {
      for (int i = 0; i < N; ++i) {
        if (coins[i].first >= last && solution[i] < coins[i].second) {
          solution[i]++;
          /*
          for (int j = 0; j < i; ++j) {
            solution[j] = 0;
          }
          */
          last = 0;
          break;
        }
      }
    }
    //printf("last = %d\n", last);
    if (last > 0) {
      break;
    }
/*
    for (int i = 0; i < N; ++i) {
      printf("(value %d, count %d) ", coins[i].first, solution[i]);
    }
    printf("\n");
*/
    int time = INT_MAX;
    for (int i = 0; i < N; ++i) {
      if (solution[i] > 0) {
        time = min(time, coins[i].second / solution[i]);
      }
    }
    days += time;
    for (int i = 0; i < N; ++i) {
      coins[i].second -= solution[i] * time;
    }
  }
  return days;
}

int main() {
  freopen("Allowance.in", "r", stdin);
  scanf("%d%d", &N, &C);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &coins[i].first, &coins[i].second);
  }
  int result = getDays();
  printf("%d\n", result);
  return 0;
}
