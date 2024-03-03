#include "Register.h"

string GeneralRegister::Name(int register_i)
{
    string register_name="";

    if(register_i>=0&&register_i<table.size()
                    &&!table[register_i].free)
    {
        register_name+="R"+to_string(register_i);
        register_name+="(";
        switch(table[register_i].store_type)
        {
            case S_NULL:register_name+="NULL";break;
            case S_INT:register_name+="INT";break;
            case S_DEC:register_name+="DEC";break;
            case S_STR:register_name+="STR";break;
        }
        register_name+=")";
    }
    else
        REGISTER_ERROR("Can not visit this general register");
    
    return register_name;
}

int GeneralRegister::Alloc(StoreType store_type)
{
    int register_i=0;
    
    for(;register_i<table.size();register_i++)
    {
        if(table[register_i].free)
        {
            table[register_i].store_type=store_type;
            table[register_i].free=false;
            break;
        }
    }

    //Insufficient
    if(register_i>=table.size())
    {
        Grow();
        table[register_i].store_type=store_type;
        table[register_i].free=false;
    }

    return register_i;
}

void GeneralRegister::Free(int register_i)
{
    if(table[register_i].free)
        REGISTER_ERROR("Can not free a free general regisgter");
    
    else 
    {
        table[register_i].free=true;
        table[register_i].store_type=S_NULL;
    }

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
        else cout<<"NO ";
        
        cout<<" StoreType:"<<StoreType_text[table[i].store_type]<<endl;
    }
    
    cout<<endl;
}

