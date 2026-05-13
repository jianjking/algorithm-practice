#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>
#include<unordered_map>
using namespace std;
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

 /**
  * Definition for a binary tree node.
  * struct TreeNode {
  *     int val;
  *     TreeNode *left;
  *     TreeNode *right;
  *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
  *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  * };
  */
 class Solution {
 public:
     string getDirections(TreeNode* root, int startValue, int destValue) {
         // 1) DFS：记录父节点，并找到 start 节点
         unordered_map<TreeNode*, TreeNode*> parent;
         TreeNode* start = nullptr;

         function<void(TreeNode*, TreeNode*)> dfs = [&](TreeNode* node, TreeNode* pa) {
             if (!node) return;
             parent[node] = pa;
             if (node->val == startValue) start = node;
             dfs(node->left, node);
             dfs(node->right, node);
             };
         dfs(root, nullptr);

         if (startValue == destValue) return ""; // 起点等于终点，直接空串

         // 2) BFS：从 start 出发，三向扩展（左、右、父）
         queue<TreeNode*> q;
         q.push(start);
         unordered_set<TreeNode*> vis{ start };

         // 记录“从哪个节点来、走了哪个方向”
         unordered_map<TreeNode*, pair<TreeNode*, char>> from;
         TreeNode* dest = nullptr;

         while (!q.empty()) {
             TreeNode* node = q.front(); q.pop();
             if (node->val == destValue) { dest = node; break; }

             if (node->left && !vis.count(node->left)) {
                 vis.insert(node->left);
                 from[node->left] = { node, 'L' };
                 q.push(node->left);
             }
             if (node->right && !vis.count(node->right)) {
                 vis.insert(node->right);
                 from[node->right] = { node, 'R' };
                 q.push(node->right);
             }
             if (parent[node] && !vis.count(parent[node])) {
                 vis.insert(parent[node]);
                 from[parent[node]] = { node, 'U' };
                 q.push(parent[node]);
             }
         }

         // 3) 反向回溯并反转
         string ans;
         for (TreeNode* cur = dest; cur && cur != start; cur = from[cur].first) {
             ans.push_back(from[cur].second);
         }
         reverse(ans.begin(), ans.end());
         return ans;
     }
 };
