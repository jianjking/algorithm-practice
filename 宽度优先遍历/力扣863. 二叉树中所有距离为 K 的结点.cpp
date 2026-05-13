#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;
struct TreeNode {
      int val;
     TreeNode *left;
      TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
void dfs(TreeNode*root,int val,unordered_map<int,vector<int>>&map) {
    if (root == NULL)return;
    map[val].push_back(root->val);
    map[root->val].push_back(val);
    dfs(root->left, root->val, map);
    dfs(root->right, root->val, map);
}
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        unordered_map<int, vector<int>>f;
        dfs(root->left, root->val, f);
        dfs(root->right, root->val, f);
        queue<vector<int>>g;
        g.push({ target->val,0 });
        vector<int>ans;
        vector<bool>visit(501, false);
        visit[target->val] = true;
        while (!g.empty()) {
            int sz = g.size();
            bool c = false;
            for (int i = 0;i < sz;i++) {
                int a = g.front()[0];
                int b = g.front()[1];
                if (b == k) { 
                   c = true;
                    ans.push_back(a); }
                g.pop();
                for (auto p : f[a]) {
                    if (!visit[p]) {
                        g.push({ p,b + 1 });
                        visit[p] = true;
                    }
                }
            }
            if (c)break;

        }
        return ans;
    }
};