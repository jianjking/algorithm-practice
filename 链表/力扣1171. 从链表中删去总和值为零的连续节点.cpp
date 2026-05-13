#include<iostream>
#include<vector>
#include<unordered_map>
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
      ListNode* removeZeroSumSublists(ListNode* head) {
          ListNode dummy(0, head);
          unordered_map<int, ListNode*> last; // 前缀和 -> 最后一次出现的结点
          int sum = 0;

          // 第1遍：记录每个前缀和最后出现的位置
          for (ListNode* p = &dummy; p; p = p->next) {
              sum += p->val;
              last[sum] = p;
          }

          // 第2遍：把每个结点的 next 指到“同前缀和的最后出现位置的 next”
          sum = 0;
          for (ListNode* p = &dummy; p; p = p->next) {
              sum += p->val;
              p->next = last[sum]->next;
          }
          return dummy.next;
      }
  };
