#include<iostream>
#include<vector>
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
      int mx;
      int mn;

      // 遍历整个树以确定最小和最大列
      void calculateMinMax(TreeNode* node, int col, int& mn, int& mx) {
          if (!node) return;
          mn = min(mn, col);
          mx = max(mx, col);
          calculateMinMax(node->left, col - 1, mn, mx);
          calculateMinMax(node->right, col + 1, mn, mx);
      }

      // 收集节点到对应的列中，并记录行号和值
      void dfs(vector<vector<pair<int, int>>>& ans, TreeNode* root, int row, int col) {
          if (!root) return;
          ans[col - mn].push_back({ row, root->val });
          dfs(ans, root->left, row + 1, col - 1);
          dfs(ans, root->right, row + 1, col + 1);
      }

      vector<vector<int>> verticalTraversal(TreeNode* root) {
          mx = INT_MIN;
          mn = INT_MAX;
          calculateMinMax(root, 0, mn, mx); // 正确计算所有列的范围

          vector<vector<pair<int, int>>> ans(mx - mn + 1);
          dfs(ans, root, 0, 0);

          // 对每列按行号及值排序
          for (auto& col : ans) {
              sort(col.begin(), col.end(), [](auto& a, auto& b) {
                  return a.first == b.first ? a.second < b.second : a.first < b.first;
                  });
          }

          // 转换为结果格式
          vector<vector<int>> res;
          for (auto& col : ans) {
              res.push_back({});
              for (auto& p : col) {
                  res.back().push_back(p.second);
              }
          }
          return res;
      }
  };