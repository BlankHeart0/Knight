#include "Register.h"

GeneralRegister general_register;

string GeneralRegister::Name(int r_i)
{
    string register_name="";

    register_name+=(is_upper?"R":"r")+to_string(r_i);

    //unnecessary
    // register_name+="(";
    // register_name+=GetReg(r_i).type.Str();
    // register_name+=")";

    return register_name;
}

Register& GeneralRegister::GetReg(int r_i)
{
    return table[r_i];
}



int GeneralRegister::Alloc(Type type)
{
    int r_i=0;
    
    for(;r_i<table.size();r_i++)
    {
        if(table[r_i].free)
        {
            table[r_i].type=type;
            table[r_i].free=false;
            break;
        }
    }

    //Insufficient
    if(r_i>=table.size())
    {
        Grow();
        table[r_i].type=type;
        table[r_i].free=false;
    }

    return r_i;
}

void GeneralRegister::Free(int r_i)
{
    table[r_i].free=true;
}

void GeneralRegister::Grow()
{
    int grow_n=table.size()/3;
    for(int i=0;i<grow_n;i++)
    {
        table.push_back(Register());
    }
}



void GeneralRegister::Print()
{
    cout<<"Register Count:"<<table.size()<<endl;
    
    for(int i=0;i<table.size();i++)
    {
        cout<<"R"<<i<<" Free:";

        if(table[i].free)cout<<"YES";
        else cout<<"NO Type:"<<table[i].type.Str();

        cout<<endl;
    }
    
    cout<<endl;
}

