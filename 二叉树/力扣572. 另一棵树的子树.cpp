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
 bool same(TreeNode* root, TreeNode* subRoot) {
     if (subRoot == NULL)return root == NULL;
     if (root == NULL)return false;
     return (root->val == subRoot->val) && same(root->left, subRoot->left) && same(root->right, subRoot->right);
 }
 class Solution {
 public:
     bool isSubtree(TreeNode* root, TreeNode* subRoot) {
         if (root != NULL && subRoot != NULL) {
             return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot) || same(root, subRoot);
         }
         return subRoot == NULL;
     }
 };