/*
// Employee info
class Employee {
public:
    // It's the unique ID of each node.
    // unique id of this employee
    int id;
    // the importance value of this employee
    int importance;
    // the id of direct subordinates
    vector<int> subordinates;
};
*/
class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int, Employee*> map;
        for (auto& e : employees) {
            map[e->id] = e;
        }
        
        queue<int> q;
        q.push(id);
        int sum = 0;
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            Employee* e = map[cur];
            sum += e->importance;
            for (auto sub : e->subordinates) {
                q.push(sub);
            }
        }
        return sum;
    }
};
