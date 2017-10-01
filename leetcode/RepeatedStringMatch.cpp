class Solution {
    
    int pattern[10001];
    
    void buildPattern(string& B) {
        int n = B.size();
        
        int j = -1;
        pattern[0] = -1;
        for (int i = 1; i < n; ++i) {
            while (B[j + 1] != B[i] && j != -1) {
                j = pattern[j];
            }
            if (B[j + 1] == B[i]) {
                j++;
            }
            pattern[i] = j;
        }
    }
    
public:
    int repeatedStringMatch(string A, string B) {
        if (B.empty()) return 0;
        if (A.empty()) return -1;
        buildPattern(B);
        for (int i = 0; i < B.size(); ++i) {
            //printf("pattern[%d] = %d\n", i, pattern[i]);
        }
        
        int j = -1;
        for (int i = 0; i < A.size() + B.size(); ++i) {
            char a = A[i % A.size()];
            while (B[j + 1] != a && j != -1) {
                //printf("j = %d, pattern[j] = %d\n", j, pattern[j]);
                j = pattern[j];
            }
            if (B[j + 1] == a) {
                j++;
                if (j + 1 == B.size()) {
                    int cycle = (i + 1) / A.size();
                    if ((i + 1) % A.size() != 0) {
                        cycle++;
                    }
                    return cycle;
                }
            }
        }
        return -1;
    }
};
