#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    bool asteroidsDestroyed(long long mass, vector<int>& asteroids) {
        sort(asteroids.begin(), asteroids.end());
        for (auto& p : asteroids) {
            if (mass < p)return false;
            mass += p;
        }
        return true;
    }
};