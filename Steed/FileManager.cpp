#include "FileManager.h"

void FileManager::Initialize(string knightASM_file_name)
{
    this->knightASM_file_name=knightASM_file_name;
}

void FileManager::Open()
{
    knightASM_file.open(knightASM_file_name,ios::in);
    if(!knightASM_file.is_open())
        FILEMANAGER_ERROR("Open the input file error!");
}

string FileManager::ReadLine()
{
    string line_str;
    if(getline(knightASM_file,line_str))
        return line_str;
    //@Bug:maybe a line is ""
    return "";
}


void FileManager::Close()
{
    knightASM_file.close();
}