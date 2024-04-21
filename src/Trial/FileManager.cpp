#include "FileManager.h"

FileManager file_manager;

void FileManager::Initialize(string input_file_name)
{
    this->input_file_name=input_file_name;
    this->output_file_name=input_file_name+"s";
}

void FileManager::Initialize(string input_file_name,string output_file_name)
{
    this->input_file_name=input_file_name;
    this->output_file_name=output_file_name;
}

string FileManager::GetInputfile()
{
    string tab_str="\t";
    if(input_file_name.size()<8)tab_str+="\t";

    return input_file_name+tab_str;
}



void FileManager::Open()
{
    input_file.open(input_file_name,ios::in);
    if(!input_file.is_open())
        FILEMANAGER_ERROR("Open the input file error!");

    //Create or Empty the output file
    output_file.open(output_file_name,ios::out);
    if(!output_file.is_open())
        FILEMANAGER_ERROR("Empty the output file error!");
    output_file.close();

    //Ready to write
    output_file.open(output_file_name,ios::app);
    if(!output_file.is_open())
        FILEMANAGER_ERROR("Open the output file error!");
}

void FileManager::Load()
{
    source="";
    string buffer;
    while(getline(input_file,buffer))
    {
        source+=buffer;
        source+='\n';
    }
}

void FileManager::Write(string code_ks)
{
    output_file<<code_ks;
}

void FileManager::WriteComma()
{
    output_file<<",";
}

void FileManager::WriteEndl()
{
    output_file<<endl;
}

void FileManager::Close()
{
    input_file.close();
    output_file.close();
}

void FileManager::Remove()
{
    remove(output_file_name.c_str());
}
