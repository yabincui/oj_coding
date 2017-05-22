class FileSystem {
    
private:

    struct Node {
        bool isfile;
        string content;
        unordered_map<string, Node*> items;
    };
    
    Node root;
    
    vector<string> splitPath(string& path) {
        vector<string> parts;
        size_t begin = 0;
        size_t end = 0;
        while (end < path.size()) {
            end = path.find('/', begin);
            if (end == std::string::npos) {
                end = path.size();
            }
            if (end > begin) {
                parts.push_back(path.substr(begin, end - begin));
            }
            begin = end + 1;
            end = begin;
        }
        return parts;
    }
    
    Node* findNode(string& path) {
        vector<string> parts = splitPath(path);
        Node* cur = &root;
        for (auto& s : parts) {
            if (cur->isfile) return nullptr;
            auto it = cur->items.find(s);
            if (it == cur->items.end()) {
                return nullptr;
            }
            cur = it->second;
        }
        return cur;
    }
    
    Node* createNode(string& path) {
        vector<string> parts = splitPath(path);
        Node* cur = &root;
        for (auto& s : parts) {
            if (cur->isfile) {
                cur->isfile = false;
            }
            auto it = cur->items.find(s);
            if (it != cur->items.end()) {
                cur = it->second;
            } else {
                Node* new_node = new Node;
                cur->items[s] = new_node;
                cur = new_node;
            }
        }
        return cur;
    }
    
    void freeNode(Node* cur) {
        if (cur != nullptr) {
            for (auto& pair : cur->items) {
                freeNode(pair.second);
                delete pair.second;
            }
        }
    }
    
public:
    FileSystem() {
        root.isfile = false;
    }
    
    ~FileSystem() {
        freeNode(&root);
    }
    
    vector<string> ls(string path) {
        Node* node = findNode(path);
        if (node == nullptr) {
            return vector<string>();
        }
        vector<string> res;
        if (!node->isfile) {
            for (auto& pair : node->items) {
                res.push_back(pair.first);
            }
            sort(res.begin(), res.end());
        } else {
            vector<string> parts = splitPath(path);
            res.push_back(parts.back());
        }
        return res;
    }
    
    void mkdir(string path) {
        Node* node = createNode(path);
        node->isfile = false;
    }
    
    void addContentToFile(string filePath, string content) {
        Node* node = createNode(filePath);
        node->isfile = true;
        node->content += content;
    }
    
    string readContentFromFile(string filePath) {
        Node* node = findNode(filePath);
        if (node == nullptr || !node->isfile) {
            return "";
        }
        return node->content;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem obj = new FileSystem();
 * vector<string> param_1 = obj.ls(path);
 * obj.mkdir(path);
 * obj.addContentToFile(filePath,content);
 * string param_4 = obj.readContentFromFile(filePath);
 */