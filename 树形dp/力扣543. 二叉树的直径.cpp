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
 struct GGG{
     int h;
     int m;
 };
 GGG f(TreeNode* root) {
     if (root == nullptr)return { 0,0 };
     GGG l = f(root->left);
     GGG r = f(root->right);
     int h = max(l.h, r.h) + 1;
     int m = max(max(l.m, r.m), l.h + r.h);
     return { h,m };
 }
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        return f(root).m;
    }
};