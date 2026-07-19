#include <iostream>
#include <string>

#include "speech_output.h"

using namespace std;

bool output_companion_reply(
    const string& reply)
{
    if (reply.empty())
    {
        return false;
    }

    cout << reply << endl;

    return cout.good();
}