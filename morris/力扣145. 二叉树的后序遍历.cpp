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
    TreeNode* reverse1(TreeNode* start) {
        TreeNode* pre = NULL;
        TreeNode* nxt = NULL;
        while (start != NULL) {
            nxt = start->right;
            start->right = pre;
            pre = start;
            start = nxt;  
        }
        return pre;
    }
    void print(vector<int>& ans, TreeNode* start) {
        TreeNode*tail=reverse1(start);
        for (TreeNode* i = tail;i != nullptr;i = i->right)ans.push_back(i->val);
        reverse1(tail);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        TreeNode* tmp = root;
        TreeNode* r = NULL;
        vector<int>ans;
        ans.reserve(100000);
        while (tmp != NULL) {
            r = tmp->left;
            if (r != NULL) {
                while (r->right != NULL && r->right != tmp)r = r->right;
                if (r->right == NULL) {
                    r->right = tmp;
                    tmp = tmp->left;
                    continue;
                }
                else {
                    r->right = NULL;
                    print(ans,tmp->left);
                }
            }
            tmp = tmp->right;
        }
        print(ans, root);
        return ans;
    }
};