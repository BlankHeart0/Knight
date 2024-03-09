#include "Register.h"

GeneralRegister general_register;

string GeneralRegister::Name(int register_i)
{
    string register_name="";

    if(register_i>=0&&register_i<table.size()
                    &&!table[register_i].free)
    {
        register_name+=(is_upper?"R":"r")+to_string(register_i);
        register_name+="(";
        switch(table[register_i].data_type)
        {
            case D_INT: register_name+=(is_upper?"INT":"int");  break;
            case D_DEC: register_name+=(is_upper?"DEC":"dec");  break;
            case D_STR: register_name+=(is_upper?"STR":"str");  break;
            case D_BOOL:register_name+=(is_upper?"BOOL":"bool");break;
        }
        register_name+=")";
    }
    else
        REGISTER_ERROR("Can not visit this general register");
    
    return register_name;
}

Register& GeneralRegister::GetReg(int register_i)
{
    return table[register_i];
}



int GeneralRegister::Alloc(DataType data_type)
{
    int register_i=0;
    
    for(;register_i<table.size();register_i++)
    {
        if(table[register_i].free)
        {
            table[register_i].data_type=data_type;
            table[register_i].free=false;
            break;
        }
    }

    //Insufficient
    if(register_i>=table.size())
    {
        Grow();
        table[register_i].data_type=data_type;
        table[register_i].free=false;
    }

    return register_i;
}

void GeneralRegister::Free(int register_i)
{
    if(table[register_i].free)
        REGISTER_ERROR("Can not free a free general regisgter");
    
    else table[register_i].free=true;
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
        if(table[i].free)
        {
            cout<<"YES";
            cout<<" DataType:"<<DataType_Text[table[i].data_type]<<endl;
        }
        else cout<<"NO "<<endl;
    }
    
    cout<<endl;
}

