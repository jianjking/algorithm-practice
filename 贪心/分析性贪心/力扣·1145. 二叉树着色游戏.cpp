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
      int leftCount = 0, rightCount = 0, X;

      // 返回以 node 为根的子树总节点数
      int dfs(TreeNode* node) {
          if (!node) return 0;
          int L = dfs(node->left);
          int R = dfs(node->right);
          if (node->val == X) {
              leftCount = L;
              rightCount = R;
          }
          return L + R + 1;
      }

  public:
      bool btreeGameWinningMove(TreeNode* root, int n, int x) {
          X = x;
          dfs(root);
          int parentCount = n - (leftCount + rightCount + 1);
          // 看哪一块 > n/2
          int maxRegion = max({ leftCount, rightCount, parentCount });
          return maxRegion > n / 2;
      }
  };
