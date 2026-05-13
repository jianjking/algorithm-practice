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
  struct GGG {
      int n;
      int m;
      int step;
 };
class Solution {
public:
    GGG f(TreeNode* root) {
        if (root == nullptr)return { 0,0,0 };
        GGG l = f(root->left);
        GGG r = f(root->right);
        int n = l.n + r.n + 1;
        int m = l.m + r.m + root->val;
        int step = l.step + r.step + abs(l.n - l.m) + abs(r.m - r.n);
        return { n,m,step };
    }
    int distributeCoins(TreeNode* root) {
        return f(root).step;
    }
};