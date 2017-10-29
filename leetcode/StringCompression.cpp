class Solution {
public:
    int compress(vector<char>& chars) {
        int k = 0;
        for (int i = 0; i < chars.size();) {
            char a = chars[i];
            int j = i + 1;
            for (; j < chars.size() && chars[j] == a; ++j) {
                
            }
            if (j == i + 1) {
                chars[k++] = chars[i++];
            }
            if (j > i + 1) {
                int count = j - i;
                vector<char> digits;
                while (count != 0) {
                    digits.push_back(count % 10 + '0');
                    count /= 10;
                }
                chars[k++] = chars[i];
                for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
                    chars[k++] = *it;
                }
            }
            i = j;
        }
        return k;
    }
};