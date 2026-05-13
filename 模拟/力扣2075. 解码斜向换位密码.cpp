#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        int n = encodedText.size();
        int cols = n / rows;
        vector<vector<char>> nums(rows, vector<char>(cols, ' '));

        for (int i = 0; i < n; i++) {
            nums[i / cols][i % cols] = encodedText[i];
        }

        string ans;
        // 第一行向右（不重复 (0,0)）
        for (int startCol = 0; startCol < cols; startCol++) {
            int i = 0, j = startCol;
            bool an = false;
            string tmp;
            while (i < rows && j < cols) {
               
               ans += nums[i][j];
                i++; j++;
            }
 
        }
        while (ans.size() && ans.back() == ' ') {
            ans.pop_back();
        }
       
        return ans;
    }
};
