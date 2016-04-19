// POJ 3734

#include <stdio.h>

#define MOD 10007

int N;

struct Matrix {
  int v[2][2];

  Matrix(int a00, int a01, int a10, int a11) {
    v[0][0] = a00;
    v[0][1] = a01;
    v[1][0] = a10;
    v[1][1] = a11;
  }

  Matrix() {
    v[0][0] = v[0][1] = v[1][0] = v[1][1] = 0;
  }
};

Matrix Mul(const Matrix& A, const Matrix& B) {
  Matrix res;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 2; ++k) {
        res.v[i][j] = (res.v[i][j] + A.v[i][k] * B.v[k][j]) % MOD;
      }
    }
  }
  return res;
}

void solve() {
  // [2, 1] * [2 0 ]^(N-1)  = A  A[0][0] is the result. 
  //          [2 4 ]
  Matrix A(2, 0, 2, 4);
  Matrix B(1, 0, 0, 1);
  int i = N - 1;
  while (i != 0) {
    if (i & 1) {
      B = Mul(A, B);
    }
    A = Mul(A, A);
    i >>= 1;
  }
  int result = (2 * B.v[0][0] + B.v[1][0]) % MOD;
  printf("%d\n", result);
}

int main() {
  freopen("Blocks.in", "r", stdin);
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; ++t) {
    scanf("%d", &N);
    solve();
  }
  return 0;
}
