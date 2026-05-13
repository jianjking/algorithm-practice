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
    pair<vector<int>, int> dfs(TreeNode* root, int distance) {
        vector<int>depth(distance + 1, 0);
        if (root->left == NULL && root->right == NULL) {
            depth[0] = 1;
            return make_pair( depth,0 );
        }
        int cnt = 0;
        pair<vector<int>, int>left;
        if (root->left != NULL) {
            left = dfs(root->left, distance);
            cnt += left.second;
            for (int i = 0;i < distance;i++) {
                depth[i + 1] += left.first[i];
            }
        }
        pair<vector<int>, int>right;
        if (root->right != NULL) {
            right = dfs(root->right, distance);
            cnt += right.second;
            for (int i = 0;i < distance;i++) {
                depth[i + 1] += right.first[i];
            }
        }
        for (int i = 0;i < left.first.size();i++) {
            for (int j = 0;j < right.first.size();j++) {
                if (i + j + 2 <= distance) {
                    cnt += left.first[i] * right.first[j];
                }
             
            }
        }
        return { depth,cnt };
    }
    int countPairs(TreeNode* root, int distance) {
        pair<vector<int>,int>tmp=dfs(root, distance);
        return tmp.second;
    }
};