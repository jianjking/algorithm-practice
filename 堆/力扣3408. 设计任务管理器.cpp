#include<iostream>
#include<vector>
#include<unordered_map>
#include<set>
using namespace std;
struct compare {
    bool operator()(const  vector<int>&a, const vector<int>& b)const {
        if (a[1] != b[1])return a[1] >b[1];
        return a[2] > b[2];
    }

};
class TaskManager {
public:
    unordered_map<int, pair<int,int>>f;
    set<vector<int>,compare>cmp;
    TaskManager(vector<vector<int>>& tasks) {
        f.clear();
        cmp.clear();
        for (auto& p : tasks) {
            f[p[1]] = { p[0],p[2 ]};
            cmp.insert({ p[0],p[2],p[1] });
        }
    }

    void add(int userId, int taskId, int priority) {
        f[taskId] = { userId,priority
        };
        cmp.insert({ userId,priority,taskId });
    }

    void edit(int b ,int c) {
        int a = f[b].first;
        int d = f[b].second;
        cmp.erase({ a,d,b });
        cmp.insert({ a,c,b });
        f[b].second = c;
    }

    void rmv(int b) {
        int a = f[b].first;
        int d = f[b].second;
        cmp.erase({ a,d,b });
        f.erase(b);
    }

    int execTop() {
        auto a = *cmp.begin();
        int b = a[0];
        int c = a[1];
        int d = a[2];
        cmp.erase({ cmp.begin() });
        return b;
    }
};
