#include<bits/stdc++.h>
#include "preprocess.h"
using namespace std;

string preprocess(string user_input)
{
    while (!user_input.empty() && user_input[0] == ' ')
    {
        user_input.erase(user_input.begin());
    }

    while (!user_input.empty() && user_input[user_input.size() - 1] == ' ')
    {
        user_input.erase(user_input.end() - 1);
    }

    return user_input;
}
