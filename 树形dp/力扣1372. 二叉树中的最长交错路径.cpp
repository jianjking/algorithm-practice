#include<iostream>
#include<vector>
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
    int mx = INT_MIN;
    pair<int,int> dfs(TreeNode* root) {
        int lmx = 0;
        int rmx = 0;
        if (root->left != NULL)lmx = dfs(root->left).second + 1;
        if (root->right != NULL)rmx = dfs(root->right).first + 1;
        mx = max(mx, lmx);
        mx = max(mx,rmx);
        return { lmx,rmx };
    }
    int longestZigZag(TreeNode* root) {
        dfs(root);
        return mx;
    }
};