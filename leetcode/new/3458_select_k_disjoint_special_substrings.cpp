// key: Graph
class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        // needs to be the first letter. only contains first letters, or letters appeared before.
        // last[c1], last[c2], last[c3], ... (find a min one). At most 26.
        // 
        vector<int> disjoint;

        vector<int> first(26, -1);
        vector<int> last(26, -1);
        vector<vector<bool>> connect(26, vector<bool>(26, false));
        for (int i = 0; i < s.size(); i++) {
            int index = s[i] - 'a';
            if (first[index] == -1) {
                first[index] = i;
            }
            last[index] = i;
        }
        for (int i = 0; i < s.size(); i++) {
            int index = s[i] - 'a';
            for (int j = 0; j < 26; j++) {
                if (index != j && i > first[j] && i < last[j]) {
                    connect[j][index] = true;
                }
            }
        }
        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < 26; i++) {
                if (k == i || !connect[i][k]) {
                    continue;
                }
                for (int j = 0; j < 26; j++) {
                    if (k == j || i == j || !connect[k][j]) {
                        continue;
                    }
                    connect[i][j] = true;
                }
            }
        }
        for (int i = 0; i < 26; i++) {
            //printf("connect[%d] = ", i);
            for (int j = 0; j < 26; j++) {
                if (connect[i][j]) {
              //      printf("%d ", j);
                }
            }
            ///printf("\n");
        }
        vector<int> last_extend(26, -1);
        for (int i = 0; i < 26; i++) {
            if (last[i] == -1) {
                continue;
            }
            int extend = last[i];
            for (int j = 0; j < 26; j++) {
                if (last[j] == -1 || !connect[i][j]) {
                    continue;
                }
                if (first[j] < first[i]) {
                    extend = -1;
                    break;
                }
                extend = max(extend, last[j]);
            }
            if (first[i] == 0 && extend == s.size() - 1) {
                extend = -1;
            }
            last_extend[i] = extend;
            //printf("last_extend[%d]=%d\n", i, extend);
        }
        
        vector<bool> used(26, false);
        int max_count = 0;
        while (true) {
            int select_index = -1;
            for (int i = 0; i < 26; i++) {
                if (used[i] || first[i] == -1 || last_extend[i] == -1) {
                    continue;
                }
                if (select_index == -1 || last_extend[select_index] > last_extend[i]) {
                    select_index = i;
                }
            }
            if (select_index == -1) {
                break;
            }
            //printf("select_index=%d\n", select_index);
            for (int i = 0; i < 26; i++) {
                if (connect[select_index][i] || connect[i][select_index] || i == select_index) {
                    used[i] = true;
                }
            }
            max_count++;
        }
        return max_count >= k;
    }
};