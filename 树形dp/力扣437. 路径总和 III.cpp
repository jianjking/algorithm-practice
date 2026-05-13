#include<iostream>
#include<vector>
#include<map>
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
      void f(TreeNode* root, int target, map<long, long>& dp, long a) {
          if (root == NULL)return;
          long b = a + root->val;
          if (dp.find(b - target) != dp.end()) {
              ans += dp[b - target];
          }
          dp[b]++;
          f(root->left, target, dp, b);
          f(root->right, target, dp, b);
          dp[b]--;
      }
      int ans;
      int pathSum(TreeNode* root, int target) {
          ans = 0;
          map<long, long>dp;
          dp[0] = 1;
          f(root, target, dp, 0);
          return ans;
      }
  };