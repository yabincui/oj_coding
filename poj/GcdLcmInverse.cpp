#include <stdio.h>

#include <cmath>
#include <set>
#include <vector>

using namespace std;

unsigned long long best_a, best_b, best_sum;

vector<unsigned long long> split(unsigned long long value) {
  vector<unsigned long long> v;
  unsigned half = (unsigned)sqrt(value);
  unsigned long long t = 1;
  while (value % 2 == 0) {
    t *= 2;
    value /= 2;
  }
  if (t != 1) {
    v.push_back(t);
  }
  for (unsigned i = 3; i <= half && value != 1; i += 2) {
    if (value % i == 0) {
      unsigned long long t = 1;
      while (value % i == 0) {
        value /= i;
        t *= i;
      }
      v.push_back(t);
    }
  }
  if (value != 0) {
    v.push_back(value);
  }
  return v;
}

struct Pos {
  unsigned long a;
  unsigned long b;
  int k;

  bool operator<(const Pos& other) const {
    if (a != other.a) {
      return a < other.a;
    }
    if (b != other.b) {
      return b < other.b;
    }
    return k < other.k;
  }
};

set<Pos> hit_set;

void permute(const vector<unsigned long long>& v, Pos pos) {
  if (pos.a > pos.b) {
    swap(pos.a, pos.b);
  }
  if (hit_set.find(pos) != hit_set.end()) {
    return;
  }
  hit_set.insert(pos);
  if (pos.k == v.size()) {
    if (pos.a + pos.b < best_sum) {
      best_a = pos.a;
      best_b = pos.b;
      best_sum = pos.a + pos.b;
    }
    return;
  }
  pos.k++;
  pos.a *= v[pos.k - 1];
  permute(v, pos);
  pos.a /= v[pos.k - 1];
  pos.b *= v[pos.k - 1];
  permute(v, pos);
}

int main() {
  freopen("GcdLcmInverse.in", "r", stdin);
  unsigned long long gcd, lcm;
  while (scanf("%llu%llu", &gcd, &lcm) == 2) {
    if (gcd == lcm) {
      printf("%llu %llu\n", gcd, lcm);
      continue;
    }
    unsigned long long d = lcm / gcd;
    vector<unsigned long long> v = split(d);
    for (int i = 0; i < v.size(); ++i) {
      //printf("v[%d] = %llu\n", i, v[i]);
    }
    best_a = 1;
    best_b = d;
    best_sum = d + 1;
    Pos pos;
    pos.k = 0;
    pos.a = 1;
    pos.b = 1;
    hit_set.clear();
    permute(v, pos);
    printf("%llu %llu\n", best_a * gcd, best_b * gcd);
  }
  return 0;
}
