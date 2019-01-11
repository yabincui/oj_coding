#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long ll;

//#define dprintf printf
#define dprintf

class LineReader {
public:
    LineReader() : buffer(NULL), buffer_size(0) {}

    ~LineReader() {
        if (buffer) free(buffer);
    }

    string getLine() {
        if (getline(&buffer, &buffer_size, stdin) <= 0) {
            return "";
        }
        return string(buffer);
    }

    char* buffer;
    size_t buffer_size;
};

// Select 6 rounds for the first six categories, C(13, 6) = 1716.
// For each case:
//   6! + 7! = 5760, about 10^7.

// If using DP, MaxScore(13, available_round_mask) =
//    select a round for nums 13 + MaxScore(12, available_round_mask).
// 2^13 * 13 * 13 = 8K * 100 = 10^6.
// You don't need to enumerate two.


class Solution {
private:
    struct Node {
        int s[13];
        int ids[13];
        int max_sum;
    };

public:
    void solve(vector<vector<int>>& nums) {
        for (auto& s : nums) {
            sort(s.begin(), s.end());
        }
        this->nums = nums;
        calculateValues();
        best.max_sum = -1;
        vector<bool> used(13, false);
        partition(0, 0, used);
        printBest();
    }

private:

    void calculateValues() {
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 13; ++j) {
                values[i][j] = getValue(nums[i], j);
                printf("values[%d][%d] = %d\n", i, j, values[i][j]);
            }
        }
    }

    int getValue(vector<int>& s, int category) {
        int sum = 0;
        if (category < 6) {
            int need_value = category + 1;
            for (auto& n : s) {
                if (n == need_value) {
                    sum += n;
                }
            }
        } else if (category == 6) {
            sum = accumulate(s.begin(), s.end(), 0);
        } else if (category == 7) {
            if (isSame(&s[0], &s[2]) || isSame(&s[1], &s[3]) || isSame(&s[2], &s[4])) {
                sum = accumulate(s.begin(), s.end(), 0);
            }
        } else if (category == 8) {
            if (isSame(&s[0], &s[3]) || isSame(&s[1], &s[4])) {
                sum = accumulate(s.begin(), s.end(), 0);
            }
        } else if (category == 9) {
            if (isSame(&s[0], &s[4])) {
                sum = 50;
            }
        } else if (category == 10) {
            if (getIncrementLength(s) >= 4) {
                sum = 25;
            }
        } else if (category == 11) {
            if (getIncrementLength(s) == 5) {
                sum = 35;
            }
        } else {
            if (isSame(&s[0], &s[1]) && isSame(&s[2], &s[4]) ||
                  isSame(&s[0], &s[2]) && isSame(&s[3], &s[4])) {
                sum = 40;
            }
        }
        return sum;
    }

    bool isSame(int* begin, int* end) {
        while (begin != end) {
            if (*begin != *end) {
                return false;
            }
            begin++;
        }
        return true;
    }

    int getIncrementLength(vector<int>& s) {
        int res = 0;
        for (int begin = 0; begin < s.size(); ++begin) {
            int need = s[begin] + 1;
            for (int i = begin + 1; i < s.size(); ++i) {
                if (s[i] == need) {
                    need++;
                }
            }
            res = max(need - s[begin], res);
            //dprintf("getIncrementLength res = %d\n", res);
        }
        return res;
    }

    void partition(int pos, int start, vector<bool>& used) {
        if (pos == 6) {
            vector<int> s1, s2;
            splitNums(used, s1, s2);
            Node b1 = findSubBest(s1, 0);
            Node b2 = findSubBest(s2, 6);
            Node result = combineResult(b1, b2);
            /*
            if (s1 == vector<int>({1, 4, 8, 10, 11, 12})) {
                printf("b1.sum = %d, b2.sum = %d, result = %d\n", b1.max_sum, b2.max_sum, result.max_sum);
            }
            */
            if (result.max_sum > best.max_sum) {
                best = result;
            }
            return;
        }
        for (int i = start; i <= 12; ++i) {
            if (!used[i]) {
                used[i] = true;
                partition(pos + 1, i + 1, used);
                used[i] = false;
            }
        }
    }

    void splitNums(vector<bool>& used, vector<int>& s1, vector<int>& s2) {
        for (int i = 0; i < used.size(); ++i) {
            if (used[i]) {
                s1.push_back(i);
            } else {
                s2.push_back(i);
            }
        }
    }

    // Now we have 6 numbers, assign that to 6 categories, 13 * 13.
    Node findSubBest(vector<int>& num_ids, int start) {
        vector<int> order;
        for (int i = 0; i < num_ids.size(); ++i) {
            order.push_back(i + start);
        }

        bool match = false;

        Node subBest;
        subBest.max_sum = -1;
        do {
            int sum = 0;
            for (int i = 0; i < order.size(); ++i) {
                sum += values[num_ids[i]][order[i]];
            }
            //printf("start = %d, sum = %d\n", start, sum);
            if (sum > subBest.max_sum) {
                subBest.max_sum = sum;
                for (int i = 0; i < order.size(); ++i) {
                    subBest.ids[order[i]] = num_ids[i];
                }
            }
        } while (next_permutation(order.begin(), order.end()));
        return subBest;
    }

    Node combineResult(Node& n1, Node& n2) {
        Node result;
        for (int i = 0; i < 6; ++i) {
            result.s[i] = values[n1.ids[i]][i];
            result.ids[i] = n1.ids[i];
        }
        for (int i = 6; i < 13; ++i) {
            result.s[i] = values[n2.ids[i]][i];
            result.ids[i] = n2.ids[i];
        }
        result.max_sum = n1.max_sum + n2.max_sum;
        if (accumulate(&result.s[0], &result.s[6], 0) >= 63) {
            result.max_sum += 35;
        }
        return result;
    }

    void printBest() {
        int sum6 = 0;
        for (int i = 0; i < 13; ++i) {
            printf("%d ", best.s[i]);
            if (i < 6) {
                sum6 += best.s[i];
            }
        }
        printf("%d ", sum6 >= 63 ? 35 : 0);
        printf("%d\n", best.max_sum);
    }

    int values[13][13];
    vector<vector<int>> nums;
    Node best;
};

