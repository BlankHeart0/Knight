#pragma once

#include "System.h"

class FileManager
{
private:
    string input_file_name;
    string output_file_name;

    ifstream input_file;
    ofstream output_file;

public:
    bool InstallInitialize(string KnightASM_file_name);
    bool ChpermInitialize(string KnightAPP_file_name);
    bool Open();
    string ReadLine();
    void Write(string application_code);
    void WriteEndl();
    void Close();
    void Remove();
};