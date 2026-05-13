#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {} };
  class Solution {
  public:
      int minimumOperations(TreeNode* root) {
          queue<TreeNode*>f;
          f.push(root);
          int ans = 0;
          while (!f.empty()) {
              int sz = f.size();
              vector<int>b(sz);
              for (int i = 0;i < sz;i++) {
                  TreeNode* tmp = f.front();
                  f.pop();
                  b[i] = tmp->val;
                  if (tmp->left)f.push(tmp->left);
                  if (tmp->right)f.push(tmp->right);
              }
              vector<int>a = b;
              sort(a.begin(), a.end());
              map<int, int>cnt;
              for (int i = 0;i < sz;i++)cnt[a[i]] = i;
              for (int i = 0;i < sz;i++) {
                  while (a[i] != b[i]) {
                      swap(b[i], b[cnt[b[i]]]);
                      ans++;
                  }
              }
          }
          return ans;
      }
  };
