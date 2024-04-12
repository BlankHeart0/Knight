#pragma once

#include "System.h"
#include "Diagnostor.h"

class FileManager
{
private:
    string knightASM_file_name;
    ifstream knightASM_file;

public:
    void Initialize(string knightASM_file_name);
    void Open();
    string ReadLine();
    void Close();
};

#define FILEMANAGER_ERROR(error_message)                  \
        do{                                               \
            diagnostor.Error(E_FILEMANAGER,error_message);\
        }while(0)
