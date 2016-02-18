#include <ctype.h>
#include <limits.h>
#include <stdio.h>

#include <algorithm>

using namespace std;

int N, M;

char S[2000];

int add_cost[256];
int del_cost[256];

int dp[2000][2000];

char getChar() {
  char c;
  do {
    c = getchar();
  } while (!islower(c));
  return c;
}

int getMinCost() {
  for (int len = 1; len <= M; ++len) {
    for (int i = 0; i <= M - len; ++i) {
      int j = i + len - 1;
      if (len == 1) {
        dp[i][j] = 0;
        continue;
      }
      int min_cost = INT_MAX;
      if (S[i] == S[j]) {
        if (i == j - 1) {
          min_cost = 0;
        } else {
          min_cost = dp[i+1][j-1];
        }
      }
      if (add_cost[S[i]] != -1) {
        min_cost = min(min_cost, dp[i+1][j] + add_cost[S[i]]);
        min_cost = min(min_cost, dp[i+1][j] + del_cost[S[i]]);
      }
      if (add_cost[S[j]] != -1) {
        min_cost = min(min_cost, dp[i][j-1] + add_cost[S[j]]);
        min_cost = min(min_cost, dp[i][j-1] + del_cost[S[j]]);
      }
      dp[i][j] = min_cost;
    }
  }
  return dp[0][M-1];
}

int main() {
  freopen("CheapestPalindrome.in", "r", stdin);
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; ++i) {
    S[i] = getChar();
  }
  memset(add_cost, -1, sizeof(add_cost));
  memset(del_cost, -1, sizeof(del_cost));
  for (int i = 0; i < N; ++i) {
    char c = getChar();
    int add, del;
    scanf("%d%d", &add, &del);
    add_cost[c] = add;
    del_cost[c] = del;
  }
  int result = getMinCost();
  printf("%d\n", result);
  return 0;
}
