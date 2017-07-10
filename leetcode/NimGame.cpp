class Solution {
public:
    bool canWinNim(int n) {
        
        // false true true ture false true true true false true true true.
        
        n %= 4;
        if (n == 0) return false;
        return true;
    }
};
