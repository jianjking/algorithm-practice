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
      int n;

      TreeNode* dfs(string& s, int depth, int& i) {
          int j = i, cnt = 0;
          // 先统计连续的 '-'
          while (j < n && s[j] == '-') {
              cnt++;
              j++;
          }
          if (cnt != depth) return nullptr; // 深度不匹配，返回空

          // 读取数字
          int val = 0;
          while (j < n && isdigit(s[j])) {
              val = val * 10 + (s[j] - '0');
              j++;
          }

          TreeNode* node = new TreeNode(val);
          i = j; // 更新下标

          // 递归建左子树和右子树
          node->left = dfs(s, depth + 1, i);
          node->right = dfs(s, depth + 1, i);

          return node;
      }

      TreeNode* recoverFromPreorder(string traversal) {
          n = traversal.size();
          int i = 0;
          return dfs(traversal, 0, i);
      }
  };
