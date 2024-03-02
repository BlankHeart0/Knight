#pragma once

#include "System.h"

enum ErrorModule
{
    E_SCANNER
};

class Diagnostor
{
public:
    void Error(ErrorModule error_module,int line,string error_message);
};

extern Diagnostor diagnostor;
