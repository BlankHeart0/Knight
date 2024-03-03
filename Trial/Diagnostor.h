#pragma once

#include "System.h"

#define DEBUG 0

enum ErrorModule
{
    E_SCANNER,E_PARSER,E_REGISTER,E_FILEMANAGER
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
