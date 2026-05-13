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
      vector<int> dfn;
      vector<int> size1;
      vector<int> deep;
      int cnt;
      void f(TreeNode* root, int k) {
          int a = root->val;
          dfn[a] = cnt++;
          deep[dfn[a]] = k;
          size1[dfn[a]] = 1;
          if (root->left != nullptr) {
              f(root->left, k + 1);
              size1[dfn[a]] += size1[dfn[root->left->val]];
          }
          if (root->right != nullptr) {
              f(root->right, k + 1);
              size1[dfn[a]] += size1[dfn[root->right->val]];
          }
      }

      vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        
          int totalNodes = 100010; 

          dfn.resize(totalNodes + 1);
          size1.resize(totalNodes + 1, 1);
          deep.resize(totalNodes + 1, 0);
          cnt = 1;

          f(root, 0);

          int m = cnt - 1;  

          vector<int> maxl(m + 2, 0);
          int currentMax = 0;
          for (int i = 1; i <= m; i++) {
              currentMax = max(deep[i], currentMax);
              maxl[i] = currentMax;
          }

          vector<int> maxr(m + 2, 0);
          currentMax = 0;
          for (int i = m; i >= 1; i--) {
              currentMax = max(deep[i], currentMax);
              maxr[i] = currentMax;
          }

          vector<int> ans;

          for (int q : queries) {
              int idx = dfn[q];  
              int leftmax = (idx - 1 >= 1 ? maxl[idx - 1] : 0);
              int rightIndex = idx + size1[idx];
              int rightmax = (rightIndex <= m ? maxr[rightIndex] : 0);
              ans.push_back(max(leftmax, rightmax));
          }
          return ans;
      }
  };