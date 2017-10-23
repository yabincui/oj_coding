class RandomizedSet {
    
    unordered_map<int, int> pos_map;
    vector<int> values;
    
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        auto it = pos_map.find(val);
        if (it != pos_map.end()) {
            return false;
        }
        int pos = values.size();
        pos_map.insert(make_pair(val, pos));
        values.push_back(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto it = pos_map.find(val);
        if (it == pos_map.end()) {
            return false;
        }
        if (values.size() > 1 && it->second != values.size() - 1) {
            int lastVal = values.back();
            int toPos = it->second;
            pos_map[lastVal] = toPos;
            values[toPos] = lastVal;
        }
        pos_map.erase(it);
        values.pop_back();
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int pos = rand() % values.size();
        return values[pos];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */