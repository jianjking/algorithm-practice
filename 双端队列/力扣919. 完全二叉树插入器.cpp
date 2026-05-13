#include<iostream>
#include<vector>
#include<queue>
using namespace std;
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;

      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
class CBTInserter {
public:
    vector<TreeNode*>father;
    vector<int>degree;
    TreeNode* r;
    int sum;
    CBTInserter(TreeNode* root) {
        father.clear();
        degree.clear();
        sum = 0;
        r = root;
        father.reserve(1e5);
        degree.reserve(1e5);
        deque<TreeNode*>tmp;
        tmp.push_back(root);
        while (!tmp.empty()) {
            TreeNode* t = tmp.front();
            int cnt = 0;
            tmp.pop_front();
            if (t->left != NULL) {
                cnt++;
                tmp.push_back(t->left);
            }
            if (t->right != NULL) {
                cnt++;
                tmp.push_back(t->right);
            }
            if (cnt < 2) {
                father.push_back(t);
                degree.push_back(cnt);
            }
        }
    }
    int insert(int val) {
        TreeNode* tmp = father[sum];
        TreeNode* nxt = new TreeNode(val);
        if (degree[sum] == 0) {
            tmp->left = nxt;
            degree[sum]++;
        }
        else {
            tmp->right = nxt;
            sum++;
        }
        degree.push_back(0);
        father.push_back(nxt);
        return tmp->val;
    }

    TreeNode* get_root() {
        return r;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */