#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
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
    TreeNode* replaceValueInTree(TreeNode* root) {
        root->val = 0;
        vector<TreeNode*>f;
        f.push_back(root);
        while (!f.empty()) {
            int sz = f.size();
            vector<TreeNode*>tmp;
            tmp.reserve(2 * sz);
            long long sum = 0;
            for (auto p : f) {
                if (p->left != nullptr) {
                    sum += p->left->val;
                    tmp.push_back(p->left);
                }
                if (p->right != nullptr) {
                    sum += p->right->val;
                    tmp.push_back(p->right);
                }
            }
            for (auto& p : f) {
                if (p->left != NULL) { 
                    p->left->val = sum - p->left->val;
                    if (p->right != NULL) {
                        p->left->val -= p->right->val;
                    }
                }
                if (p->right != NULL) {
                    if (p->left != NULL)p->right->val = p->left->val;
                    else {
                        p->right->val = sum - p->right->val;
                    }
                }
            }
            f = tmp;
        }
        return root;
    }
};