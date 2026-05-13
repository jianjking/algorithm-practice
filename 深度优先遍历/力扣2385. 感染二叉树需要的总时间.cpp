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
      int amountOfTime(TreeNode* root, int start) {
          const int MAXV = 100000;
          vector<vector<int>> graph(MAXV + 1);
          vector<int> deep(MAXV + 1, 0);

          // 1) 建图，避开自环
          dfs(root, -1, graph);

          // 2) 从 start 递归／BFS 计算所有点到 start 的距离
          f(start, -1, graph, 0, deep);

          // 3) 找最远距离
          int ans = 0;
          for (int d : deep)
              ans = max(ans, d);
          return ans;
      }

  private:
      void dfs(TreeNode* node, int parent, vector<vector<int>>& g) {
          if (parent != -1) {
              g[node->val].push_back(parent);
              g[parent].push_back(node->val);
          }
          if (node->left)  dfs(node->left, node->val, g);
          if (node->right) dfs(node->right, node->val, g);
      }

      void f(int u, int parent, vector<vector<int>>& g, int dist, vector<int>& deep) {
          deep[u] = dist;
          for (int v : g[u]) {
              if (v == parent) continue;
              f(v, u, g, dist + 1, deep);
          }
      }
  };
