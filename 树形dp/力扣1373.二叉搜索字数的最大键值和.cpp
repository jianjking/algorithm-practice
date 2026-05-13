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
  struct GGG {
      int max1;
      int min1;
      int maxsum;
      int sum;
      bool an;
  };

  class Solution {
  public:
      GGG bns(TreeNode* root) {
          if (root == nullptr) {
              return { INT_MIN,INT_MAX,0,0,true };
          }
          GGG l = bns(root->left);
          GGG r = bns(root->right);
          int max1 = max(root->val, max(l.max1, r.max1));
          int min1 = min(root->val, min(l.min1, r.min1));
          bool an = l.an && r.an && root->val > l.max1 && root->val < r.min1;
          int maxsum = max(l.maxsum, r.maxsum);
          if (an) {
              maxsum = max(maxsum, l.sum + r.sum + root->val);
          }
          int sum = l.sum + r.sum + root->val;
          return { max1,min1,maxsum,sum,an };
      }
      int maxSumBST(TreeNode* root) {
          return bns(root).maxsum;
      }
  };