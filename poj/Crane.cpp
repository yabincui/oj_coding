#include <stdio.h>

#include <cmath>
#include <utility>
#include <vector>
using namespace std;

double PI;

int N, C;

int L[10000];
int s[10000];
int a[10000];

double X[10001];
double Y[10001];
int rel_ang[10001];

int AddAng(int ang1, int ang2) {
  return (ang1 + ang2) % 360;
}

int SubAng(int ang1, int ang2) {
  return (ang1 + 360 - ang2) % 360;
}

double toRadius(int ang) {
  if (ang > 180) {
    ang = -(360 - ang);
  }
  return ang * PI / 180;
}

double formatD(double d) {
  if (fabs(d) < 1e-8) {
    return 0.0;
  }
  return d;
}

void solve() {
  X[0] = 0;
  Y[0] = 0;
  rel_ang[0] = 0;
  for (int i = 1; i <= N; ++i) {
    X[i] = 0;
    Y[i] = L[i-1] + Y[i-1];
    rel_ang[i] = 180;
  }
  for (int i = 0; i < C; ++i) {
    int j = s[i];
    rel_ang[j] = a[i];
    int ang = 90;
    for (int k = 1; k < j; ++k) {
      ang = AddAng(SubAng(ang, 180), rel_ang[k]);
    }
    for (; j < N; ++j) {
      ang = AddAng(SubAng(ang, 180), rel_ang[j]);
      //printf("ang[%d] = %d\n", j, ang);
      //printf("Y[j] = %f, L[j] = %d, sin(%d) = %f\n", Y[j], L[j], ang, sin(toRadius(ang)));
      Y[j+1] = Y[j] + L[j] * sin(toRadius(ang));
      X[j+1] = X[j] + L[j] * cos(toRadius(ang));
    }
    printf("%.2f %.2f\n", formatD(X[N]), formatD(Y[N]));
  }
}

// rotate a vector (x0, y0) a degree a, the new vector (x1, y1) is (x0*cosa - y0*sina, y0*cosa + x0*sina).
pair<double, double> rotateVector(pair<double, double> v, int a) {
  double sin_a = sin(toRadius(a));
  double cos_a = cos(toRadius(a));
  double x = v.first;
  double y = v.second;
  return make_pair(x * cos_a - y * sin_a, y * cos_a + x * sin_a);
}

vector<pair<double, double> > vs;
void solve2() {
  vs.clear();
  for (int i = 0; i < N; ++i) {
    vs.push_back(make_pair<double, double>(0, L[i]));
  }
  for (int i = 1; i < N; ++i) {
    rel_ang[i] = 180;
  }
  for (int i = 0; i < C; ++i) {
    int j = s[i];
    int new_ang = a[i];
    int ang_diff = SubAng(new_ang, rel_ang[j]);
    rel_ang[j] = new_ang;
    for (; j < N; ++j) {
      vs[j] = rotateVector(vs[j], ang_diff);
    }
    double x = 0;
    double y = 0;
    for (int k = 0; k < N; ++k) {
      x += vs[k].first;
      y += vs[k].second;
      //printf("vs[%d] = %f, %f\n", i, vs[i].first, vs[i].second);
    }
    printf("%.2f %.2f\n", formatD(x), formatD(y));
  }
}

double vx[40000];
double vy[40000];
int todoRotate[40000];
int degree[10000];

void build(int root, int left, int right) {
  if (left == right) {
    // only one node.
    vx[root] = 0;
    vy[root] = L[left];
  } else {
    int mid = (left + right) / 2;
    build(root * 2 + 1, left, mid);
    build(root * 2 + 2, mid + 1, right);
    vx[root] = vx[root * 2 + 1] + vx[root * 2 + 2];
    vy[root] = vy[root * 2 + 1] + vy[root * 2 + 2];
  }
  todoRotate[root] = 0;
}

void updateAng(int root, int left, int right, int target, int ang_diff) {
  if (left == right) {
    int ang = todoRotate[root];
    todoRotate[root] = 0;
    if (left >= target) {
      ang = AddAng(ang, ang_diff);
    }
    if (ang != 0) {
      std::pair<double, double> p = rotateVector(make_pair(vx[root], vy[root]), ang);
      vx[root] = p.first;
      vy[root] = p.second;
    }
  } else {
    if (target <= left || target > right) {
      // update all.
      if (target <= left) {
        ang_diff = AddAng(todoRotate[root], ang_diff);
      } else {
        ang_diff = todoRotate[root];
      }
      todoRotate[root] = 0;
      std::pair<double, double> p = rotateVector(make_pair(vx[root], vy[root]), ang_diff);
      vx[root] = p.first;
      vy[root] = p.second;
      todoRotate[root * 2 + 1] = AddAng(todoRotate[root * 2 + 1], ang_diff);
      todoRotate[root * 2 + 2] = AddAng(todoRotate[root * 2 + 2], ang_diff);
    } else {
      todoRotate[root * 2 + 1] = AddAng(todoRotate[root * 2 + 1], todoRotate[root]);
      todoRotate[root * 2 + 2] = AddAng(todoRotate[root * 2 + 2], todoRotate[root]);
      todoRotate[root] = 0;
      int mid = (left + right) / 2;
      updateAng(root * 2 + 1, left, mid, target, ang_diff);
      updateAng(root * 2 + 2, mid + 1, right, target, ang_diff);
      vx[root] = vx[root * 2 + 1] + vx[root * 2 + 2];
      vy[root] = vy[root * 2 + 1] + vy[root * 2 + 2];
    }
  }
}

// Use segment tree to record vector change.
void solve3() {
  // build segment tree.
  build(0, 0, N - 1);
  for (int i = 1; i < N; ++i) {
    degree[i] = 180;
  }
  for (int i = 0; i < C; ++i) {
    int j = s[i];
    int diff = SubAng(a[i], degree[j]);
    degree[j] = a[i];
    updateAng(0, 0, N - 1, j, diff);
    printf("%.2f %.2f\n", formatD(vx[0]), formatD(vy[0]));
  }
}


int main() {
  freopen("Crane.in", "r", stdin);
  PI = atan(1) * 4;
  bool first = true;
  while (scanf("%d%d", &N, &C) == 2) {
    if (first) {
      first = false;
    } else {
      printf("\n");
    }
    for (int i = 0; i < N; ++i) {
      scanf("%d", &L[i]);
    }
    for (int i = 0; i < C; ++i) {
      scanf("%d%d", &s[i], &a[i]);
    }
    solve3();
  }
  return 0;
}
