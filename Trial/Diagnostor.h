#pragma once

#include "System.h"

#define DEBUG 1

enum ErrorModule
{
    E_SCANNER,E_PARSER
};

class Diagnostor
{
public:
    void Error(ErrorModule error_module,int line,string error_message);
    void WhoAmI(string name);
};

extern Diagnostor diagnostor;
