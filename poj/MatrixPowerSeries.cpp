// POJ 3233
#include <stdio.h>
#include <string.h>

int N, K, M;

int a[30][30];

struct Matrix {
  int v[60][60];
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
  Matrix A(N, N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      A.v[i][j] = a[i][j];
    }
  }
  // [A^(k-1), Sk-1] * [A A] = [A^k, Sk]
  //                   [0 I]
  // [A, A] * [A A]^(k-1) = [A^k, Sk]
  //          [0 I]
  Matrix P(2*N, 2*N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      P.v[i][j] = P.v[i][j + N] = A.v[i][j];
    }
    P.v[i + N][i + N] = 1;
  }
  Matrix B(2*N, 2*N);
  for (int i = 0; i < 2*N; ++i) {
    B.v[i][i] = 1;
  }
  int k = K - 1;
  while (k != 0) {
    if (k & 1) {
      B = Mul(B, P);
    }
    P = Mul(P, P);
    k >>= 1;
  }
  Matrix init(N, 2*N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      init.v[i][j] = init.v[i][j + N] = A.v[i][j];
    }
  }
  Matrix res = Mul(init, B);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      printf("%d", res.v[i][j + N]);
      if (j < N - 1) {
        printf(" ");
      } else {
        printf("\n");
      }
    }
  }
}

int main() {
  freopen("MatrixPowerSeries.in", "r", stdin);
  scanf("%d%d%d", &N, &K, &M);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  solve();
  return 0;
}
