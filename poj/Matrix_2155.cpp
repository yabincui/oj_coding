#include <stdio.h>
#include <string.h>
#include <stdint.h>

int N, T;

struct Op {
  char op;
  int x1, y1, x2, y2;
} Ops[50000];

#define MAX_N 1002

int64_t BIT0[MAX_N][MAX_N];
int64_t BIT1[MAX_N][MAX_N];
int64_t BIT2[MAX_N][MAX_N];
int64_t BIT3[MAX_N][MAX_N];

void addBitValue(int64_t BIT[MAX_N][MAX_N], int x, int y, int value) {
  for (int i = x; i <= N; i += i & -i) {
    for (int j = y; j <= N; j += j & -j) {
      BIT[i][j] += value;
    }
  }
}

int64_t queryBitValue(int64_t BIT[MAX_N][MAX_N], int x, int y) {
  int64_t result = 0;
  for (int i = x; i != 0; i -= i & -i) {
    for (int j = y; j != 0; j -= j & -j) {
      result += BIT[i][j];
    }
  }
  return result;
}

int64_t queryBitValue(int x, int y) {
  int64_t t0 = queryBitValue(BIT0, x, y);
  int64_t t1 = queryBitValue(BIT1, x, y);
  int64_t t2 = queryBitValue(BIT2, x, y);
  int64_t t3 = queryBitValue(BIT3, x, y);
  return t0 + t1 * x + t2 * y + t3 * x * y;
}

// Use two dimentional BIT. Update a range (x1, y1) - (x2, y2) each time.
// To calculate range sum, we need four Binary index Tree: T0, T1, T2, T3.
// The formula is S(x, y) = T0 + T1 * x + T2 * y + T3 * x * y.
// To update a range [(x1, y1), (x2, y2)] to add value t.
// at pos (x1, y1), T0 + t*(x1-1)*(y1-1), T1 - t*(y1-1), T2 - t*(x1-1), T3 + t
// at pos (x1, y2+1), T0 - t*(x1-1)*y2, T1 + t*y2, T2 + t*(x1-1), T3 - t
// at pos (x2+1, y1), T0 - t*x2*(y1-1), T1 + t*(y1-1), T2 + t*x2, T3 - t
// at pos (x2+1, y2+1), T0 + t*x2*y2, T1 - t*y2, T2 - t*x2, T3 + t
void solve() {
  memset(BIT0, 0, sizeof(BIT0));
  memset(BIT1, 0, sizeof(BIT1));
  memset(BIT2, 0, sizeof(BIT2));
  memset(BIT3, 0, sizeof(BIT3));
  for (int i = 0; i < T; ++i) {
    if (Ops[i].op == 'C') {
      int x1 = Ops[i].x1;
      int y1 = Ops[i].y1;
      int x2 = Ops[i].x2;
      int y2 = Ops[i].y2;
      int t = 1;
      addBitValue(BIT0, x1, y1, t * (x1-1) * (y1-1));
      addBitValue(BIT1, x1, y1, -t * (y1-1));
      addBitValue(BIT2, x1, y1, -t * (x1-1));
      addBitValue(BIT3, x1, y1, t);

      addBitValue(BIT0, x1, y2 + 1, -t * (x1-1) * y2);
      addBitValue(BIT1, x1, y2 + 1, t * y2);
      addBitValue(BIT2, x1, y2 + 1, t * (x1-1));
      addBitValue(BIT3, x1, y2 + 1, -t);

      addBitValue(BIT0, x2 + 1, y1, -t * x2 * (y1-1));
      addBitValue(BIT1, x2 + 1, y1, t * (y1-1));
      addBitValue(BIT2, x2 + 1, y1, t * x2);
      addBitValue(BIT3, x2 + 1, y1, -t);

      addBitValue(BIT0, x2 + 1, y2 + 1, t * x2 * y2);
      addBitValue(BIT1, x2 + 1, y2 + 1, -t * y2);
      addBitValue(BIT2, x2 + 1, y2 + 1, -t * x2);
      addBitValue(BIT3, x2 + 1, y2 + 1, t);
      /*
      for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
          printf("BIT0[%d][%d] = %lld\n", i, j, BIT0[i][j]);
          printf("BIT1[%d][%d] = %lld\n", i, j, BIT1[i][j]);
          printf("BIT2[%d][%d] = %lld\n", i, j, BIT2[i][j]);
          printf("BIT3[%d][%d] = %lld\n", i, j, BIT3[i][j]);
        }
      }
      */
    } else {
      int64_t a = queryBitValue(Ops[i].x1, Ops[i].y1);
      int64_t b = queryBitValue(Ops[i].x1 - 1, Ops[i].y1);
      int64_t c = queryBitValue(Ops[i].x1, Ops[i].y1 - 1);
      int64_t d = queryBitValue(Ops[i].x1 - 1, Ops[i].y1 - 1);
      int64_t value = (a + d) - (b + c);
      //printf("a = %lld, b = %lld, c = %lld, d = %lld, value = %lld\n", a, b, c, d, value);
      value &= 1;
      printf("%lld\n", value);
    }
  }
}

int main() {
  freopen("Matrix_2155.in", "r", stdin);
  int test;
  scanf("%d", &test);
  for (int t = 0; t < test; ++t) {
    scanf("%d%d", &N, &T);
    for (int i = 0; i < T; ++i) {
      char op;
      do {
        op = getchar();
      } while (op != 'Q' && op != 'C');
      Ops[i].op = op;
      if (op == 'Q') {
        scanf("%d%d", &Ops[i].x1, &Ops[i].y1);
      } else {
        scanf("%d%d%d%d", &Ops[i].x1, &Ops[i].y1, &Ops[i].x2, &Ops[i].y2);
      }
    }
    solve();
    if (t != test - 1) {
      printf("\n");
    }
  }
  return 0;
}
