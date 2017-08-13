class Solution {
    
    void printArray(vector<int>& s) {
        printf("s = ");
        for (auto n : s) {
            printf("%d ", n);
        }
        printf("\n");
    }
    
    bool check(vector<int>& s) {
        for (int i = 0; i < s.size(); ++i) {
            int prev2 = i > 1 ? min(s[i-1], s[i-2]) : 0;
            int next2 = i + 2 < s.size() ? min(s[i+1], s[i+2]) : 0;
            int prev_next = (i > 0 && i + 1 < s.size()) ? min(s[i-1], s[i+1]) : 0;
            int prev_next_plus = i > 1 ? min(s[i-1] - prev_next, s[i-2]) : 0;
            prev_next_plus += i + 1 < s.size() ? min(s[i+1] - prev_next, s[i+2]) : 0;
            int limit = max(prev2 + next2, prev_next + prev_next_plus);
            if (s[i] > limit) {
                //printArray(s);
                return false;
            }
        }
        return true;        
    }
    
    bool check2(vector<int>& s) {
        if (s.size() < 3) return false;
        vector<int> t = s;
        for (int i = 0; i < s.size(); ++i) {
            if (i + 2 < s.size()) {
                int need = s[i] - (i > 0 ? s[i-1] : 0);
                if (t[i + 1] < need || t[i + 2] < need) {
                    return false;
                }
                t[i + 2] -= need;
            } else {
                if (s[i] > s[i-1]) {
                    return false;
                }
            }
        }
        return true;
    }
    
public:
    bool isPossible1(vector<int>& nums) {
        vector<int> countArray;
        int current;
        for (int num : nums) {
            if (countArray.empty()) {
                countArray.push_back(1);
                current = num;
            } else if (current == num) {
                countArray.back()++;
            } else if (current == num - 1) {
                current++;
                countArray.push_back(1);
            } else {
                if (!check(countArray)) return false;
                countArray.clear();
                countArray.push_back(1);
                current = num;
            }
        }
        if (!countArray.empty()) return check(countArray);
        return true;
    }
    
    bool isPossible(vector<int>& nums) {
        vector<int> countArray;
        int current;
        for (int num : nums) {
            if (countArray.empty()) {
                countArray.push_back(1);
                current = num;
            } else if (current == num) {
                countArray.back()++;
            } else if (current == num - 1) {
                current++;
                countArray.push_back(1);
            } else {
                if (!check2(countArray)) return false;
                countArray.clear();
                countArray.push_back(1);
                current = num;
            }
        }
        if (!countArray.empty()) return check2(countArray);
        return true;
    }
};
