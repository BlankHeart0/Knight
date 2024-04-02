#include "Diagnostor.h"

Diagnostor diagnostor;

void Diagnostor::ErrorHead(ErrorModule error_module)
{
    switch(error_module)
    {
        case E_FILEMANAGER:
            cout<<"FileManager Error: ";
            break;
        case E_FUNCTION:
            cout<<"Function Error: ";
            break;
        case E_TYPE:
            cout<<"Type Error: ";
            break;
        case E_REGISTER:
            cout<<"Register Error: ";
            break;
    }
}

void Diagnostor::Error(ErrorModule error_module,int line,string error_message)
{
    ErrorHead(error_module);

    cout<<"Line "<<line<<", "<<error_message<<endl;

    exit(-1);
}

void Diagnostor::Error(ErrorModule error_module,string error_message)
{
    ErrorHead(error_module);

    cout<<error_message<<endl;

    exit(-1);
}
