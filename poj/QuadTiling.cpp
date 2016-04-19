// POJ 3240
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int N, M;

// table[i][j] is the situations that go from prev line in situation i to next line in situation j.
int table[16][16];

enum Action {
  Leave,
  LinkToAbove,
  LinkToPrev,
  LinkToAfter,
};

void init() {
  for (int i = 0; i < 16; ++i) {
    int prev[4];
    for (int j = 0; j < 4; ++j) {
      prev[j] = (i >> j) & 1;
    }
    for (int action = 0; action < (1 << 8); ++action) {
      enum Action s[4];
      for (int k = 0; k < 4; ++k) {
        s[k] = (Action)((action >> (k * 2)) & 3);
      }
      bool valid = true;
      int next[4];
      memset(next, 0, sizeof(next));
      for (int k = 0; k < 4; ++k) {
        if (prev[k] == 0) {
          if (s[k] == LinkToAbove) {
            next[k] = 1;
          } else {
            valid = false;
            break;
          }
        } else {
          if (s[k] == LinkToAfter && (k + 1 < 4 && s[k+1] == LinkToPrev)) {
            next[k] = 1;
          } else if (k != 0 && s[k] == LinkToPrev && s[k-1] == LinkToAfter) {
            next[k] = 1;
          } else if (s[k] == Leave) {
            continue;
          } else {
            valid = false;
            break;
          }
        }
      }
      if (!valid) {
        continue;
      }
      int j = 0;
      for (int k = 0; k < 4; ++k) {
        j |= (next[k] << k);
      }
      table[i][j]++;
    }
  }
  /*
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      printf("table[%d][%d] = %d\n", i, j, table[i][j]);
    }
  }
  */
}

struct Matrix {
  int64_t v[16][16];
  int row;
  int col;

  Matrix(int row, int col) : row(row), col(col) {
    memset(v, 0, sizeof(v));
  }
};

Matrix Mul(const Matrix& A, const Matrix& B) {
  Matrix res(A.row, B.col);
  for (int i = 0; i < A.row; ++i) {
    for (int j = 0; j < B.col; ++j) {
      for (int k = 0; k < A.col; ++k) {
        res.v[i][j] = (res.v[i][j] + A.v[i][k] * B.v[k][j]) % M;
      }
    }
  }
  return res;
}

void solve() {
  Matrix A(1, 16);
  A.v[0][15] = 1;

  Matrix P(16, 16);
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      P.v[i][j] = table[i][j] % M;
    }
  }
  Matrix B(16, 16);
  for (int i = 0; i < 16; ++i) {
    B.v[i][i] = 1;
  }
  int n = N;
  while (n != 0) {
    if (n & 1) {
      B = Mul(B, P);
    }
    P = Mul(P, P);
    n >>= 1;
  }
  A = Mul(A, B);
  printf("%lld\n", A.v[0][15]);
}

int main() {
  init();
  freopen("QuadTiling.in", "r", stdin);
  while (scanf("%d%d", &N, &M) == 2 && !(N == 0 && M == 0)) {
    solve();
  }
}
