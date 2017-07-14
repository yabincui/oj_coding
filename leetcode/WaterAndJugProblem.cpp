class Solution {
    
    int64_t getKey(int a, int b) {
        return ((int64_t)a << 32) | b;
    }
    
    void getAb(int64_t key, int& a, int& b) {
        a = key >> 32;
        b = key & 0xffffffff;
    }
    
    bool addKey(int a, int b, unordered_set<int64_t>& hit_set, queue<int64_t>& q, int z) {
        if (a == z || b == z || a + b == z) return true;
        int64_t key = getKey(a, b);
        if (hit_set.find(key) != hit_set.end()) {
            return false;
        }
        hit_set.insert(key);
        q.push(key);
        return false;
    }

    int64_t getKey32(int a, int b) {
        return ((int32_t)a << 16) | b;
    }
    
    void getAb32(int32_t key, int& a, int& b) {
        a = key >> 16;
        b = key & 0xffff;
    }
    
    bool addKey(int a, int b, unordered_set<int32_t>& hit_set, queue<int32_t>& q, int z) {
        if (a == z || b == z || a + b == z) return true;
        int32_t key = getKey32(a, b);
        if (hit_set.find(key) != hit_set.end()) {
            return false;
        }
        hit_set.insert(key);
        q.push(key);
        return false;
    }
    
    
    bool smallVersion(int x, int y, int z) {
        unordered_set<int32_t> hit_set;
        queue<int32_t> q;
        if (z == 0) return true;
        q.push(getKey32(0, 0));
        hit_set.insert(getKey32(0, 0));
        while (!q.empty()) {
            int a, b;
            int32_t key = q.front(); q.pop();
            getAb32(key, a, b);
            // fill a.
            bool ok = false;
            ok |= addKey(x, b, hit_set, q, z);
            // fill b.
            ok |= addKey(a, y, hit_set, q, z);
            // empty a.
            ok |= addKey(0, b, hit_set, q, z);
            // empty b.
            ok |= addKey(a, 0, hit_set, q, z);
            // pour a to b.
            int pour = min(a, y - b);
            ok |= addKey(a - pour, b + pour, hit_set, q, z);
            // pour b to a.
            pour = min(b, x - a);
            ok |= addKey(a + pour, b - pour, hit_set, q, z);
            if (ok) return true;
        }
        return false;
    }    

    
public:
    
    bool canMeasureWater(int x, int y, int z) {
        /*
            counterexample: 4, 5, 2.
            
            4 1    => 1
            1 5    =>  y - (x - cur = 3 , 2)
            4 2
        */
        
        if (x + y < z) {
            return false;
        }
        if (z == 0) return true;
        if (x == z || y == z) return true;
        if (x == y) return false;
        if (x == 0 || y == 0) return false;
        unordered_set<int> hit_set;
        queue<int> q;
        int cur = (x > y) ? x % y : y % x;
        hit_set.insert(cur);
        q.push(cur);
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            // cur < x, cur < y.
            
            // put cur at A, pour water from B to A, see if we can get z.
            // cur + kb, b
            if ((z - cur) % y == 0) return true;
            // at last we get, y - ((x - cur) / y * y + cur) is a new number we can get.
            int next = y - (x - cur - (x - cur) / y * y);
            next %= x;
            next %= y;
            if (hit_set.find(next) == hit_set.end()) {
                q.push(next);
                hit_set.insert(next);
            }
            
            // put cur at B, pour water from A to B, see if we can get z.
            // a, cur + ka
            if ((z - cur) % x == 0) return true;
            // at last we get, x - ((y - cur) / x * x + cur) is a new number we can get.
            next = x - (y - cur - (y - cur) / x * x);
            next %= x;
            next %= y;
            if (hit_set.find(next) == hit_set.end()) {
                q.push(next);
                hit_set.insert(next);
            }
        }
        
        return false;
    }
    
    bool canMeasureWaterSlow(int x, int y, int z) {
        int limit = 1 << 16;
        if (x < limit && y < limit) {
            return smallVersion(x, y, z);
        }
        unordered_set<int64_t> hit_set;
        queue<int64_t> q;
        if (z == 0) return true;
        q.push(getKey(0, 0));
        hit_set.insert(getKey(0, 0));
        while (!q.empty()) {
            int a, b;
            int64_t key = q.front(); q.pop();
            getAb(key, a, b);
            // fill a.
            bool ok = false;
            ok |= addKey(x, b, hit_set, q, z);
            // fill b.
            ok |= addKey(a, y, hit_set, q, z);
            // empty a.
            ok |= addKey(0, b, hit_set, q, z);
            // empty b.
            ok |= addKey(a, 0, hit_set, q, z);
            // pour a to b.
            int pour = min(a, y - b);
            ok |= addKey(a - pour, b + pour, hit_set, q, z);
            // pour b to a.
            pour = min(b, x - a);
            ok |= addKey(a + pour, b - pour, hit_set, q, z);
            if (ok) return true;
        }
        return false;
    }
};
