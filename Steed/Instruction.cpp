#include "Instruction.h"
#include "VM.h"

// Variable
void Var::Excute()
{   
    VariableTable& variables=Steed.NowExcuteFunction().variables;

    string name=operand2_variable.name;
    int scope_i=operand2_variable.scope_i;

    switch(operand1_type.data_type)
    {
        case D_INT: variables.Set(scope_i,name,0);    break;
        case D_DEC: variables.Set(scope_i,name,0.0);  break;
        case D_STR: variables.Set(scope_i,name,"");   break;
        case D_BOOL:variables.Set(scope_i,name,false);break;
    }
}

void LoadConstant::Excute()
{
    int R_i=operand1_register.register_i;

    switch(operand2_constant.data_type)
    {
        case D_INT:
            general_register.Set(R_i,operand2_constant.INT_val);
            break;
        case D_DEC:
            general_register.Set(R_i,operand2_constant.DEC_val);
            break;
        case D_STR:
            general_register.Set(R_i,operand2_constant.STR_val);
            break;
        case D_BOOL:
            general_register.Set(R_i,operand2_constant.BOOL_val);
            break;
    }
}

void LoadVariable::Excute()
{
    int R_i=operand1_register.register_i;

    Variable& variable=Steed.main.vartable.
        GetVariable(operand2_variable.scope_i,operand2_variable.name);

    switch(variable.data_type)
    {
        case D_INT:
            general_register.Set(R_i,variable.INT_val);
            break;
        case D_DEC:
            general_register.Set(R_i,variable.DEC_val);
            break;
        case D_STR:
            general_register.Set(R_i,variable.STR_val);
            break;
    }
}

void Store::Excute()
{
    Register& R=general_register.GetRegister(operand2_register.register_i);
    Variable& variable=Steed.main.vartable.
        GetVariable(operand1_variable.scope_i,operand1_variable.name);

    switch(R.store_type)
    {
        case S_INT:variable.INT_val=R.INT_val;break;
        case S_DEC:variable.DEC_val=R.DEC_val;break;
        case S_STR:variable.STR_val=R.STR_val;break;
    }
} 



// Function    
void Print::Excute()
{
    Register& R=general_register.GetRegister(operand1_register.register_i);
    switch(R.store_type)
    {
        case S_INT:cout<<R.INT_val<<endl;break;
        case S_DEC:cout<<R.DEC_val<<endl;break;

        case S_STR:cout<<R.STR_val<<endl;break;
    }
}



// Binary
void Add::Excute()
{
    Register& R1=general_register.GetRegister(operand1_register.register_i);
    Register& R2=general_register.GetRegister(operand2_register.register_i);
    
    switch(R1.store_type)
    {
        case S_INT:R1.INT_val+=R2.INT_val;break;
        case S_DEC:R1.DEC_val+=R2.DEC_val;break;

        case S_STR:R1.STR_val+=R2.STR_val;break;
    }
}

void Sub::Excute()
{
    Register& R1=general_register.GetRegister(operand1_register.register_i);
    Register& R2=general_register.GetRegister(operand2_register.register_i);
    
    switch(R1.store_type)
    {
        case S_INT:R1.INT_val-=R2.INT_val;break;
        case S_DEC:R1.DEC_val-=R2.DEC_val;break;
    }
}

void Mul::Excute()
{
    Register& R1=general_register.GetRegister(operand1_register.register_i);
    Register& R2=general_register.GetRegister(operand2_register.register_i);
    
    switch(R1.store_type)
    {
        case S_INT:R1.INT_val*=R2.INT_val;break;
        case S_DEC:R1.DEC_val*=R2.DEC_val;break;
    }
}

void Div::Excute()
{
    Register& R1=general_register.GetRegister(operand1_register.register_i);
    Register& R2=general_register.GetRegister(operand2_register.register_i);
    
    switch(R1.store_type)
    {
        case S_INT:R1.INT_val/=R2.INT_val;break;
        case S_DEC:R1.DEC_val/=R2.DEC_val;break;
    }
}

void Mod::Excute()
{
    Register& R1=general_register.GetRegister(operand1_register.register_i);
    Register& R2=general_register.GetRegister(operand2_register.register_i);
    
    R1.INT_val%=R2.INT_val;
}



// Unary
void Neg::Excute()
{
    Register& R=general_register.GetRegister(operand1_register.register_i);

    switch(R.store_type)
    {
        case S_INT:R.INT_val=-R.INT_val;break;
        case S_DEC:R.DEC_val=-R.DEC_val;break;
    }
}