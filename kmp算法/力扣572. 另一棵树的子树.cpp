#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
void f(TreeNode* root, string& s) {
    if (root == NULL) {
        s += ",a,";
        return;
    }
    s += "," + to_string(root->val) + ",";
    f(root->left, s);
    f(root->right, s);

}
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        string s1;
        string s2;
        f(root, s1);
        f(subRoot, s2);
        return kmp(s1, s2) != -1;
    }
    void g(vector<int>& next, string& s2) {
        int m = s2.size();
        if (m == 1)return;
        next[1] = 0;
        int i = 2;
        int cn = 0;
        while (i < m) {
            if (s2[i - 1] == s2[cn]) {
                next[i] = ++cn;
                i++;
            }
            else if (cn == 0)next[i++] = 0;
            else {
                cn = next[cn];
            }
        }
    }
    int kmp(string& s1, string& s2) {
        int n = s1.size();
        int m = s2.size();
        vector<int>next(m, -1);
        g(next, s2);
        int x = 0;
        int y = 0;
        while (x < n && y < m) {
            if (s1[x] == s2[y]) {
                x++;
                y++;
            }
            else if (y == 0) {
                x++;
            }
            else {
                y = next[y];
            }
        }
        return y == m ? x - y : -1;
    }
};