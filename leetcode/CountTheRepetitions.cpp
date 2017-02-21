// 466. Count the Repetitions.
class Solution {
public:

    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int size1 = s1.size();
        int size2 = s2.size();
        int64_t s1_n1_size = (int64_t)size1 * n1;
        if ((int64_t)size1 * n1 < (int64_t)size2 * n2) {
            return 0;
        }
        // dp[i][j] means from s1[i] to match s2[j], needs dp[i][j] characters.
        int dp[size1][size2];
        for (int i = 0; i < size1; ++i) {
            for (int j = 0; j < size2; ++j) {
                int t = 0;
                for (; t < size1; ++t) {
                    int pos = (i + t) % size1;
                    if (s1[pos] == s2[j]) {
                        break;
                    }
                }
                if (t == size1) {
                    return 0;
                }
                dp[i][j] = t + 1;
            }
        }
        // dpS2[i] means from s1[i] to match s2, needs dpS2[i] characters.
        int dpS2[size1];
        for (int i = 0; i < size1; ++i) {
            int s1_pos = i;
            int move = 0;
            for (int j = 0; j < size2; ++j) {
                move += dp[s1_pos][j];
                s1_pos = (s1_pos + dp[s1_pos][j]) % size1;
            }
            dpS2[i] = move;
        }
        int max_s2_count = s1_n1_size / size2;
        int max_power = 1;
        int order = 0;
        while (max_power < max_s2_count) {
            max_power *= 2;
            order++;
        }
        // dpPower[i][j] means from s1[i] to match (s2, 1 << j), needs dpPower[i][j] characters. -1 if not possible.
        int dpPower[size1][order + 1];
        for (int i = 0; i < size1; ++i) {
            dpPower[i][0] = dpS2[i];
        }
        for (int i = 1; i <= order; ++i) {
            for (int j = 0; j < size1; ++j) {
                int move1 = dpPower[j][i-1];
                if (move1 == -1) {
                    dpPower[j][i] = -1;
                    continue;
                }
                int pos1 = (j + move1) % size1;
                int move2 = dpPower[pos1][i-1];
                if (move2 == -1 || move1 + move2 + j > s1_n1_size) {
                    dpPower[j][i] = -1;
                    continue;
                }
                dpPower[j][i] = move1 + move2;
            }
        }
        
        int low = 0;
        int high = max_s2_count / n2;
        while (low + 1 < high) {
            int mid = low + (high - low) / 2;
            int s2_count = mid * n2;
            int move = getMove(s2_count, order, (int*)dpPower, size1, s1_n1_size);
            if (move == -1) {
                high = mid - 1;
            } else {
                low = mid;
            }
        }
        if (getMove(high * n2, order, (int*)dpPower, size1, s1_n1_size) != -1) {
            return high;
        }
        return low;
    }
    
    int getMove(int s2_count, int order, int* dp, int size1, int s1_n1_size) {
        int s1_pos = 0;
        int move = 0;
        int (*dpPower)[order + 1] = (int (*)[(order + 1)])dp;
        for (int j = order; j >= 0; --j) {
            if ((s2_count >> j) & 1) {
                int add = dpPower[s1_pos][j];
                if (add == -1 || move + add > s1_n1_size) {
                    move = -1;
                    break;
                }
                move += add;
                s1_pos = (s1_pos + add) % size1;
            }
        }
        return move;
    }

    int getMaxRepetitions1(string s1, int n1, string s2, int n2) {
        int size1 = s1.size();
        int size2 = s2.size();
        int64_t s1_n1_size = (int64_t)size1 * n1;
        if ((int64_t)size1 * n1 < (int64_t)size2 * n2) {
            return 0;
        }
        // dp[i][j] means from s1[i] to match s2[j], needs dp[i][j] characters.
        int dp[size1][size2];
        for (int i = 0; i < size1; ++i) {
            for (int j = 0; j < size2; ++j) {
                int t = 0;
                for (; t < size1; ++t) {
                    int pos = (i + t) % size1;
                    if (s1[pos] == s2[j]) {
                        break;
                    }
                }
                if (t == size1) {
                    return 0;
                }
                dp[i][j] = t + 1;
            }
        }
        // dpS2[i] means from s1[i] to match s2, needs dpS2[i] characters.
        int dpS2[size1];
        for (int i = 0; i < size1; ++i) {
            int s1_pos = i;
            int move = 0;
            for (int j = 0; j < size2; ++j) {
                move += dp[s1_pos][j];
                s1_pos = (s1_pos + dp[s1_pos][j]) % size1;
            }
            dpS2[i] = move;
        }
        int max_power = 1;
        int order = 0;
        while (max_power < n2) {
            max_power *= 2;
            order++;
        }
        // dpPower[i][j] means from s1[i] to match (s2, 1 << j), needs dpPower[i][j] characters. -1 if not possible.
        int dpPower[size1][order + 1];
        for (int i = 0; i < size1; ++i) {
            dpPower[i][0] = dpS2[i];
        }
        for (int i = 1; i <= order; ++i) {
            for (int j = 0; j < size1; ++j) {
                int move1 = dpPower[j][i-1];
                if (move1 == -1) {
                    dpPower[j][i] = -1;
                    continue;
                }
                int pos1 = (j + move1) % size1;
                int move2 = dpPower[pos1][i-1];
                if (move2 == -1 || move1 + move2 + j > s1_n1_size) {
                    dpPower[j][i] = -1;
                    continue;
                }
                dpPower[j][i] = move1 + move2;
            }
        }
        
        // dpN2[i] means from s1[i] to match (s2, n2), needs dpN2[i] characters. -1 if not possible.
        int dpN2[size1];
        for (int i = 0; i < size1; ++i) {
            int s1_pos = i;
            int move = 0;
            for (int j = order; j >= 0; --j) {
                if ((n2 >> j) & 1) {
                    int add = dpPower[s1_pos][j];
                    if (add == -1 || i + move + add > s1_n1_size) {
                        move = -1;
                        break;
                    }
                    move += add;
                    s1_pos = (s1_pos + add) % size1;
                }
            }
            dpN2[i] = move;
            //printf("dpN2[%d] = %d\n", i, dpN2[i]);
        }
        int res = 0;
        for (int i = 0, s1_pos = 0; i < s1_n1_size;) {
            int move = dpN2[s1_pos];
            if (move == -1) break;
            i += move;
            if (i > s1_n1_size) break;
            s1_pos = (s1_pos + move) % size1;
            res++;
        }
        return res;
    }
};
