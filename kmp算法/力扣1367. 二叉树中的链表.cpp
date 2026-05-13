#include<iostream>
#include<vector>
#include<string>
using namespace std;

 struct ListNode {
      int val;
      ListNode *next;
   ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
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
       vector<int>next;
       bool dfs(TreeNode* root, int i, vector<int>& arr) {
           if (i == arr.size())return true;
           if (root == NULL)return false;
           while (i >= 0) {
               if (arr[i] == root->val)break;
               else {
                   i = next[i];
               }
           }
           return dfs(root->left, i + 1, arr) || dfs(root->right, i + 1, arr);
       }
       bool isSubPath(ListNode* head, TreeNode* root) {
           vector<int>arr;
           while (head != NULL) {
               arr.push_back(head->val);
               head = head->next;
           }
           next.assign(arr.size(), -1);
           if (next.size() != 1) {
               next[1] = 0;
               int i = 2;
               int cn = 0;
               while (i < arr.size()) {
                   if (arr[i - 1] == arr[cn]) {
                       next[i++] = ++cn;
                   }
                   else if (cn == 0) {
                       next[i++] = 0;
                   }
                   else {
                       cn = next[cn];
                   }
               }
           }
           return dfs(root, 0, arr);

       }
   };