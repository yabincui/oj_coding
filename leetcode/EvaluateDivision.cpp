// 399. Evaluate Division
class Solution {
public:
    class Node {
    private:
        Node* parent;
        double mul;
    
    public:
        Node() : parent(NULL), mul(1.0) {}
        
        Node* findRoot() {
            if (parent == NULL) {
                return this;
            }
            Node* root = parent->findRoot();
            mul *= parent->mul;
            parent = root;
            return root;
        }

        // this / other = m
        void Union(Node* other, double m) {
            Node* other_root = other->findRoot();
            other_root->parent = this;
            other_root->mul = 1.0 / (m * other->mul);
        }
        
        double Div(Node* other) {
            if (findRoot() == other->findRoot()) {
                return mul / other->mul;
            }
            return -1.0;
        }
    };

    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        map<string, Node> key_map;
        for (auto& pair : equations) {
            key_map[pair.first] = Node();
            key_map[pair.second] = Node();
        }
        for (size_t i = 0; i < equations.size(); ++i) {
            auto& pair = equations[i];
            Node* a = &key_map[pair.first];
            Node* b = &key_map[pair.second];
            a->Union(b, values[i]);
        }
        vector<double> result;
        for (size_t i = 0; i < queries.size(); ++i) {
            auto it = key_map.find(queries[i].first);
            if (it == key_map.end()) {
                result.push_back(-1);
                continue;
            }
            Node* a = &it->second;
            it = key_map.find(queries[i].second);
            if (it == key_map.end()) {
                result.push_back(-1);
                continue;
            }
            Node* b = &it->second;
            result.push_back(a->Div(b));
        }
        return result;
    }
};

