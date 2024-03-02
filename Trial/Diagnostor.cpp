#include "Diagnostor.h"

Diagnostor diagnostor;

void Diagnostor::Error(ErrorModule error_module,int line,string error_message)
{
    switch(error_module)
    {
        case E_SCANNER:
            cout<<"Scan Error: ";
            break;
    }

    cout<<"Line "<<line<<", "<<error_message<<endl;

    exit(-1);
}
