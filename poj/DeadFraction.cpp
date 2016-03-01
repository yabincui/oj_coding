#include <stdio.h>
#include <stdint.h>

#include <string>
#include <utility>
#include <vector>

using namespace std;

#define MASK 1000000000

#define dprintf(...)
//#define dprintf printf

class BigInt {
 public:
  BigInt() {
  }

  BigInt(uint32_t value) {
    if (value == 0) {
      v.push_back(0);
    } else {
      while (value != 0) {
        v.push_back(value % MASK);
        value /= MASK;
      }
    }
  }

  BigInt Add(const BigInt& other) const {
    BigInt res;
    uint32_t carry = 0;
    uint32_t tmp;
    int i;
    for (i = 0; i < v.size() && i < other.v.size(); ++i) {
      tmp = v[i] + other.v[i] + carry;
      if (tmp >= MASK) {
        tmp -= MASK;
        carry = 1;
      } else {
        carry = 0;
      }
      res.v.push_back(tmp);
    }
    for (; i < v.size(); ++i) {
      tmp = carry + v[i];
      if (tmp >= MASK) {
        tmp -= MASK;
        carry = 1;
      } else {
        carry = 0;
      }
      res.v.push_back(tmp);
    }
    for (; i < other.v.size(); ++i) {
      tmp = carry + other.v[i];
      if (tmp >= MASK) {
        tmp -= MASK;
        carry = 1;
      } else {
        carry = 0;
      }
      res.v.push_back(tmp);
    }
    if (carry == 1) {
      res.v.push_back(1);
    }
    dprintf("%s + %s = %s\n", Str().c_str(), other.Str().c_str(), res.Str().c_str());
    return res;
  }

  BigInt Mul(int value) const {
    BigInt res;
    uint64_t mul = value;
    uint64_t carry = 0;
    uint64_t sum;
    int i;
    for (i = 0; i < v.size(); ++i) {
      sum = carry + v[i] * mul;
      res.v.push_back(sum % MASK);
      carry = sum / MASK;
      dprintf("carry = %llu, sum = %llu\n", carry, sum);
    }
    while (carry != 0) {
      res.v.push_back(carry % MASK);
      carry /= MASK;
    }
    dprintf("%s * %d = %s\n", Str().c_str(), value, res.Str().c_str());
    return res;
  }

  BigInt Mul(const BigInt& other) const {
    BigInt res(0);
    BigInt Base = *this;
    for (int i = 0; i < other.v.size(); ++i) {
      int cur = other.v[i];
      if (cur != 0) {
        BigInt tmp = Base.Mul(cur);
        res = res.Add(tmp);
      }
      Base = Base.Mul(MASK);
    }
    return res;
  }

  int compare(const BigInt& other) const {
    if (v.size() != other.v.size()) {
      return v.size() - other.v.size();
    }
    for (int i = v.size() - 1; i >= 0; --i) {
      if (v[i] != other.v[i]) {
        return v[i] - other.v[i];
      }
    }
    return 0;
  }

  BigInt Sub(BigInt& other) const {
    BigInt res;
    int carry = 0;
    int tmp;
    int i;
    for (i = 0; i < v.size() && i < other.v.size(); ++i) {
      int tmp = v[i] - other.v[i] - carry;
      if (tmp < 0) {
        tmp += MASK;
        carry = 1;
      } else {
        carry = 0;
      }
      res.v.push_back(tmp);
    }
    for (; i < v.size(); ++i) {
      tmp = v[i] - carry;
      if (tmp < 0) {
        tmp += MASK;
        carry = 1;
      } else {
        carry = 0;
      }
      res.v.push_back(tmp);
    }
    for (; i < other.v.size(); ++i) {
      tmp = -other.v[i]-carry; 
      if (tmp < 0) {
        tmp += MASK;
        carry = 1;
      } else {
        carry = 0;
      }
      res.v.push_back(tmp);
    }
    int last_nonzero = res.v.size() - 1;
    while (last_nonzero > 0 && res.v[last_nonzero] == 0) {
      last_nonzero--;
    }
    res.v.resize(last_nonzero + 1);
    return res;
  }

  pair<BigInt, BigInt> Div(const BigInt& other) const {
    BigInt div(0);
    BigInt rem = *this;
    BigInt cur = other;
    int mul_count = 0;
    vector<BigInt> bases;
    while (rem.compare(cur) >= 0) {
      bases.push_back(cur);
      cur = cur.Add(cur);
    }
    for (int i = (int)bases.size() - 1; i >= 0; --i) {
      div = div.Add(div);
      if (rem.compare(bases[i]) >= 0) {
        rem = rem.Sub(bases[i]);
        div = div.Add(BigInt(1));
      }
    }
    dprintf("%s / %s = %s, rem %s\n", Str().c_str(), other.Str().c_str(), div.Str().c_str(), rem.Str().c_str());
    return make_pair(div, rem);
  }

  void Swap(BigInt& other) {
    swap(v, other.v);
  }

  std::string Str() const {
    std::string s;
    char buf[20];
    for (int i = v.size() - 1; i >= 0; --i) {
      if (i == v.size() - 1) {
        snprintf(buf, sizeof(buf), "%d", v[i]);
      } else {
        snprintf(buf, sizeof(buf), "%09d", v[i]);
      }
      s.append(buf);
    }
    return s;
  }

 private:
  vector<uint32_t> v;
};

BigInt zero(0);
BigInt one(1);

BigInt Gcd(BigInt a, BigInt b) {
  if (a.compare(b) < 0) {
    a.Swap(b);
  }
  if (b.compare(zero) == 0) {
    return a;
  }
  BigInt c = a.Div(b).second;
  while (c.compare(zero) != 0) {
    a = b;
    b = c;
    c = a.Div(b).second;
  }
  return b;
}

char s[8192];

pair<BigInt, BigInt> getBest() {
  int len = 0;  
  for (int i = 2; s[i] != '.'; ++i) {
    len++;
  }
  char* p = s + 2;
  BigInt bestNo, bestDeno;
  for (int t = 0; t < len; ++t) {
    int k = len - t;
    BigInt A(0), M(0);
    BigInt ten_k_minus_1(1), ten_t(1);
    for (int i = 0; i < t; ++i) {
      A = A.Mul(10).Add(BigInt(p[i] - '0'));
      ten_t = ten_t.Mul(10);
    }
    for (int i = t; i < len; ++i) {
      M = M.Mul(10).Add(BigInt(p[i] - '0'));
      ten_k_minus_1 = ten_k_minus_1.Mul(10);
    }
    ten_k_minus_1 = ten_k_minus_1.Sub(one);
    BigInt No = M.Add(ten_k_minus_1.Mul(A));
    BigInt Deno = ten_k_minus_1.Mul(ten_t);
    BigInt gcd = Gcd(No, Deno);
    dprintf("A = %s, M = %s, ten_k_minus_1 = %s, ten_t = %s\n", A.Str().c_str(), M.Str().c_str(),
          ten_k_minus_1.Str().c_str(), ten_t.Str().c_str());
    dprintf("No = %s, Deno = %s, gcd = %s\n", No.Str().c_str(), Deno.Str().c_str(), gcd.Str().c_str());
    No = No.Div(gcd).first;
    Deno = Deno.Div(gcd).first;
    if (t == 0 || Deno.compare(bestDeno) < 0) {
      bestNo = No;
      bestDeno = Deno;
    }
  }
  return make_pair(bestNo, bestDeno);
}

uint64_t Gcd(uint64_t a, uint64_t b) {
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

pair<uint64_t, uint64_t> getBest64() {
  int len = 0;
  char* p = s + 2;
  uint64_t all = 0;
  vector<uint64_t> tens(1, 1);
  uint64_t cur = 1;
  for (int i = 0; p[i] != '.'; ++i) {
    len++;
    all = all * 10 + (p[i] - '0');
    cur *= 10;
    tens.push_back(cur);
  }
  uint64_t bestNo, bestDeno;
  uint64_t A = 0;
  uint64_t M = all;
  for (int t = 0; t < len; ++t) {
    int k = len - t;
    uint64_t ten_k_minus_1 = tens[k] - 1;
    uint64_t ten_t = tens[t];
    uint64_t No = M + ten_k_minus_1 * A;
    uint64_t Deno = ten_k_minus_1 * ten_t;
    uint64_t gcd = Gcd(No, Deno);
    No /= gcd;
    Deno /= gcd;
    if ( t== 0 || Deno < bestDeno) {
      bestNo = No;
      bestDeno = Deno;
    }
    A = A * 10 + (p[t] - '0');
    M = M - tens[k - 1] * (p[t] - '0');
  }
  return make_pair(bestNo, bestDeno);
}

int main() {
  freopen("DeadFraction.in", "r", stdin);
  while (fgets(s, sizeof(s), stdin) != NULL) {
    if (s[0] == '0' && s[1] != '.') {
      break;
    }
    /*
    pair<BigInt, BigInt> result = getBest();
    printf("%s/%s\n", result.first.Str().c_str(), result.second.Str().c_str());
    */
    pair<uint64_t, uint64_t> result = getBest64();
    printf("%llu/%llu\n", result.first, result.second);
  }
  return 0;
}
