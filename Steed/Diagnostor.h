#pragma once

#include "System.h"

enum ErrorModule
{
    E_FILEMANAGER,E_FUNCTION
};

class Diagnostor
{
private:
    void ErrorHead(ErrorModule error_module);

public:
    void Error(ErrorModule error_module,int line,string error_message);
    void Error(ErrorModule error_module,string error_message);
};

extern Diagnostor diagnostor;
