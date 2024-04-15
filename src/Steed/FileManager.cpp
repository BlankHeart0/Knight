#include "FileManager.h"

void FileManager::Initialize(string knightASM_file_name)
{
    this->knightASM_file_name=knightASM_file_name;
}

void FileManager::Open()
{
    knight_file.open(knightASM_file_name,ios::in);
    if(!knight_file.is_open())
        FILEMANAGER_ERROR("Open the file error!");
}

string FileManager::ReadLine()
{
    string line_str;
    if(getline(knight_file,line_str))
        return line_str;
    //@Bug:maybe a line is ""
    return "";
}


void FileManager::Close()
{
    knight_file.close();
}