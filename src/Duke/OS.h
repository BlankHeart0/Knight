#pragma once

#include "System.h"
#include "Parser.h"

class OperatingSystem
{
private:
    void PrintLogo();

public:
    void Flash();
    void Run();
};

extern OperatingSystem duke;