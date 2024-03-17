#pragma once

#include "System.h"
#include "Diagnostor.h"

class FileManager
{
private:
    string input_file_name;
    string output_file_name;

    ifstream input_file;
    ofstream output_file;

public:
    string source;

    void Initialize(string input_file_name);
    void Initialize(string input_file_name,string output_file_name);

    void Open();
    void Load();
    void Write(string code_ks);
    void WriteComma();
    void WriteEndl();
    void Close();
};

extern FileManager file_manager;

#define FILEMANAGER_ERROR(error_message)                  \
        do{                                               \
            diagnostor.Error(E_FILEMANAGER,error_message);\
        }while(0)

#define WriteGeneralRegisterName(r_i)                        \
        do{                                                         \
            file_manager.Write(general_register.Name(r_i));  \
        }while(0)
