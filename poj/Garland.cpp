#include <stdio.h>

#include <iostream>
#include <iomanip>

using namespace std;

int N;
double A;

int e2[1001];
int e1[1001];
int e0[1001];

bool isOk(double B) {
  double x2 = (B - e0[N] - e1[N] * A) / e2[N];
  if (x2 < 0) {
    return false;
  }
  for (int i = 3; i < N; ++i) {
    double x = e2[i] * x2 + e1[i] * A + e0[i];
    if (x < 0) {
      return false;
    }
  }
  return true;
}

double getMinB() {
  // x1 = 0 * x2 + 1 * x1 + 0.
  e2[1] = 0;
  e1[1] = 1;
  e0[1] = 0;
  // x2 = 1 * x2 + 0 * x1 + 0.
  e2[2] = 1;
  e1[2] = 0;
  e0[2] = 0;
  for (int t = 3; t <= N; ++t) {
    // xt = 2 * x(t-1) - x(t-2) + 2.
    e2[t] = e2[t-1] * 2 - e2[t-2];
    e1[t] = e1[t-1] * 2 - e1[t-2];
    e0[t] = e0[t-1] * 2 - e0[t-2] + 2;
  }
  double low = 0.0;
  // Use all ways up as high limit of B.
  double high = e2[N] * A + e1[N] * A + e0[N];
  //printf("low = %lf, high = %lf\n", low, high);
  while (high - low > 1e-6) {
    double mid = (low + high) / 2;
    if (isOk(mid)) {
      high = mid;
    } else {
      low = mid;
    }
  }
  return high;
}

double B;

bool isX2Ok(double x2) {
  double prev = A;
  double cur = x2;
  for (int i = 3; i <= N; ++i) {
    double next = 2 * cur + 2 - prev;
    if (next < 0) {
      return false;
    }
    prev = cur;
    cur = next;
  }
  B = cur;
  return true;
}

double getMinB2() {
  double low = -1.0;
  double high = A;
  for (int i = 0; i < 1000; ++i) {
    double mid = (low + high) / 2;
    if (isX2Ok(mid)) {
      high = mid;
    } else {
      low = mid;
    }
  }
  return B;
}

double H[1001];

bool C(double mid) {
  H[1] = A;
  H[2] = mid;
  for (int i = 3; i <= N; ++i) {
    H[i] = 2 * H[i-1] + 2 - H[i-2];
    if (H[i] < 0) {
      return false;
    }
  }
  B = H[N];
  return true;
}

double getMinB3() {
  double low = -1, high = 1000 + 16;
  for (int i = 0; i < 100; ++i) {
    double mid = (low + high) / 2;
    if (C(mid)) {
      high = mid;
    } else {
      low = mid;
    }
  }
  return B;
}


int main() {
  freopen("Garland.in", "r", stdin);
  scanf("%d%lf", &N, &A);
  double result = getMinB3();
  printf("%.2f\n", result);
  return 0;
}

/*
int main() {
  freopen("Garland.in", "r", stdin);
  cin >> N >> A;
  double result = getMinB();
  cout << fixed << setprecision(2) << result << endl;
  return 0;
}
*/
