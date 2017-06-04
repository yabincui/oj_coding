class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<int>> content_map;
        vector<string> abs_path;
        for (auto& s : paths) {
            size_t d1 = s.find(' ');
            if (d1 == string::npos) {
                continue;
            }
            string dir = s.substr(0, d1);
            d1++;
            while (d1 < s.size()) {
                size_t name_start_id = d1;
                size_t end = s.find(' ', name_start_id);
                if (end == string::npos) {
                    end = s.size();
                }
                size_t name_end_id = s.find('(', name_start_id);
                string name = s.substr(name_start_id, name_end_id - name_start_id);
                size_t content_start_id = name_end_id + 1;
                size_t content_end_id = s.find(')', content_start_id);
                string content = s.substr(content_start_id, content_end_id - content_start_id);
                
                abs_path.push_back(dir + '/' + name);
                content_map[content].push_back(abs_path.size() - 1);
                d1 = end + 1;
            }
        }
        vector<vector<string>> res;
        for (auto& pair : content_map) {
            if (pair.second.size() < 2) {
                continue;
            }
            vector<string> v;
            for (auto id : pair.second) {
                v.push_back(abs_path[id]);
            }
            res.push_back(v);
        }
        return res;
    }
};
