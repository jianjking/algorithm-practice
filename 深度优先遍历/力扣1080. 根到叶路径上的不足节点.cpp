#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
class Solution {
public:
    int dfs(TreeNode* root, int limit, int sum, unordered_map<TreeNode*, int>& cnt) {
        if (!root)return sum;
        cnt[root] = dfs(root->left, limit, sum + root->val, cnt);
        cnt[root] = max(cnt[root], dfs(root->right, limit, sum + root->val, cnt));
        return cnt[root];
    }
    int dfs1(TreeNode* root, int limit, unordered_map<TreeNode*, int>& cnt) {
        if (!root)return true;
        if (!dfs1(root->left, limit, cnt)) {
            root->left = NULL;
        }
        if (!dfs1(root->right, limit, cnt)) {
            root->right = NULL;
        }
        return cnt[root] >= limit;
    }
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        unordered_map<TreeNode*, int>cnt;
        dfs(root, limit, 0, cnt);
        dfs1(root, limit, cnt);
        return root;
    }
};
