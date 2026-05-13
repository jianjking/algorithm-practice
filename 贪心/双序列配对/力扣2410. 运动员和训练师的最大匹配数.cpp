#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(players.begin(), players.end());
        sort(trainers.begin(), trainers.end());
        int n = players.size();
        int m = trainers.size();
        int ans = 0;
        for (int l1 = 0, l2 = 0;l1 < n && l2 < m;) {
            if (players[l1] <= trainers[l2]) {
                l1++;
                l2++;
                ans++;
            }
            else {
                l2++;
            }
        }
        return ans;
    }
};