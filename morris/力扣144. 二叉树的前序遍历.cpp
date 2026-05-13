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
    vector<int> preorderTraversal(TreeNode* root) {
        TreeNode* tmp = root;
        vector<int>ans;
        ans.reserve(1000000);
        TreeNode* r = nullptr;
        while (tmp != nullptr) {
            r = tmp->left;
            if (r != NULL) {
                while (r->right != tmp && r->right != NULL)r = r->right;
                if (r->right == NULL) {
                    r->right = tmp;
                    ans.push_back(tmp->val);
                    tmp = tmp->left;
                    continue;
                }
                else {
                    r->right = nullptr;
                }
            }
            else {
                ans.push_back(tmp->val);
            }
            tmp = tmp->right;
        }
        return ans;
    }
};