#pragma once

#include "System.h"

#define DEBUG 1

enum ErrorModule
{
    E_SCANNER,E_PARSER,E_REGISTER,
    E_FILEMANAGER,E_SYMBOL
};

class Diagnostor
{
public:
    void ErrorHead(ErrorModule error_module);
    void Error(ErrorModule error_module,int line,string error_message);
    void Error(ErrorModule error_module,string error_message);
    
    void WhoAmI(string name);
};

extern Diagnostor diagnostor;
