#include <stdio.h>

int modularMul(int a, int b, int M) {
  a %= M;
  int base = a;
  int res = 1;
  while (b) {
    if (b & 1) {
      res = res * base % M;
    }
    base = base * base % M;
    b >>= 1;
  }
  return res;
}

int main() {
  freopen("RaisingModuloNumbers.in", "r", stdin);
  int Z;
  scanf("%d", &Z);
  while (--Z >= 0) {
    int M, H;
    scanf("%d%d", &M, &H);
    int res = 0;
    for (int i = 0; i < H; ++i) {
      int a, b;
      scanf("%d%d", &a, &b);
      res = (res + modularMul(a, b, M)) % M;
    }
    printf("%d\n", res);
  }
  return 0;
}
