#include<iostream>
#include<vector>
#include<algorithm>
#include<deque>
using namespace std;
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(deck.begin(), deck.end());
        int n = deck.size();
        vector<int>ans(n);
        deque<int>f;
        for (int i = 0;i < n;i++) {
            f.push_back(i);
        }
        int cnt = 0;
        while (!f.empty()) {
            int num = f.front();
            f.pop_front();
            ans[num] = deck[cnt++];
            int tmp = f.front();
            f.pop_front();
            if (f.empty())ans[tmp] = deck[cnt]++;
            else f.push_back(tmp);
        }
        return ans;
    }
};