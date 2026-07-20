#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "speech_output.h"

using namespace std;

static bool is_tts_enabled()
{
    const char* tts_enabled_value =
        getenv("TTS_ENABLED");

    if (tts_enabled_value == nullptr)
    {
#ifdef _WIN32
        return true;
#else
        return false;
#endif
    }

    const string configured_value =
        tts_enabled_value;

    if (configured_value == "1")
    {
        return true;
    }

    if (configured_value == "0")
    {
        return false;
    }

    cerr
        << "[WARNING] Invalid TTS_ENABLED value: "
        << configured_value
        << ". TTS playback is disabled."
        << endl;

    return false;
}

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
    const string& display_reply,
    const string& spoken_reply)
{
    if (display_reply.empty())
    {
        return false;
    }

    cout << display_reply << endl;

    if (!cout.good())
    {
        return false;
    }

    if (!is_tts_enabled())
    {
        return true;
    }

    if (spoken_reply.empty())
    {
        cerr
            << "[WARNING] TTS content is empty. "
            << "Text output is still available."
            << endl;

        return true;
    }

    cerr << "[DEBUG-TTS] 实际传给语音的内容：<<<"
         << spoken_reply
         << ">>>" << endl;

    const bool tts_success =
        speak_reply_with_windows_tts(
            spoken_reply);

    if (!tts_success)
    {
        cerr
            << "[WARNING] TTS playback failed. "
            << "Text output is still available."
            << endl;
    }

    return true;
}

bool output_companion_reply(
    const string& reply)
{
    return output_companion_reply(
        reply,
        reply);
}
