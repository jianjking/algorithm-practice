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
    bool isValidBST(TreeNode* root) {
        TreeNode* tmp = root;
        TreeNode* pre = NULL;
        bool an = true;
        while (tmp != NULL) {
            TreeNode* r = tmp->left;
            if (r != NULL) {
                while (r->right != NULL && r->right != tmp) {
                    r = r->right;
                }
                    if (r->right == NULL) {
                        r->right = tmp;
                        tmp = tmp->left;
                        continue;
                    }
                    else {
                        r->right = NULL;
                        if (pre != NULL && pre->val >= tmp->val)an = false;
                        pre = tmp;
                    }
                }
            else {
                if (pre != NULL && pre->val >= tmp->val)an = false;
                pre = tmp;
            }
            tmp = tmp->right;
            }
        return an;
        }
    
};