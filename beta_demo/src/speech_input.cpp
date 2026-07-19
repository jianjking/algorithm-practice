#include <iostream>
#include <string>

#include "speech_input.h"

using namespace std;

bool read_user_input(string& user_input)
{
    if (!getline(cin, user_input))
    {
        return false;
    }

    return true;
}