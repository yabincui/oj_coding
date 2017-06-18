class Solution {
    
public:
    int leastInterval(vector<char>& tasks, int n) {
        int count[26];
        int total_count = 0;
        memset(count, 0, sizeof(count));
        for (auto& c : tasks) {
            count[c - 'A']++;
            total_count++;
        }
        int next_ok_time[26];
        memset(next_ok_time, 0, sizeof(count));
        int q_mask = 0;
        int cur_time = 0;
        int process_count = 0;
        while (process_count < total_count) {
            int min_ok_time = INT_MAX;
            for (int i = 0; i < 26; ++i) {
                if (count[i] == 0) continue;
                next_ok_time[i] = max(next_ok_time[i], cur_time);
                min_ok_time = min(min_ok_time, next_ok_time[i]);
            }
            cur_time = min_ok_time;
            int max_left_count = 0;
            int max_left_id = 0;
            for (int i = 0; i < 26; ++i) {
                if (count[i] > max_left_count && next_ok_time[i] == cur_time) {
                    max_left_count = count[i];
                    max_left_id = i;
                }
            }
            //printf("put %d at time %d\n", max_left_id, cur_time);
            count[max_left_id]--;
            process_count++;
            next_ok_time[max_left_id] = cur_time + n + 1;
            //printf("next_ok_time[%d] = %d\n", max_left_id, next_ok_time[max_left_id]);
            cur_time++;
        }
        return cur_time;
    }
};
