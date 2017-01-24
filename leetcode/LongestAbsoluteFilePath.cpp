//388. Longest Absolute File Path
class Solution {
public:
    int lengthLongestPath(string input) {
        int max_len = 0;
        vector<int> cur_lens;
        int cur_indent = 0;
        string cur_item;
        input.push_back('\n');
        for (size_t i = 0; i < input.size(); ++i) {
            char c = input[i];
            if (c != '\n' && c != '\t') {
                cur_item.push_back(c);
            } else if (c == '\t') {
                cur_indent++;
            } else if (c == '\n') {
                int len = cur_item.size();
                if (cur_indent > 0) {
                    len += cur_lens[cur_indent - 1];
                }
                //printf("cur_item = %s, len = %d\n", cur_item.c_str(), len);
                if (cur_item.find('.') != -1) {
                    // is a file.
                    if (len > max_len) {
                        max_len = len;
                    }
                } else {
                    // is a dir.
                    len++;
                    if (cur_lens.size() <= cur_indent) {
                        cur_lens.push_back(len);
                    } else {
                        cur_lens[cur_indent] = len;
                    }
                }
                cur_indent = 0;
                cur_item.clear();
            }
        }
        return max_len;
    }
};
