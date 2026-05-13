#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int>cnt;
        for (auto& p : nums) {
            cnt[p]++;
        }
        int ans = 0;
        for (auto& p : nums) {
            if (p == 1) {
                ans = max(ans, cnt[p] % 2 == 0 ? cnt[p] - 1 : cnt[p]);
                continue;
            }
            long long tmp = p;
            int sum = 0;
            while (true) {
                if (cnt[tmp] >= 2)sum += 2;
                else if (cnt[tmp] == 1) {
                    sum += 1;
                    break;
                }
                else {
                    sum--;
                    break;
                }
                tmp *= tmp;
            }
            ans = max(sum, ans);
        }
        return ans;
    }
};
