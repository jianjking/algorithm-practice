#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<map>
using namespace  std;
class Solution {
public:
    vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback, vector<string>& report, vector<int>& student_id, int k) {
        int n = student_id.size();
        unordered_map<string, int>p2;
        map<int, int>ans;
        for (auto& p : positive_feedback) {
            p2[p] = 3;
        }
        for (auto& p : negative_feedback) {
            p2[p] = -1;
        }
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < report[i].size();j++) {
                string s;
                int sum = 0;
                while (j < report[i].size() && report[i][j] != ' ') {
                    s += report[i][j];
                    j++;
                }
                ans[student_id[i]] += p2[s];

            }
        }
        vector<pair<int, int>>vec(ans.begin(), ans.end());;
        sort(vec.begin(), vec.end(), [](pair<int, int> a, pair<int, int> b) {
            if (a.second != b.second)return a.second > b.second;
            return a.first < b.first;
            });
        vector<int>arr(k);
        for (int i = 0;i < k;i++) {
            arr[i] = vec[i].first;
        }
        return arr;
    }
};