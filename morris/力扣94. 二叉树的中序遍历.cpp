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
      vector<int> inorderTraversal(TreeNode* root) {
          TreeNode* tmp = root;
          TreeNode* r = NULL;
          vector<int>ans;
          ans.reserve(100000);
          while (tmp != NULL) {
              r = tmp->left;
              if (r != NULL) {
                  while (r->right != nullptr && r->right != tmp) {
                      r = r->right;
                  }
                  if (r->right == NULL) {
                      r->right = tmp;
                      tmp = tmp->left;
                      continue;
                  }
                  else {
                      r->right = nullptr;
                      ans.push_back(tmp->val);
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