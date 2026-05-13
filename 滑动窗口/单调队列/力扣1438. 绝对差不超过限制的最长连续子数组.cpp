#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
private:
    int* minq; // 单调递增队列（维护最小值）
    int* maxq; // 单调递减队列（维护最大值）
    int min_head, min_tail; // minq的头尾指针
    int max_head, max_tail; // maxq的头尾指针

public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        if (n == 0) return 0;

        // 动态分配队列内存
        minq = new int[n];
        maxq = new int[n];
        min_head = min_tail = 0;
        max_head = max_tail = 0;

        int max_len = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            int num = nums[right];

            // 维护minq：移除尾部比当前元素大的元素，保持递增
            while (min_tail > min_head && num < minq[min_tail - 1]) {
                min_tail--;
            }
            minq[min_tail++] = num;

            // 维护maxq：移除尾部比当前元素小的元素，保持递减
            while (max_tail > max_head && num > maxq[max_tail - 1]) {
                max_tail--;
            }
            maxq[max_tail++] = num;

            // 当前窗口的极值差超过limit时，收缩左边界
            while (maxq[max_head] - minq[min_head] > limit) {
                if (nums[left] == minq[min_head]) {
                    min_head++;
                }
                if (nums[left] == maxq[max_head]) {
                    max_head++;
                }
                left++;
            }

            // 更新最大长度
            max_len = max(max_len, right - left + 1);
        }

        // 释放动态分配的内存
        delete[] minq;
        delete[] maxq;

        return max_len;
    }
};