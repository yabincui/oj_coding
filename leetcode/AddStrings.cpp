// 415. Add Strings
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class BigInt {
public:
	BigInt() {}
	BigInt(const string& s) {
		for (auto& c : s) {
			vals_.push_back(c - '0');
		}
		reverse(vals_.begin(), vals_.end());
	}

	BigInt operator+(const BigInt& o) {
		BigInt res;
		int add = 0;
		for (size_t i = 0; i < vals_.size() || i < o.vals_.size() || add != 0; ++i) {
			if (i < vals_.size()) {
				add += vals_[i];
			}
			if (i < o.vals_.size()) {
				add += o.vals_[i];
			}
			res.vals_.push_back(add % 10);
			add /= 10;
		}
		return res;
	}

	string toString() {
		string s;
		for (auto& v : vals_) {
			s.push_back(v + '0');
		}
		reverse(s.begin(), s.end());
		return s;
	}

private:
	vector<int> vals_;
};


class Solution {
public:
    string addStrings(string num1, string num2) {
        BigInt a(num1);
        BigInt b(num2);
        return (a+b).toString();
    }
};
