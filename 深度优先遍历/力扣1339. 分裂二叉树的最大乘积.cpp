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
  const int mod = 1e9 + 7;
  class Solution {
  public:
      long long sum;
      long long best;
      void dfs1(TreeNode* node) {
          if (node == nullptr)return;
          sum += node->val;
          dfs1(node->left);
          dfs1(node->right);
      }
      long long dfs2(TreeNode* node) {
          if (node == nullptr)return 0;
          long long sumv = node->val + dfs2(node->left) + dfs2(node->right);
          if (abs(2 * sumv - sum) < abs(2 * best - sum))best = sumv;
          return sumv;
      }
      int maxProduct(TreeNode* root) {
          sum = 0;
          best = INT_MAX;
          dfs1(root);
          dfs2(root);
          return (best * (sum - best)) % mod;
      }
  };