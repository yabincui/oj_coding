#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

int K;

struct Block {
  int h;
  int c;
  int a;
} blocks[400];

bool dp[400 * 100 * 10 + 1];

bool compareBlock(const Block& b1, const Block& b2) {
  return b1.a < b2.a;
}

void frontToBack(int step, int limit) {
  for (int i = step; i <= limit; ++i) {
    dp[i] |= dp[i - step];
  }
}

void backToFront(int step, int limit) {
  for (int i = limit; i >= step; --i) {
    dp[i] |= dp[i - step];
  }
}

int getHighest() {
  memset(dp, false, sizeof(dp));
  dp[0] = true;
  for (int i = 0; i < K; ++i) {
    if (blocks[i].c * blocks[i].h >= blocks[i].a) {
      frontToBack(blocks[i].h, blocks[i].a);
    } else {
      int count = blocks[i].c;
      for (int k = 1; k < count; k *= 2) {
        backToFront(blocks[i].h * k, blocks[i].a);
        count -= k;
      }
      backToFront(blocks[i].h * count, blocks[i].a);
    }
  }
  for (int i = sizeof(dp) - 1; i >= 0; --i) {
    if (dp[i]) {
      return i;
    }
  }
  return 0;
}

int main() {
  freopen("SpaceElevator.in", "r", stdin);
  scanf("%d", &K);
  for (int i = 0; i < K; ++i) {
    scanf("%d%d%d", &blocks[i].h, &blocks[i].a, &blocks[i].c);
  }
  sort(blocks, &blocks[K], compareBlock);
  int result = getHighest();
  printf("%d\n", result);
  return 0;
}
