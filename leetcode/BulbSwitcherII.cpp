class Solution {
    
    struct State {
        set<int> options; // b_value, c_value, d_value.
        vector<bool> result;
    };
    
public:
    int flipLights(int n, int m) {
        if (n == 0 || m == 0) return 1;
        vector<State> states;
        for (int option = 0; option < 8; ++option) {
            vector<bool> values(n, true);
            for (int i = 1; i <= n; ++i) {
                if (option & 1) { // even
                    if ((i & 1) == 0) {
                        values[i-1] = !values[i-1];
                    }
                }
                if (option & 2) { // odd
                    if ((i & 1) == 1) {
                        values[i-1] = !values[i-1];
                    }
                }
                if (option & 4) { // 3 * K + 1
                    if (i % 3 == 1) {
                        values[i-1] = !values[i-1];
                    }
                }
            }
            bool found = false;
            for (int i = 0; i < states.size(); ++i) {
                if (values == states[i].result) {
                    states[i].options.insert(option);
                    found = true;
                    break;
                }
            }
            if (!found) {
                State state;
                state.options.insert(option);
                state.result = values;
                states.push_back(state);
            }
        }
        if (m >= 4) {
            return states.size();
        }
        vector<bool> filled(states.size(), false);
        for (int d_value = 0; d_value <= m; ++d_value) {
            int bc_value = m - d_value;
            int d_option = (d_value % 2 == 0) ? 0 : 4;
            vector<int> bc_options;
            if (bc_value == 0) {
                bc_options.push_back(0);
            } else if (bc_value == 1) {
                bc_options.push_back(1);
                bc_options.push_back(2);
                bc_options.push_back(3);
            } else {
                bc_options.push_back(0);
                bc_options.push_back(1);
                bc_options.push_back(2);
                bc_options.push_back(3);
            }
            for (int i = 0; i < bc_options.size(); ++i) {
                int option = d_option | bc_options[i];
                for (int j = 0; j < states.size(); ++j) {
                    if (states[j].options.find(option) != states[j].options.end()) {
                        filled[j] = true;
                        break;
                    }
                }
            }
        }
        int res = 0;
        for (int i = 0; i < filled.size(); ++i) {
            if (filled[i]) res++;        
        }
        return res;
    }
};
