#pragma once

#include "System.h"

#define DEBUG 0

enum ErrorModule
{
    E_FILEMANAGER
};

class Diagnostor
{
public:
    void ErrorHead(ErrorModule error_module);
    void Error(ErrorModule error_module,int line,string error_message);
    void Error(ErrorModule error_module,string error_message);
};

extern Diagnostor diagnostor;
