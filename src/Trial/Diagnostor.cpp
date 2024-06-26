#include "Diagnostor.h"

Diagnostor diagnostor;
bool is_upper;

void Diagnostor::ErrorHead(ErrorModule error_module)
{
    switch(error_module)
    {
        case E_SCANNER:
            cout<<"Scan Error: ";
            break;
        case E_PARSER:
            cout<<"Parse Error: ";
            break;
        case E_FILEMANAGER:
            cout<<"FileManager Error: ";
            break;
        case E_SYMBOL:
            cout<<"Symbol Error: ";
            break;
        case E_TYPE:
            cout<<"Type Error: ";
            break;
    }
}

void Diagnostor::Error(ErrorModule error_module,int line,string error_message)
{
    ErrorHead(error_module);

    cout<<"Line "<<line<<", "<<error_message<<endl;

    file_manager.Close();
    file_manager.Remove();
    exit(-1);
}

void Diagnostor::Error(ErrorModule error_module,string error_message)
{
    ErrorHead(error_module);

    cout<<error_message<<endl;

    file_manager.Close();
    file_manager.Remove();
    exit(-1);
}



void Diagnostor::WhoAmI(string name)
{
    if(DEBUG)cout<<name<<endl;
}