class SolutionDP {
private:
    struct Node {
        int s[13];
        int max_sum;
    };

    // dp[i][j], i means 0..i categories has been used,
    // j means j bit mask nums are still available.
    static Node dp[13][1 << 13];
    Node best;

public:
    void solve(vector<vector<int>>& nums) {
        for (auto& s : nums) {
            sort(s.begin(), s.end());
        }
        this->nums = nums;
        calculateValues();
        findBest();
        printBest();
    }

    void printBest() {
        int sum6 = 0;
        for (int i = 0; i < 13; ++i) {
            printf("%d ", best.s[i]);
            if (i < 6) {
                sum6 += best.s[i];
            }
        }
        printf("%d ", sum6 >= 63 ? 35 : 0);
        printf("%d\n", best.max_sum);
    }

private:

    void findBest() {
        int mask = (1 << 13) - 1;
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j <= mask; ++j) {
                if (getBits(j) != i + 1) {
                    continue;
                }
                dp[i][j].max_sum = -1;
                for (int k = 0; k <= 12; ++k) {
                    if ((j & (1 << k)) == 0) {
                        continue;
                    }
                    int add = values[k][i];
                    int prev = 0;
                    if (i > 0) {
                        prev = dp[i-1][j & ~(1 << k)].max_sum;
                    }
                    if (i == 5 && prev + add >= 63) {
                        prev += 35;
                    }
                    if (add + prev > dp[i][j].max_sum) {
                        dp[i][j].max_sum = add + prev;
                        if (i > 0) {
                            memcpy(dp[i][j].s, dp[i-1][j & ~(1 << k)].s, sizeof(dp[i][j].s));
                        }
                        dp[i][j].s[i] = add;
                    }
                }
                if (i == 5 && (j & 2) != 0) {
                    dprintf("dp[%d][%d] = %d\n", i, j, dp[i][j].max_sum);
                }
            }
        }
        best = dp[12][mask];
    }

    int getBits(int i) {
        int bits = 0;
        while (i) {
            bits++;
            i &= i - 1;
        }
        return bits;
    }

    void calculateValues() {
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 13; ++j) {
                values[i][j] = getValue(nums[i], j);
                //printf("values[%d][%d] = %d\n", i, j, values[i][j]);
            }
        }
    }

    int getValue(vector<int>& s, int category) {
        int sum = 0;
        if (category < 6) {
            int need_value = category + 1;
            for (auto& n : s) {
                if (n == need_value) {
                    sum += n;
                }
            }
        } else if (category == 6) {
            sum = accumulate(s.begin(), s.end(), 0);
        } else if (category == 7) {
            if (isSame(&s[0], &s[2]) || isSame(&s[1], &s[3]) || isSame(&s[2], &s[4])) {
                sum = accumulate(s.begin(), s.end(), 0);
            }
        } else if (category == 8) {
            if (isSame(&s[0], &s[3]) || isSame(&s[1], &s[4])) {
                sum = accumulate(s.begin(), s.end(), 0);
            }
        } else if (category == 9) {
            if (isSame(&s[0], &s[4])) {
                sum = 50;
            }
        } else if (category == 10) {
            if (getIncrementLength(s) >= 4) {
                sum = 25;
            }
        } else if (category == 11) {
            if (getIncrementLength(s) == 5) {
                sum = 35;
            }
        } else {
            if (isSame(&s[0], &s[1]) && isSame(&s[2], &s[4]) ||
                  isSame(&s[0], &s[2]) && isSame(&s[3], &s[4])) {
                sum = 40;
            }
        }
        return sum;
    }

    bool isSame(int* begin, int* end) {
        while (begin != end) {
            if (*begin != *end) {
                return false;
            }
            begin++;
        }
        return true;
    }

    int getIncrementLength(vector<int>& s) {
        int res = 0;
        for (int begin = 0; begin < s.size(); ++begin) {
            int need = s[begin] + 1;
            for (int i = begin + 1; i < s.size(); ++i) {
                if (s[i] == need) {
                    need++;
                }
            }
            res = max(need - s[begin], res);
            //dprintf("getIncrementLength res = %d\n", res);
        }
        return res;
    }

    int values[13][13];
    vector<vector<int>> nums;
};

SolutionDP::Node SolutionDP::dp[13][1<<13];

int main() {
    freopen("Yahtzee.in", "r", stdin);
    LineReader reader;
    while (true) {
        string s = reader.getLine();
        if (s.empty() || s == "\n") {
            break;
        }
        vector<vector<int>> nums;
        for (int i = 1; i <= 13; ++i) {
            vector<int> v(5);
            sscanf(s.c_str(), "%d%d%d%d%d", &v[0], &v[1], &v[2], &v[3], &v[4]);

            if (i < 13) {
                s = reader.getLine();
            }
            nums.push_back(v);
        }
        SolutionDP solution;
        solution.solve(nums);
    }
}