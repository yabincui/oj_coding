#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <vector>

using namespace std;

uint64_t best_a, best_b, best_sum;


const int MAX_PRIME = 200000;
bool is_prime[MAX_PRIME + 1];
vector<int> primes;

void initPrimes() {
  memset(is_prime, true, sizeof(is_prime));
  is_prime[0] = is_prime[1] = false;
  for (int i = 0; i <= MAX_PRIME; ++i) {
    if (is_prime[i]) {
      for (int j = i + i; j <= MAX_PRIME; j += i) {
        is_prime[j] = false;
      }
      primes.push_back(i);
    }
  }
}

// Split using division, O(n^0.5)
vector<uint64_t> split(uint64_t value) {
  vector<uint64_t> v;
  unsigned half = (unsigned)sqrt(value);
  uint64_t t = 1;
  while (value % 2 == 0) {
    t *= 2;
    value /= 2;
  }
  if (t != 1) {
    v.push_back(t);
  }
  for (unsigned i = 3; i <= half && value != 1; i += 2) {
    if (value % i == 0) {
      uint64_t t = 1;
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

uint64_t modularMul(uint64_t a, uint64_t b, uint64_t n) {
  uint64_t res = 0;
  a %= n;
  uint64_t base = a;
  while (b != 0) {
    if (b & 1) {
      res = (res + base) % n;
    }
    b >>= 1;
    base = (base << 1) % n;
  }
  return res;
}

uint64_t modularExp(uint64_t a, uint64_t b, uint64_t n) {
  uint64_t res = 1;
  a %= n;
  uint64_t base = a;
  while (b != 0) {
    if (b & 1) {
      res = modularMul(res, base, n);
    }
    b >>= 1;
    base = modularMul(base, base, n);
  }
  return res;
}

bool witness(uint32_t a, uint64_t u, int t, uint64_t n) {
  // n - 1 = 2^t * u
  uint64_t x = modularExp(a, u, n);
  for (int i = 1; i <= t; ++i) {
    uint64_t x2 = modularMul(x, x, n);
    if (x2 == 1 && x != 1 && x != n - 1) {
      return true;
    }
    x = x2;
  }
  if (x != 1) {
    return true;
  }
  return false;
}

bool isPrime(uint64_t value) {
  if (value % 2 == 0) {
    return (value == 2);
  }
  if (value <= MAX_PRIME) {
    return is_prime[value];
  }
  uint64_t u = value - 1;
  int t = 0;
  while (!(u & 1)) {
    u >>= 1;
    t++;
  }
  for (int i = 1; i < 50; ++i) {
    uint64_t a = rand() % (value - 2) + 2;
    if (witness(a, u, t, value)) {
      return false;
    }
  }
  return true;
}

uint64_t gcd2(uint64_t a, uint64_t b) {
  if (a < b) {
    swap(a, b);
  }
  if (b == 0) {
    return a;
  }
  uint64_t c = a % b;
  while (c != 0) {
    a = b;
    b = c;
    c = a % b;
  }
  return b;
}

uint64_t getFactor(uint64_t n) {
  for (int c = 1; ; ++c) {
    uint64_t x = 2;
    uint64_t y = 2;
    uint64_t k = 2;
    uint64_t d = 1;

    while (d == 1) {
      x = (modularMul(x, x, n) + c) % n;
      y = (modularMul(y, y, n) + c) % n;
      y = (modularMul(y, y, n) + c) % n;
      uint64_t diff = (y > x) ? y - x : x - y;
      d = gcd2(diff, n);
    }
    if (d != n) {
      return d;
    }
  }
}

map<uint64_t, uint64_t> factor_map;

void smartSplit(uint64_t n) {
  if (n == 1) {
    return;
  }
  if (isPrime(n)) {
    uint64_t a = factor_map[n];
    if (a == 0) {
      a = 1;
    }
    factor_map[n] = a * n;
    return;
  }
  uint64_t d = getFactor(n);
  smartSplit(d);
  smartSplit(n / d);
}

vector<uint64_t> optimizedSplit(uint64_t value) {
  vector<uint64_t> v;
  factor_map.clear();
  for (int i = 0; i < primes.size(); ++i) {
    if (value % primes[i] == 0) {
      uint64_t a = 1;
      uint64_t d = primes[i];
      while (value % d == 0) {
        a *= d;
        value /= d;
      }
      factor_map[d] = a;
    }
  }

  smartSplit(value);
  for (map<uint64_t, uint64_t>::iterator it = factor_map.begin(); it != factor_map.end(); ++it) {
    v.push_back(it->second);
  }
  return v;
}

struct Pos {
  uint64_t a;
  uint64_t b;
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

void permute(const vector<uint64_t>& v, Pos pos) {
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
  uint64_t gc, cm;
  initPrimes();
  while (scanf("%llu%llu", &gc, &cm) == 2) {
    if (gc == cm) {
      printf("%llu %llu\n", gc, cm);
      continue;
    }
    uint64_t d = cm / gc;
    
    vector<uint64_t> v = optimizedSplit(d);
    sort(v.begin(), v.end());

    best_a = 1;
    best_b = d;
    best_sum = d + 1;
    Pos pos;
    pos.k = 0;
    pos.a = 1;
    pos.b = 1;
    hit_set.clear();
    permute(v, pos);

    printf("%llu %llu\n", best_a * gc, best_b * gc);
  }
  return 0;
}
