#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "speech_output.h"

using namespace std;

static bool speak_reply_with_windows_tts(
    const string& reply)
{
    const string text_file_path =
        "speech_output_temp.txt";

    const string script_file_path =
        "speech_output_temp.ps1";

    ofstream text_file(
        text_file_path,
        ios::binary | ios::trunc);

    if (!text_file.is_open())
    {
        return false;
    }

    text_file.write(
        reply.data(),
        static_cast<streamsize>(reply.size()));

    text_file.close();

    if (text_file.fail())
    {
        remove(text_file_path.c_str());
        return false;
    }

    ofstream script_file(
        script_file_path,
        ios::binary | ios::trunc);

    if (!script_file.is_open())
    {
        remove(text_file_path.c_str());
        return false;
    }

    const string script =
        "$ErrorActionPreference = \"Stop\"\r\n"
        "$speaker = $null\r\n"
        "$success = $false\r\n"
        "try {\r\n"
        "    Add-Type -AssemblyName System.Speech\r\n"
        "    $text = Get-Content -Raw -Encoding UTF8 "
        "\"speech_output_temp.txt\"\r\n"
        "    $speaker = New-Object "
        "System.Speech.Synthesis.SpeechSynthesizer\r\n"
        "    $speaker.SelectVoice("
        "\"Microsoft Huihui Desktop\")\r\n"
        "    $speaker.Speak($text)\r\n"
        "    $success = $true\r\n"
        "}\r\n"
        "catch {\r\n"
        "    [Console]::Error.WriteLine("
        "$_.Exception.Message)\r\n"
        "}\r\n"
        "finally {\r\n"
        "    if ($null -ne $speaker) {\r\n"
        "        $speaker.Dispose()\r\n"
        "    }\r\n"
        "}\r\n"
        "if ($success) {\r\n"
        "    exit 0\r\n"
        "}\r\n"
        "else {\r\n"
        "    exit 1\r\n"
        "}\r\n";

    script_file.write(
        script.data(),
        static_cast<streamsize>(script.size()));

    script_file.close();

    if (script_file.fail())
    {
        remove(text_file_path.c_str());
        remove(script_file_path.c_str());
        return false;
    }

    const string command =
        "powershell.exe -NoProfile "
        "-ExecutionPolicy Bypass "
        "-File \"speech_output_temp.ps1\"";

    const int command_result =
        system(command.c_str());

    remove(text_file_path.c_str());
    remove(script_file_path.c_str());

    return command_result == 0;
}

bool output_companion_reply(
    const string& reply)
{
    if (reply.empty())
    {
        return false;
    }

    cout << reply << endl;

    if (!cout.good())
    {
        return false;
    }

    const bool tts_success =
        speak_reply_with_windows_tts(reply);

    if (!tts_success)
    {
        cerr
            << "[WARNING] TTS playback failed. "
            << "Text output is still available."
            << endl;
    }

    return true;
}