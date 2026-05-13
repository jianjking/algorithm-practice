#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int resum(int x, int cnt, int ans, vector<int>& card) {
    int n = card.size();
    for (int i = cnt;i < n;i++) {
        if (card[i] % 2 != x % 2) {
            return ans - x + card[i];
        }
    }
    return 0;
}
class Solution {
public:
    int maximumScore(vector<int>& cards, int cnt) {
        sort(cards.begin(), cards.end(), [](int a, int b) {
            return a > b;
            });
        int n = cards.size();
        int ans = 0;
        for (int i = 0;i < cnt;i++) {
            ans += cards[i];
        }
        if (ans % 2 == 0)return ans;
        int ans1 = resum(cards[cnt - 1], cnt, ans, cards);
        for (int i = cnt - 2;i >= 0;i--) {
            if (cards[i] % 2 != cards[cnt - 1] % 2) {
                ans1 = max(ans1, resum(cards[i], cnt, ans, cards));
            }
        }
        return ans1;
    }
};