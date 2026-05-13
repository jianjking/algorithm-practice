#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;
class Solution {
public:
    string s1, s2;
    int countBalls(int lowLimit, int highLimit) {
        s1 = to_string(highLimit);
        s2 = to_string(lowLimit);
        s2 = string(s1.size() - s2.size(), 0) + s2;
        vector<vector<int>>map(s1.size(), vector<int>(highLimit + 1, -1));
    }
};