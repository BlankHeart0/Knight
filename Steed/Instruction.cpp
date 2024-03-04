#include "Instruction.h"

// Load
void Load_ConstantToRegister::Excute()
{
    int R_i=operand1_register.register_i;

    switch(operand2_constant.constant_type)
    {
        case C_INT:
            general_register.Set(R_i,operand2_constant.INT_val);
            break;
        case C_DEC:
            general_register.Set(R_i,operand2_constant.DEC_val);
            break;
        case C_STR:
            general_register.Set(R_i,operand2_constant.STR_val);
            break;
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
    Register& R1=general_register.GetRegister(operand1_register.register_i);

    switch(R1.store_type)
    {
        case S_INT:R1.INT_val=-R1.INT_val;break;
        case S_DEC:R1.DEC_val=-R1.DEC_val;break;
    }
}