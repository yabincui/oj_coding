class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> visited;
        while (n != 1) {
            visited.insert(n);
            int next = 0;
            while (n != 0) {
                next += (n%10) * (n%10);
                n /= 10;
            }
            n = next;
            if (visited.find(n) != visited.end()) {
                break;
            }
        }
        return n == 1;
    }
};
