class Solution {
    
    int m, n;
    
    int getRowLess(int key, int row) {
        if (row * n < key) {
            return n;
        }
        if (row >= key) {
            return 0;
        }
        int low = 1;
        int high = n - 1;
        while (low + 1 < high) {
            int mid = (low + high) / 2;
            if (mid * row < key) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        if (high * row < key) return high;
        return low;
    }
    
    int getLess(int key) {
        int count = 0;
        for (int r = 1; r <= m; ++r) {
            count += getRowLess(key, r);
        }
        return count;
    }
    
public:
    int findKthNumber(int m, int n, int k) {
        if (m > n) {
            swap(m, n);
        }
        this->m = m;
        this->n = n;
        int low = 1;
        int high = m * n;
        while (low + 1 < high) {
            int mid = low + (high - low) / 2;
            if (getLess(mid) < k) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        if (high == low) return high;
        if (getLess(high) >= k) {
            return low;
        }
        return high;
    }
};
