#include<iostream>
#include<vector>
#include<map>
using namespace std;
class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        map<long long, long long>p;
        long long day = 0;
        for (auto& p1 : tasks) {
            if (p.find(p1) == p.end()) {
                day++;
                p.insert({ p1,day });
            }
            else {
                day = max(day + 1, p[p1] + space + 1);
                p[p1] = day;
            }
        }
        return day;
    }
};