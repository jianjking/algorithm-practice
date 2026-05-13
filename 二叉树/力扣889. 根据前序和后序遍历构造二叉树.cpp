#include<iostream>
#include<vector>
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

  class Solution {
  public:
      // pre[l..r] 对应 post[l1..r1]
      TreeNode* dfs(int l, int r, int l1, int r1,
          const vector<int>& pre,
          const unordered_map<int, int>& f) {
          if (l > r) return nullptr;           // 区间空
          if (l == r) return new TreeNode(pre[l]); // 只有一个节点
          // 下一个 pre[l+1] 肯定是左子树的根
          int leftRoot = pre[l + 1];
          int idx = f.at(leftRoot);            // 在 post 序列中的下标
          int sz = idx - l1 + 1;               // 左子树节点数

          TreeNode* left = dfs(l + 1, l + sz, l1, idx, pre, f);
          TreeNode* right = dfs(l + sz + 1, r, idx + 1, r1 - 1, pre, f);
          return new TreeNode(pre[l], left, right);
      }

      TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
          int n = pre.size();
          unordered_map<int, int> f;
          for (int i = 0; i < n; i++) {
              f[post[i]] = i;
          }
          return dfs(0, n - 1, 0, n - 1, pre, f);
      }
  };
