#include<iostream>
#include<vector>
using namespace std;
//贪心分析
// 0：节点没有被覆盖
//1 节点被覆盖且没有摄像头
//2节点被覆盖并且有摄像头
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
    int f(TreeNode* root) {
        if (root == NULL)return 1;
        int l = f(root->left);
        int r = f(root->right);
        if (l == 1 && r == 1)return 0;
        if (l == 0 || r == 0) {
            ans++;
            return 2;
        }
        return 1;
    }
    int ans;
    int minCameraCover(TreeNode* root) {
        ans = 0;
        if (f(root) == 0)ans++;
        return ans;
    }
};