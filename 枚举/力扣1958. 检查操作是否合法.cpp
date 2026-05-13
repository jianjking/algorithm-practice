#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool checkMove(vector<vector<char>>& board, int x, int y, char color) {
        board[x][y] = color;
        int n = board.size();
        char limit = color == 'W' ? 'B' : 'W';
        int arr[8][2] = { {-1,1},{1,-1},{1,1},{-1,-1},{1,0},{-1,0},{0,-1},{0,1} };
        for (int i = 0;i < 8;i++) {
            int a = arr[i][0];
            int b = arr[i][1];

            if (a + x >= 0 && a + x < n && b + y >= 0 && b + y < n) {
                if (board[a + x][b + y] != limit)continue;
                for (int i = x + 2 * a, j = 2 * b + y;i >= 0 && i < n && j >= 0 && j < n;i += a, j += b) {
                    if (board[i][j] == '.')break;
                    if (board[i][j] == color)return true;
                }
           }
        }
        return false;
    }
};