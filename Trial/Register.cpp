#include "Register.h"

GeneralRegister general_register;

string GeneralRegister::Name(int r_i)
{
    string register_name="";

    if(r_i>=0&&r_i<table.size())
    {
        register_name+=(is_upper?"R":"r")+to_string(r_i);
        register_name+="(";
        switch(table[r_i].data_type)
        {
            case D_INT: register_name+=(is_upper?"INT":"int");  break;
            case D_DEC: register_name+=(is_upper?"DEC":"dec");  break;
            case D_STR: register_name+=(is_upper?"STR":"str");  break;
            case D_BOOL:register_name+=(is_upper?"BOOL":"bool");break;
        }
        register_name+=")";
    }
    else REGISTER_ERROR("You visit a void value");
    
    return register_name;
}

Register& GeneralRegister::GetReg(int r_i)
{
    return table[r_i];
}



int GeneralRegister::Alloc(DataType data_type)
{
    int r_i=0;
    
    for(;r_i<table.size();r_i++)
    {
        if(table[r_i].free)
        {
            table[r_i].data_type=data_type;
            table[r_i].free=false;
            break;
        }
    }

    //Insufficient
    if(r_i>=table.size())
    {
        Grow();
        table[r_i].data_type=data_type;
        table[r_i].free=false;
    }

    return r_i;
}

void GeneralRegister::Free(int r_i)
{
    if(r_i>=0&&r_i<table.size()&&!table[r_i].free)
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
        if(table[i].free)
        {
            cout<<"YES";
            cout<<" DataType:"<<DataType_Text[table[i].data_type]<<endl;
        }
        else cout<<"NO "<<endl;
    }
    
    cout<<endl;
}

