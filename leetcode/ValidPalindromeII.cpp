class Solution {
    
    bool isPalindrome(string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
    
public:
    bool validPalindrome(string s) {
        int n = s.size();
        if (n <= 2) return true;
        int left = 0;
        int right = n - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                if (isPalindrome(s, left, right - 1) || isPalindrome(s, left + 1, right)) {
                    return true;
                }
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};
