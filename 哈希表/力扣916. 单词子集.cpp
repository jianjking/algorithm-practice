#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    vector<string> wordSubsets(vector<string>& A, vector<string>& B)
    {
        vector<int> B_char_freq(26, 0);     //B看成一个很大的stirng。A要想符合条件，26个字母都要足够
        for (string b : B)
        {
            vector<int> v = func_count(b);
            for (int i = 0; i < 26; i++)
                B_char_freq[i] = max(B_char_freq[i], v[i]);
        }
        vector<string> res;
        for (string a : A)
        {
            vector<int> A_char_freq = func_count(a);
            bool flag = true;
            for (int i = 0; i < 26; i++)
                if (A_char_freq[i] < B_char_freq[i])
                {
                    flag = false;
                    break;
                }
            if (flag == true)
                res.push_back(a);
        }
        return res;
    }

    vector<int> func_count(string& s)
    {
        vector<int> char_freq(26, 0);
        for (char c : s)
            char_freq[c - 'a']++;
        return char_freq;
    }
};

