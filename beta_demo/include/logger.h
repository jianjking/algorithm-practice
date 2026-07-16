#ifndef LOGGER_H
#define LOGGER_H

#include<bits/stdc++.h>
using namespace std;

void init_console_encoding();
string get_time_string();
void save_log(std::string user_input,
              std::string processed_input,
              std::string core_result,
              std::string final_response,
              std::string frame_path,
              bool frame_success);

#endif
