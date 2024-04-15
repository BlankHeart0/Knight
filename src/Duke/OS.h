#pragma once

#include "System.h"
#include "Parser.h"

class OperatingSystem
{
private:
    void PrintLogo0();
    void PrintLogo1();
    void PrintLogo2();

public: 
    bool is_stop;
    vector<string> history_command;

    void Run();

    void Flash();
    void HostOldTerminalRun(string command);
    void HostNewTerminalRun(string command);
};

extern OperatingSystem duke;