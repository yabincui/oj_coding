// POJ 3735
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int N, M, K;

struct Op {
  char op;
  int a, b;
} ops[100];

struct Matrix {
  int64_t v[101][101];
  int row;
  int col;

  Matrix(int row, int col) : row(row), col(col) {
    memset(v, 0, sizeof(v));
  }

  // For g op.
  void addCol(int from, int to) {
    for (int i = 0; i < row; ++i) {
      v[i][to] += v[i][from];
    }
  }
  void addCol2(int from, int to) {
    v[N][to]++; 
  }

  // For s op.
  void swapCol(int c1, int c2) {
    for (int i = 0; i < row; ++i) {
      int tmp = v[i][c1];
      v[i][c1] = v[i][c2];
      v[i][c2] = tmp;
    }
  }

  // For e op.
  void clearCol(int c) {
    for (int i = 0; i < row; ++i) {
      v[i][c] = 0;
    }
  }
};

Matrix MulBad(const Matrix& A, const Matrix& B) {
  Matrix res(A.row, B.col);
  for (int i = 0; i < A.row; ++i) {
    for (int j = 0; j < B.col; ++j) {
      for (int k = 0; k < A.col; ++k) {
        res.v[i][j] = res.v[i][j] + A.v[i][k] * B.v[k][j];
      }
    }
  }
  return res;
}

Matrix Mul(const Matrix& A, const Matrix& B) {
  Matrix res(A.row, B.col);
  for (int i = 0; i < A.row; ++i) {
    for (int k = 0; k < A.col; ++k) {
      if (A.v[i][k] != 0) {
        for (int j = 0; j < B.col; ++j) {
          res.v[i][j] += A.v[i][k] * B.v[k][j];
        }
      }
    }
  }
  return res;
}

void solve() {
  Matrix P(N + 1, N + 1);  // The last col is for g op (add 1 peanut).
  for (int i = 0; i < N + 1; ++i) {
    P.v[i][i] = 1;
  }
  for (int i = 0; i < K; ++i) {
    if (ops[i].op == 'g') {
      P.addCol2(N, ops[i].a - 1);
    } else if (ops[i].op == 'e') {
      P.clearCol(ops[i].a - 1);
    } else {
      P.swapCol(ops[i].a - 1, ops[i].b - 1);
    }
  }
  /*
  for (int i = 0; i < P.row; ++i) {
    for (int j = 0; j < P.col; ++j) {
      printf("P.v[%d][%d] = %lld\n", i, j, P.v[i][j]);
    }
  }
  */
  Matrix B(N + 1, N + 1);
  for (int i = 0; i < N + 1; ++i) {
    B.v[i][i] = 1;
  }
  int i = M;
  while (i != 0) {
    if (i & 1) {
      B = Mul(B, P);
    }
    P = Mul(P, P);
    i >>= 1;
  }
  Matrix A(1, N + 1);
  A.v[0][N] = 1;
  A = Mul(A, B);
  for (int i = 0; i < N; ++i) {
    printf("%lld%c", A.v[0][i], (i < N - 1) ? ' ' : '\n');
  }
}

int main() {
  freopen("TrainingLittleCats.in", "r", stdin);
  while (scanf("%d%d%d", &N, &M, &K) == 3 && !(N == 0 && M == 0 && K == 0)) {
    char s[10];
    for (int i = 0; i < K; ++i) {
      scanf("%s", s);
      ops[i].op = s[0];
      if (s[0] == 'g') {
        scanf("%d", &ops[i].a);
      } else if (s[0] == 's') {
        scanf("%d%d", &ops[i].a, &ops[i].b);
      } else if (s[0] == 'e') {
        scanf("%d", &ops[i].a);
      }
    }
    solve();
  }
  return 0;
}
