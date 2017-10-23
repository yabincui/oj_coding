class Solution {
public:
    bool isValidSerialization(string preorder) {
        vector<string> v;
        for (int i = 0; i < preorder.size();) {
            if (preorder[i] == ',') {
                return false;
            }
            if (preorder[i] == '#') {
                v.push_back("#");
                ++i;
            } else {
                string s;
                while (i < preorder.size() && preorder[i] != ',') {
                    s.push_back(preorder[i++]);
                }
                v.push_back(s);
            }
            if (i < preorder.size()) {
                if (preorder[i] != ',') {
                    return false;
                }
                i++;
            }
        }
        
        if (v.empty()) return true;
        int need_count = 1;
        for (int i = 0; i < v.size(); ++i) {
            //printf("v[%d] = %s, need_count = %d\n", i, v[i].c_str(), need_count);
            if (need_count == 0) return false;
            if (v[i] == "#") {
                need_count--;
            } else {
                need_count++;
            }
        }
        return need_count == 0;
    }
};