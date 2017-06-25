class Excel {
    
    int getPointKey(int r, int c) {
        return (r << 5) | c;
    }
    
    struct Value {
        bool isValue;
        int value;
        unordered_map<int, int> count_map;
        Value() : isValue(true), value(0) {}
    };
    
    vector<vector<Value>> values;
    unordered_set<int> update_values;
    int rows;
    int cols;
    
    void updateValues() {
        printf("updateValues\n");
        update_values.clear();
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                auto& v = values[r][c];
                if (!v.isValue) {
                    updateValue(r, c);
                }
            }
        }
    }
    
    int updateValue(int r, int c) {
        //printf("updateValue(r %d, c %d)\n", r, c);
        auto& v = values[r][c];
        if (v.isValue) {
            return v.value;
        }
        int key = getPointKey(r, c);
        if (update_values.find(key) != update_values.end()) {
            return v.value;
        }
        long long sum = 0;
        for (auto& pair : v.count_map) {
            int tr = pair.first >> 5;
            int tc = pair.first & 0x1f;
            long long temp_value = updateValue(tr, tc);
            temp_value *= pair.second;
            sum += temp_value;
        }
        v.value = (int)sum;
        update_values.insert(key);
        return v.value;
    }
    
    void getRC(const string& s, int* r, int* c) {
        *c = s[0] - 'A';
        *r = atoi(&s[1]) - 1;
    }
    
public:
    Excel(int H, char W) {
        printf("init(%d, %c)\n", H, W);
        rows = H;
        cols = W - 'A' + 1;
        values = vector<vector<Value>>(rows, vector<Value>(cols));
    }
    
    void set(int r, char c, int v) {
        printf("set(r %d, c %c, v %d)\n", r, c, v);
        int row = r - 1;
        int col = c - 'A';
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            auto& value = values[row][col];
            value.isValue = true;
            value.value = v;
            value.count_map.clear();
        }
        updateValues();
    }
    
    int get(int r, char c) {
        printf("get(r %d, c %c)\n", r, c);
        int row = r - 1;
        int col = c - 'A';
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return values[row][col].value;
        }
        return 0;
    }
    
    int sum(int r, char c, vector<string> strs) {
        printf("sum(r %d, c %c strs: ", r, c);
        for (auto& s : strs) {
            printf("%s, ", s.c_str());
        }
        printf("\n");
        int row = r - 1;
        int col = c - 'A';
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return 0;
        }
        auto& v = values[row][col];
        v.isValue = false;
        v.count_map.clear();
        for (auto& s : strs) {
            size_t id = s.find(':');
            int start_r;
            int end_r;
            int start_c;
            int end_c;
            if (id == string::npos) {
                getRC(s, &start_r, &start_c);
                end_r = start_r;
                end_c = start_c;
            } else {
                getRC(s.substr(0, id), &start_r, &start_c);
                getRC(s.substr(id + 1), &end_r, &end_c);
            }
            for (int r = start_r; r <= end_r; ++r) {
                for (int c = start_c; c <= end_c; ++c) {
                    int key = getPointKey(r, c);
                    v.count_map[key]++;
                }
            }
        }
        updateValues();
        return v.value;
    }
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel obj = new Excel(H, W);
 * obj.set(r,c,v);
 * int param_2 = obj.get(r,c);
 * int param_3 = obj.sum(r,c,strs);
 */
