class StringIterator {
    struct Node {
        char c;
        int count;
    };
    
    vector<Node> nodes;
    int index;
    
public:
    StringIterator(string compressedString) {
        for (int i = 0; i < compressedString.size();) {
            char c = compressedString[i];
            i++;
            int count = 0;
            while (i < compressedString.size() && isdigit(compressedString[i])) {
                count = count * 10 + compressedString[i] - '0';
                i++;
            }
            Node n;
            n.c = c;
            n.count = count;
            nodes.push_back(n);
        }
        index = 0;
    }
    
    char next() {
        char c = ' ';
        if (hasNext()) {
            c = nodes[index].c;
            nodes[index].count--;
            if (nodes[index].count == 0) {
                index++;
            }
        }
        return c;
    }
    
    bool hasNext() {
        return index < nodes.size();
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator obj = new StringIterator(compressedString);
 * char param_1 = obj.next();
 * bool param_2 = obj.hasNext();
 */
