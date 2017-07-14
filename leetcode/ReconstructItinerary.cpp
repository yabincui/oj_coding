class Solution {
    struct Node {
        vector<pair<int, int>> neighbors;    
    };
    
    vector<string> getNames(vector<pair<string, string>>& tickets) {
        set<string> hit_set;
        for (auto& pair : tickets) {
            hit_set.insert(pair.first);
            hit_set.insert(pair.second);
        }
        return vector<string>(hit_set.begin(), hit_set.end());
    }
    
    vector<Node> buildNodes(vector<pair<string, string>>& tickets, vector<string>& names, unordered_map<string, int>& name_map) {
        for (int i = 0; i < names.size(); ++i) {
            name_map[names[i]] = i;
        }
        vector<Node> nodes(names.size());
        vector<map<int, int>> sets(names.size());
        for (auto& pair : tickets) {
            int from = name_map[pair.first];
            int to = name_map[pair.second];
            sets[from][to]++;
        }
        for (int i = 0; i < names.size(); ++i) {
            for (auto& pair : sets[i]) {
                nodes[i].neighbors.push_back(pair);
            }
        }
        return nodes;
    }
    vector<Node> nodes;
    vector<int> path;
    int pathCount;
    
    bool find(int cur) {
        if (pathCount == 0) {
            return true;
        }
        for (auto& pair : nodes[cur].neighbors) {
            if (pair.second != 0) {
                pair.second--;
                pathCount--;
                path.push_back(pair.first);
                if (find(pair.first)) return true;
                pathCount++;
                path.pop_back();
                pair.second++;
            }
        }
        return false;
    }
    
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        // Try a simple dfs method. O(N!).
        vector<string> names = getNames(tickets);
        unordered_map<string, int> name_map;
        nodes = buildNodes(tickets, names, name_map);
        path.clear();
        pathCount = tickets.size();
        int start = name_map["JFK"];
        path.push_back(start);
        find(start);
        vector<string> res;
        for (auto i : path) {
            res.push_back(names[i]);
        }
        return res;
    }
};
