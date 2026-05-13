#include<iostream>
#include<vector>
using namespace std;
#include <bits/stdc++.h>
using namespace std;

// 二叉树节点定义（力扣默认给的）
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<int> flipped;  // 记录需要翻转的节点
    int index;            // voyage 的当前位置
    vector<int> voyage;   // 目标序列

    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        flipped.clear();
        index = 0;
        this->voyage = voyage;

        dfs(root);

        // 如果失败（返回 -1）
        if (!flipped.empty() && flipped[0] == -1) {
            flipped.clear();
            flipped.push_back(-1);
        }
        return flipped;
    }

    void dfs(TreeNode* node) {
        if (!node) return;

        // 1. 检查当前节点是否匹配
        if (node->val != voyage[index++]) {
            flipped.clear();
            flipped.push_back(-1); // 标记失败
            return;
        }

        // 2. 判断是否需要翻转
        if (index < (int)voyage.size() && node->left && node->left->val != voyage[index]) {
            flipped.push_back(node->val); // 标记要翻转的节点
            dfs(node->right); // 先访问右子树（模拟翻转）
            dfs(node->left);
        }
        else {
            dfs(node->left);
            dfs(node->right);
        }
    }
};
