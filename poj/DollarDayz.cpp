#include <stdio.h>

#include <string>
#include <vector>

using namespace std;

class BigInt {
 public:
  static BigInt getOne();
  void add(const BigInt& b);
  string toString() const;
 
 private:
  static const int DIGITS = 9;
  static const unsigned LIMIT = 1000000000;
  vector<unsigned> data;
};

BigInt BigInt::getOne() {
  BigInt ret;
  ret.data.resize(1, 1);
  return ret;
}

void BigInt::add(const BigInt& b) {
  unsigned add = 0;
  size_t i;
  for (i = 0; i < data.size() && i < b.data.size(); ++i) {
    add += data[i] + b.data[i];
    data[i] = add % LIMIT;
    add /= LIMIT;
  }
  for (; i < b.data.size(); ++i) {
    add += b.data[i];
    data.push_back(add % LIMIT);
    add /= LIMIT;
  }
  for (; i < data.size() && add != 0; ++i) {
    add += data[i];
    data[i] = add % LIMIT;
    add /= LIMIT;
  }
  while (add != 0) {
    data.push_back(add % LIMIT);
    add /= LIMIT;
  }
}

string BigInt::toString() const {
  string ret;
  char buf[20];
  for (int i = (int)data.size() - 1; i >= 0; --i) {
    if (i == (int)data.size() - 1) {
      snprintf(buf, sizeof(buf), "%d", data[i]);
    } else {
      snprintf(buf, sizeof(buf), "%0*d", DIGITS, data[i]);
    }
    ret += buf;
  }
  return ret;
}

int N, K;
BigInt dp[1001];

BigInt getCount() {
  dp[0] = BigInt::getOne();
  for (int i = 1; i <= K; ++i) {
    for (int j = i; j <= N; ++j) {
      dp[j].add(dp[j-i]);
    }
  }
  return dp[N];
}

int main() {
  freopen("DollarDayz.in", "r", stdin);
  scanf("%d%d", &N, &K);
  BigInt result = getCount();
  printf("%s\n", result.toString().c_str());
  return 0;
}
