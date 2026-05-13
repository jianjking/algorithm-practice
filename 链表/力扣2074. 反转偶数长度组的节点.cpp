#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
 struct ListNode {
      int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

 class Solution {
 public:
     ListNode* reverseEvenLengthGroups(ListNode* head) {
         if (!head) return head;

         int cnt = 1;               // 预期本组长度
         ListNode* groupStart = head;
         ListNode* cur = head;

         // 逐组处理
         while (groupStart) {
             // ——第一步：先数这一组实际能走到多少个节点
             int groupSize = 0;
             ListNode* t = groupStart;
             while (t && groupSize < cnt) {
                 groupSize++;
                 t = t->next;
             }
             // 此时，t 是“本组第 groupSize+1 个节点”的指针（或者已经到 nullptr）

             // ——第二步：如果 groupSize 是偶数，就反转这一段节点的值
             if (groupSize % 2 == 0) {
                 // 用栈+队列把 groupStart 开始的 groupSize 个节点入栈，把它们的原值进队
                 stack<ListNode*> st;
                 queue<int> vals;
                 ListNode* r = groupStart;
                 for (int k = 0; k < groupSize; k++) {
                     st.push(r);
                     vals.push(r->val);
                     r = r->next;
                 }
                 // 然后出栈/出队，把原来的数值倒序写回
                 while (!st.empty()) {
                     st.top()->val = vals.front();
                     st.pop();
                     vals.pop();
                 }
             }

             // ——第三步：跳到本组末尾，准备开始下一组
             // groupStart 向后走 groupSize 步，就到了下一组的开头
             for (int k = 0; k < groupSize; k++) {
                 if (groupStart)
                     groupStart = groupStart->next;
             }
             cnt++;
         }

         return head;
     }
 };
