#pragma once

#include "System.h"
#include "Parser.h"

class OperatingSystem
{
private:
    void PrintLogo();

public: 
    bool is_stop;
    vector<string> history_command;

    void Flash();
    void HostOldTerminalRun(string command);
    void HostNewTerminalRun(string command);
    void Run();
};

extern OperatingSystem duke;