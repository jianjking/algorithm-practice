#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using namespace std;

class ThroneInheritance {
public:
    string king;
    unordered_map<string, vector<string>> rem; // 孩子们（保持出生顺序）
    unordered_set<string> vis;                 // 死亡的人

    ThroneInheritance(string kingName) {
        king = kingName;
    }

    // parentName 生了个 childName
    void birth(string parentName, string childName) {
        rem[parentName].push_back(childName);
    }

    // name 去世
    void death(string name) {
        vis.insert(name);
    }

    // 深度优先遍历继承顺序
    void dfs(const string& cur, vector<string>& ans) {
        if (!vis.count(cur)) {      // 当前人没死就加入
            ans.push_back(cur);
        }
        for (auto& child : rem[cur]) {
            dfs(child, ans);        // 孩子们依次递归
        }
    }

    // 获取完整继承顺序
    vector<string> getInheritanceOrder() {
        vector<string> ans;
        dfs(king, ans);
        return ans;
    }
};

