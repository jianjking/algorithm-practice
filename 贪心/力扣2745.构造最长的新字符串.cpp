#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int longestString(int x, int y, int z) {
        int n = min(x, y);
        return x != y ? 4 * n + 2 + 2 * z : 4 * n + 2 * z;
    }
};