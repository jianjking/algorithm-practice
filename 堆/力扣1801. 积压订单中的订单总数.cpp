#include<iostream>
#include<vector>
#include<set>
using namespace std;
struct compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b)const {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    }
};
struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b)const {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    }
};
const int mod = 1e9 + 7;
class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        multiset<pair<int, int>, compare>f1;
        multiset<pair<int, int>, Compare>f2;
        for (auto& p : orders) {
            int a = p[0];
            int b = p[1];
            if (p[2] == 0) {
                while (!f1.empty() && b > 0 && (*f1.begin()).first <= a) {
                    int c = (*f1.begin()).first;
                    int d = (*f1.begin()).second;
                    f1.erase(f1.begin());
                    if (d <= b)b -= d;
                    else {
                        f1.insert({ c,d -= b });
                        b = 0;
                    }
                }
                if (b != 0)f2.insert({ a,b });
            }
            else {
                while (!f2.empty() && b > 0 && (*f2.begin()).first >= a) {
                    int c = (*f2.begin()).first;
                    int d = (*f2.begin()).second;
                    f2.erase(f2.begin());
                    if (d <= b)b -= d;
                    else {
                        f2.insert({ c,d -= b });
                        b = 0;
                    }
                }
                if (b != 0)f1.insert({ a,b });
            }
        }
        int ans = 0;
        for (auto& p : f1) {
            ans = (ans + p.second) % mod;
        }
        for (auto& p : f2) {
            ans = (ans + p.second) % mod;
        }
        return ans;
    }
};