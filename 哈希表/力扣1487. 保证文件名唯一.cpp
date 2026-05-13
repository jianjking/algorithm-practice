#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;
class Solution {
public:
    string create(string s,int k) {
        return s + '(' + to_string(k) + ')';
    }
    vector<string> getFolderNames(vector<string>& names) {
        unordered_map<string, int>fnd;
        vector<string>res;
        for (auto& p : names) {
            if (!fnd.count(p)) {
                res.push_back(p);
                fnd[p] = 1;
            }
            else {
                int k = fnd[p];
                while (fnd.count(create(p, k)) == 1)k++;
                res.push_back(create(p, k));
                fnd[p] = k+1;
                fnd[create(p, k)] = 1;
            }
        }
        return res;
    }
};