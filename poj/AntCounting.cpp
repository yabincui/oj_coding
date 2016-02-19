#include <stdio.h>
#include <string.h>

/*
  1, 1, 2, 2, 3

  2  {1, 1}, {1, 2}, {1, 3}, {2, 2}, {2, 3}
  3 {1, 1, 2}, {1, 1, 3}, {1, 2, 2}, {1, 2, 3}, {2, 2, 3}

  dp[i][j] = dp[i-j][j] + dp[i][j-1], O(T * B) (10^5 * 10^3), use how many ants in this level.
  count, zb, cb. O(T * B * log(Ni)) = O(10^9).
*/

int T, A, S, B;

int types[1000];
int dp[100001];
int cur[100001];

#define LIMIT 1000000

void incFromFront(int c) {
  for (int i = c; i <= B; ++i) {
    dp[i] += dp[i-c];
    if (dp[i] >= LIMIT) {
      dp[i] -= LIMIT;
    }
  }
  /*
  printf("incFromFront(%d)\n", c);
  for (int i = 0; i <= B; ++i) {
    printf("dp[%d] = %d\n", i, dp[i]);
  }
  */
}

void incFromBack(int c) {
  for (int i = B; i >= c; --i) {
    dp[i] += dp[i-c];
    if (dp[i] >= LIMIT) {
      dp[i] -= LIMIT;
    }
  }
  /*
  printf("incFromBack(%d)\n", c);
  for (int i = 0; i <= B; ++i) {
    printf("dp[%d] = %d\n", i, dp[i]);
  }
  */
}

int getCount() {
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;
  for (int i = 0; i < T; ++i) {
    int count = types[i];
    printf("type %d, count %d\n", i, count);
    if (count >= B) {
      incFromFront(1);
      continue;
    }
    for (int k = 1; k < count; k <<= 1) {
      incFromBack(k);
      count -= k;
      continue;
    }
    // incFromBack(count) can repeat with incFromBack(k).
    incFromBack(count);
  }
  int count = 0;
  for (int i = S; i <= B; ++i) {
    count += dp[i];
    if (count >= LIMIT) {
      count -= LIMIT;
    }
  }
  return count;
}

int getCount2() {
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;
  for (int i = 0; i < T; ++i) {
    if (types[i] >= B) {
      incFromFront(1);
      continue;
    }
    memset(cur, 0, sizeof(cur));
    int count = types[i];
    int k = 0;
    int add = cur[0] = 1;
    for (int j = 1; j <= B; ++j) {
      cur[j] = dp[j];
      if (k < j - count) {
        add -= cur[k];
        if (add < 0) {
          add += LIMIT;
        }
        k++;
      }
      dp[j] += add;
      if (dp[j] >= LIMIT) {
        dp[j] -= LIMIT;
      }
      add += cur[j];
      if (add >= LIMIT) {
        add -= LIMIT;
      }
    }
    /*
    printf("after type[%d] = %d\n", i, types[i]);
    for (int t = 0; t <= B; ++t) {
      printf("dp[%d] = %d, cur[%d] = %d\n", t, dp[t], t, cur[t]);
    }
    */
  }
  int result = 0;
  for (int i = S; i <= B; ++i) {
    result += dp[i];
    if (result >= LIMIT) {
      result -= LIMIT;
    }
  }
  return result;
}

int main() {
  freopen("AntCounting.in", "r", stdin);
  scanf("%d%d%d%d", &T, &A, &S, &B);
  memset(types, 0, sizeof(types));
  for (int i = 0; i < A; ++i) {
    int temp;
    scanf("%d", &temp);
    types[temp - 1]++;
  }
  int result = getCount2();
  printf("%d\n", result);
  return 0;
}
