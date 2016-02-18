#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cmath>

using namespace std;

int s[6];

void subOneSlots(int count) {
  s[0] -= min(s[0], count);
}

void subTwoSlots(int count) {
  if (count <= s[1]) {
    s[1] -= count;
  } else {
    subOneSlots((count - s[1]) * 4);
    s[1] = 0;
  }
}

long long getBoxes() {
  long long boxes = 0;
  // 6 * 6.
  boxes += s[5];
  // 5 * 5.
  boxes += s[4];
  subOneSlots(11 * s[4]);
   // 4 * 4.
  boxes += s[3];
  subTwoSlots(5 * s[3]);
  // 3 * 3.
  boxes += s[2] / 4;
  s[2] %= 4;
  if (s[2] == 1) {
    boxes++;
    subTwoSlots(5);
    subOneSlots(7);  
  } else if (s[2] == 2) {
    boxes++;
    subTwoSlots(3);
    subOneSlots(6);
  } else if (s[2] == 3) {
    boxes++;
    subTwoSlots(1);
    subOneSlots(5);
  }
  boxes += s[1] / 9;
  s[1] %= 9;
  if (s[1] != 0) {
    boxes++;
    subOneSlots(36 - s[1] * 4);
  }
  boxes += s[0] / 36;
  s[0] %= 36;
  if (s[0] != 0) {
    boxes++;
  }
  return boxes;
}

long long getBoxes2(int s[6]) {
  int space[4] = {0, 5, 3, 1};
  long long n = s[5] + s[4] + s[3] + ceil(s[2] / 4.0);
  long long y = 5 * s[3] + space[s[2] % 4];
  if (s[1] > y) {
    n += ceil((s[1] - y) / 9.0);
  }
  long long x = 36 * n - 36 * s[5] - 25 * s[4] - 16 * s[3] - 9 * s[2] - 4 * s[1];
  if (s[0] > x) {
    n += ceil((s[0] - x) / 36.0);
  }
  return n;
}

void test() {
  int test_count = 1000;
  while (test_count-- > 0) {
    int t[6];
    for (int i = 0; i < 6; ++i) {
      t[i] = s[i] = rand() % 100;
    }
    long long result2 = getBoxes2(s);
    long long result = getBoxes();
    if (result != result2) {
      for (int i = 0; i < 6; ++i) {
        printf("t[%d] = %d\n", i, t[i]);
      }
      printf("result = %lld, result2 = %lld\n", result, result2);
      break;
    }
  }
}

int main() {
  freopen("Packets.in", "r", stdin);
  test();
  while (true) {
    int zero_count = 0;
    for (int i = 0; i < 6; ++i) {
      scanf("%d", &s[i]);
      zero_count += (s[i] == 0);
    }
    if (zero_count == 6) {
      break;
    }
    long long result2 = getBoxes2(s);
    long long result = getBoxes();
    printf("%lld\n", result);
  }
  return 0;
}
