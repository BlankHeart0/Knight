#include "FileManager.h"

bool FileManager::InstallInitialize(string KnightASM_file_name)
{
    this->input_file_name=KnightASM_file_name;

    int end=KnightASM_file_name.find(".ks");
    if(end==string::npos)
    {
        cout<<"You can only install package file!"<<endl;
        return false;
    }   

    this->output_file_name=KnightASM_file_name.substr(0,end);
    return true;
}

bool FileManager::ChpermInitialize(string KnightAPP_file_name)
{
    if(KnightAPP_file_name.find(".ks")!=string::npos)
    {
        cout<<"You can only change application's permission!"<<endl;
        return false;
    }

    string mv="mv "+KnightAPP_file_name+" "+KnightAPP_file_name+".app";
    system(mv.c_str());
    
    this->input_file_name=KnightAPP_file_name+".app";
    this->output_file_name=KnightAPP_file_name;
    return true;
}

bool FileManager::Open()
{
    input_file.open(input_file_name,ios::in);
    if(!input_file)
    {
        cout<<"Open the package file error!"<<endl;
        return false;
    }

    output_file.open(output_file_name,ios::out);
    if(!output_file)
    {
        cout<<"Open the application file error!"<<endl;
        return false;
    }

    return true;
}

string FileManager::ReadLine()
{
    string line_str;
    if(getline(input_file,line_str))
        return line_str;
    return "";
}

void FileManager::Write(string application_code)
{
    output_file<<application_code;
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
    remove(input_file_name.c_str());
}