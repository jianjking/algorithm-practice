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
      int minDepth(TreeNode* root) {
          if (!root)
              return 0;

          TreeNode* cur = root;
          TreeNode* mostRight = nullptr;

          // preLevel tracks the depth (number of nodes) from root to the current 'cur' when first visiting it
          int preLevel = 0;
          // ans will hold the minimum depth found among all leaf nodes
          int ans = INT_MAX;
          // rightLen is used to count the number of nodes on the right-boundary path in the left subtree
          int rightLen;

          // Morris traversal loop
          while (cur) {
              mostRight = cur->left;
              if (mostRight) {
                  // Find the inorder predecessor (rightmost node in left subtree)
                  rightLen = 1;
                  while (mostRight->right && mostRight->right != cur) {
                      mostRight = mostRight->right;
                      rightLen++;
                  }
                  if (!mostRight->right) {
                      // First time we see 'cur': increment depth and thread back
                      preLevel++;
                      mostRight->right = cur;
                      cur = cur->left;
                      continue;
                  }
                  else {
                      // Second time we see 'cur': we're returning from its left subtree
                      // If that predecessor has no left child, it's a leaf¡ªupdate ans
                      if (!mostRight->left) {
                          ans = min(ans, preLevel);
                      }
                      // Undo the depth increment for the entire left subtree
                      preLevel -= rightLen;
                      // Remove the thread
                      mostRight->right = nullptr;
                  }
              }
              else {
                  // No left subtree: visit cur directly by bumping depth
                  preLevel++;
              }
              // Move to right subtree
              cur = cur->right;
          }

          // Finally, handle the rightmost path from root to its deepest right-leaf
          rightLen = 1;
          cur = root;
          while (cur->right) {
              cur = cur->right;
              rightLen++;
          }
          // If that last node is a leaf, update ans
          if (!cur->left) {
              ans = min(ans, rightLen);
          }

          return ans;
      }
  };
