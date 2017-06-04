class Solution {
    
    bool getStartTag(string& s, int start, int* end, string* name) {
        if (start + 2 > s.size()) {
            return false;
        }
        int i = start;
        while (i < s.size() && s[i] != '>') {
            if (!(s[i] >= 'A' && s[i] <= 'Z')) {
                return false;
            }
            i++;
        }
        if (i == s.size() || i - start < 1 || i - start > 9) {
            return false;
        }
        *name = s.substr(start, i - start);
        *end = i + 1;
        return true;
    }
    
    bool checkValid(string s) {
        int i = 0;
        vector<string> tag_stack;
        string cdata = "![CDATA[";
        string cdata_end = "]]>";
        while (i < s.size()) {
            if (s[i] != '<') {
                i++;
                continue;
            }
            i++;
            if (i == s.size()) return false;
            if (i + cdata.size() <= s.size() && s.substr(i, cdata.size()) == cdata) {
                size_t end = s.find(cdata_end, i + cdata.size());
                if (end == string::npos) {
                    return false;
                }
                i = end + 1;
                continue;
            }
            if (s[i] == '/') {
                int end;
                string tag_name;
                if (!getStartTag(s, i + 1, &end, &tag_name)) {
                    return false;
                }
                if (tag_stack.empty() || tag_stack.back() != tag_name) {
                    return false;
                }
                tag_stack.pop_back();
                i = end;
                continue;
            }
            int end;
            string tag_name;
            if (!getStartTag(s, i, &end, &tag_name)) {
                return false;
            }
            tag_stack.push_back(tag_name);
            i = end;
        }
        if (!tag_stack.empty()) {
            return false;
        }
        return true;
    }
    
public:
    bool isValid(string code) {
        int next_pos;
        string tag_name;
        if (code.size() == 0 || code[0] != '<') {
            return false;
        }
        if (!getStartTag(code, 1, &next_pos, &tag_name)) {
            return false;
        }
        if (next_pos + tag_name.size() + 3 > code.size()) {
            return false;
        }
        string end_tag = "</" + tag_name + ">";
        int end_pos = code.size() - end_tag.size();
        if (code.substr(end_pos, end_tag.size()) != end_tag) {
            return false;
        }
        return checkValid(code.substr(next_pos, end_pos - next_pos));
    }
};
