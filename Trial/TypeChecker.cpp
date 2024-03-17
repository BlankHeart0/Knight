#include "Type.h"
#include "Register.h"
#include "CodeGenerator.h"

DataType TokenToType(Token data_type_token)
{
    DataType data_type;

    switch(data_type_token.token_type)
    {
        case INT: data_type=D_INT; break;
        case DEC: data_type=D_DEC; break;
        case STR: data_type=D_STR; break;
        case BOOL:data_type=D_BOOL;break;
    }

    return data_type;
}



void TypeChecker::Check_Store(DataType data_type,int r_i,int line)
{
    Register& R=general_register.GetReg(r_i);

    switch(data_type)
    {
        case D_INT:
            switch(R.data_type)
            {
                // int=int -> int
                case D_INT:return;                                      break;
                // int=dec -> int=(int)dec -> int=int -> int
                case D_DEC:CodeGenerator::Convert(r_i,D_INT);    break;
                // int=str -> error
                case D_STR:TYPE_ERROR("int = str");                     break;
                // int=bool-> int=(int)bool-> int=int -> int
                case D_BOOL:CodeGenerator::Convert(r_i,D_INT);   break;
            }
            break;
        
        case D_DEC:
            switch(R.data_type)
            {
                // dec=int -> dec=(dec)int -> dec=dec -> dec
                case D_INT:CodeGenerator::Convert(r_i,D_DEC);    break;
                // dec=dec -> dec
                case D_DEC:return;                                      break;
                // dec=str -> error
                case D_STR:TYPE_ERROR("dec = str");                     break;
                // dec=bool-> error
                case D_BOOL:TYPE_ERROR("dec = bool");                   break;
            }
            break;
        
        case D_STR:
            switch(R.data_type)
            {
                // str=int -> error
                case D_INT:TYPE_ERROR("str = int");                     break;
                // str=dec -> error
                case D_DEC:TYPE_ERROR("str = dec");                     break;
                // str=str -> str
                case D_STR:return;                                      break;
                // str=bool-> error
                case D_BOOL:TYPE_ERROR("str = bool");                   break;
            }
            break;

        case D_BOOL:
            switch(R.data_type)
            {
                // bool=int-> bool=(bool)int -> bool=bool -> bool 
                case D_INT:CodeGenerator::Convert(r_i,D_BOOL);   break;
                // bool=dec-> bool=(bool)dec -> bool=bool -> bool 
                case D_DEC:CodeGenerator::Convert(r_i,D_BOOL);   break;
                // bool=str-> error
                case D_STR:TYPE_ERROR("bool = str");                    break;
                // bool=bool->bool
                case D_BOOL:return;                                     break;
            }
            break;
    }
}



// Logic
void TypeChecker::Check_Or(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.data_type)
    {   
        case D_INT:
            switch(R2.data_type)
            {
                // int or int -> (bool)int or (bool)int -> bool or bool -> bool
                // int or dec -> (bool)int or (bool)dec -> bool or bool -> bool
                case D_INT: 
                case D_DEC:
                    CodeGenerator::Convert(r1_i,D_BOOL);
                    CodeGenerator::Convert(r2_i,D_BOOL);
                    break;
                // int or str -> error
                case D_STR:TYPE_ERROR("int or str");                break;
                // int or bool-> (bool)int or bool -> bool or bool -> bool
                case D_BOOL:CodeGenerator::Convert(r1_i,D_BOOL);    break;
            }
            break;

        case D_DEC:
            switch(R2.data_type)
            {
                // dec or int -> (bool)dec or (bool)int -> bool or bool -> bool
                // dec or dec -> (bool)dec or (bool)dec -> bool or bool -> bool
                case D_INT: 
                case D_DEC:
                    CodeGenerator::Convert(r1_i,D_BOOL);
                    CodeGenerator::Convert(r2_i,D_BOOL);
                    break;
                // dec or str -> error
                case D_STR:TYPE_ERROR("dec or str");                break;
                // dec or bool-> (bool)dec or bool -> bool or bool -> bool
                case D_BOOL:CodeGenerator::Convert(r1_i,D_BOOL);    break;
            }
            break;
        
        case D_STR:
            switch(R2.data_type)
            {
                // str or int -> error
                case D_INT:TYPE_ERROR("str or int");                break;
                // str or dec -> error
                case D_DEC:TYPE_ERROR("str or dec");                break;
                // str or str -> error
                case D_STR:TYPE_ERROR("str or str");                break;
                // str or bool-> error
                case D_BOOL:TYPE_ERROR("str or bool");              break;
            }
            break;
        
        case D_BOOL:
            switch(R2.data_type)
            {
                // bool or int -> bool or (bool)int -> bool or bool -> bool
                case D_INT:CodeGenerator::Convert(r2_i,D_BOOL);     break;
                // bool or dec -> bool or (bool)dec -> bool or bool -> bool
                case D_DEC:CodeGenerator::Convert(r2_i,D_BOOL);     break;
                // bool or str-> error
                case D_STR:TYPE_ERROR("bool or str");               break;
                // bool or bool-> bool
                case D_BOOL:return;                                 break;
            }
            break;
    }
}

void TypeChecker::Check_And(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.data_type)
    {   
        case D_INT:
            switch(R2.data_type)
            {
                // int and int -> (bool)int and (bool)int -> bool and bool -> bool
                // int and dec -> (bool)int and (bool)dec -> bool and bool -> bool
                case D_INT: 
                case D_DEC:
                    CodeGenerator::Convert(r1_i,D_BOOL);
                    CodeGenerator::Convert(r2_i,D_BOOL);
                    break;
                // int and str -> error
                case D_STR:TYPE_ERROR("int and str");               break;
                // int and bool-> (bool)int and bool -> bool and bool -> bool
                case D_BOOL:CodeGenerator::Convert(r1_i,D_BOOL);    break;
            }
            break;

        case D_DEC:
            switch(R2.data_type)
            {
                // dec and int -> (bool)dec and (bool)int -> bool and bool -> bool
                // dec and dec -> (bool)dec and (bool)dec -> bool and bool -> bool
                case D_INT: 
                case D_DEC:
                    CodeGenerator::Convert(r1_i,D_BOOL);
                    CodeGenerator::Convert(r2_i,D_BOOL);
                    break;
                // dec and str -> error
                case D_STR:TYPE_ERROR("dec and str");               break;
                // dec and bool-> (bool)dec and bool -> bool and bool -> bool
                case D_BOOL:CodeGenerator::Convert(r1_i,D_BOOL);    break;
            }
            break;
        
        case D_STR:
            switch(R2.data_type)
            {
                // str and int -> error
                case D_INT:TYPE_ERROR("str and int");               break;
                // str and dec -> error
                case D_DEC:TYPE_ERROR("str and dec");               break;
                // str and str -> error
                case D_STR:TYPE_ERROR("str and str");               break;
                // str and bool-> error
                case D_BOOL:TYPE_ERROR("str and bool");             break;
            }
            break;
        
        case D_BOOL:
            switch(R2.data_type)
            {
                // bool and int -> bool and (bool)int -> bool and bool -> bool
                case D_INT:CodeGenerator::Convert(r2_i,D_BOOL);     break;
                // bool and dec -> bool and (bool)dec -> bool and bool -> bool
                case D_DEC:CodeGenerator::Convert(r2_i,D_BOOL);     break;
                // bool and str-> error
                case D_STR:TYPE_ERROR("bool and str");              break;
                // bool and bool-> bool
                case D_BOOL:return;                                 break;
            }
            break;
    }
}

void TypeChecker::Check_Not(int r_i,int line)
{
    Register& R=general_register.GetReg(r_i);
    
    switch(R.data_type)
    {
        // not int -> not (bool)int -> not bool -> bool
        case D_INT:CodeGenerator::Convert(r_i,D_BOOL);       break;
        // not dec -> not (bool)dec -> not bool -> bool
        case D_DEC:CodeGenerator::Convert(r_i,D_BOOL);       break;
        // not str -> error
        case D_STR:TYPE_ERROR("not str");                           break;
        // not bool-> bool
        case D_BOOL:return;                                         break;
    }
}

void TypeChecker::Check_Equal(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.data_type)
    {
        case D_INT:
            switch(R2.data_type)
            {
                // int ?= int -> bool
                case D_INT:return;                                  break;
                // int ?= dec -> (dec)int ?= dec -> dec ?= dec -> bool
                case D_DEC:CodeGenerator::Convert(r1_i,D_DEC);      break;
                // int ?= str -> error
                case D_STR:TYPE_ERROR("int ?= str");                break;
                // int ?= bool-> (bool)int ?= bool -> bool ?= bool -> bool
                case D_BOOL:CodeGenerator::Convert(r1_i,D_BOOL);    break;
            }
            break;

        case D_DEC:
            switch(R2.data_type)
            {
                // dec ?= int -> dec ?= (dec)int -> dec ?= dec -> bool
                case D_INT:CodeGenerator::Convert(r2_i,D_DEC);      break;
                // dec ?= dec -> bool
                case D_DEC:return;                                  break;
                // dec ?= str -> error
                case D_STR:TYPE_ERROR("dec ?= str");                break;
                // dec ?= bool-> (bool)dec ?= bool -> bool ?= bool -> bool
                case D_BOOL:CodeGenerator::Convert(r1_i,D_BOOL);    break;
            }
            break;

        case D_STR:
            switch(R2.data_type)
            {
                // str ?= int -> error
                case D_INT:TYPE_ERROR("str ?= int");                break;
                // str ?= dec -> error
                case D_DEC:TYPE_ERROR("str ?= dec");                break;
                // str ?= str -> bool
                case D_STR:return;                                  break;
                // str ?= bool-> error
                case D_BOOL:TYPE_ERROR("str ?= bool");              break;
            }
            break;

        case D_BOOL:
            switch(R2.data_type)
            {
                // bool ?= int -> bool ?= (bool)int -> bool ?= bool -> bool
                case D_INT:CodeGenerator::Convert(r2_i,D_BOOL);     break;
                // bool ?= dec -> bool ?= (bool)dec -> bool ?= bool -> bool
                case D_DEC:CodeGenerator::Convert(r2_i,D_BOOL);     break;
                // bool ?= str -> error
                case D_STR:TYPE_ERROR("bool ?= str");               break;
                // bool ?= bool-> bool
                case D_BOOL:return;                                 break;
            }
            break;
    }
}

void TypeChecker::Check_NotEqual(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.data_type)
    {
        case D_INT:
            switch(R2.data_type)
            {
                // int != int -> bool
                case D_INT:return;                                  break;
                // int != dec -> (dec)int != dec -> dec != dec -> bool
                case D_DEC:CodeGenerator::Convert(r1_i,D_DEC);      break;
                // int != str -> error
                case D_STR:TYPE_ERROR("int != str");                break;
                // int != bool-> (bool)int != bool -> bool != bool -> bool
                case D_BOOL:CodeGenerator::Convert(r1_i,D_BOOL);    break;
            }
            break;

        case D_DEC:
            switch(R2.data_type)
            {
                // dec != int -> dec != (dec)int -> dec != dec -> bool
                case D_INT:CodeGenerator::Convert(r2_i,D_DEC);      break;
                // dec != dec -> bool
                case D_DEC:return;                                  break;
                // dec != str -> error
                case D_STR:TYPE_ERROR("dec != str");                break;
                // dec != bool-> (bool)dec != bool -> bool != bool -> bool
                case D_BOOL:CodeGenerator::Convert(r1_i,D_BOOL);    break;
            }
            break;

        case D_STR:
            switch(R2.data_type)
            {
                // str != int -> error
                case D_INT:TYPE_ERROR("str != int");                break;
                // str != dec -> error
                case D_DEC:TYPE_ERROR("str != dec");                break;
                // str != str -> bool
                case D_STR:return;                                  break;
                // str != bool-> error
                case D_BOOL:TYPE_ERROR("str != bool");              break;
            }
            break;

        case D_BOOL:
            switch(R2.data_type)
            {
                // bool != int -> bool != (bool)int -> bool != bool -> bool
                case D_INT:CodeGenerator::Convert(r2_i,D_BOOL);     break;
                // bool != dec -> bool != (bool)dec -> bool != bool -> bool
                case D_DEC:CodeGenerator::Convert(r2_i,D_BOOL);     break;
                // bool != str -> error
                case D_STR:TYPE_ERROR("bool != str");               break;
                // bool != bool-> bool
                case D_BOOL:return;                                 break;
            }
            break;
    }
}

void TypeChecker::Check_Less(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.data_type)
    {
        case D_INT:
            switch(R2.data_type)
            {
                // int < int -> bool
                case D_INT:return;                                  break;   
                // int < dec -> (dec)int < dec -> dec < dec -> bool
                case D_DEC:CodeGenerator::Convert(r1_i,D_DEC);      break;
                // int < str -> error
                case D_STR:TYPE_ERROR("int < str");                 break;            
                // int < bool-> error
                case D_BOOL:TYPE_ERROR("int < bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.data_type)
            {
                // dec < int -> dec < (dec)int -> dec < dec -> bool
                case D_INT:CodeGenerator::Convert(r2_i,D_DEC);      break;
                // dec < dec -> bool
                case D_DEC:return;                                  break;
                // dec < str -> error
                case D_STR:TYPE_ERROR("dec < str");                 break;
                // dec < bool-> error
                case D_BOOL:TYPE_ERROR("dec < bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.data_type)
            {
                // str < int -> error
                case D_INT:TYPE_ERROR("str < int");                 break;
                // str < dec -> error
                case D_DEC:TYPE_ERROR("str < dec");                 break;
                // str < str -> error
                case D_STR:TYPE_ERROR("str < str");                 break;
                // str < bool-> error
                case D_BOOL:TYPE_ERROR("str < bool");               break;
            }
            break;
        
        case D_BOOL:
            switch(R2.data_type)
            {
                // bool < int -> error
                case D_INT:TYPE_ERROR("bool < int");                break;
                // bool < dec -> error
                case D_DEC:TYPE_ERROR("bool < dec");                break;
                // bool < str -> error
                case D_STR:TYPE_ERROR("bool < str");                break;
                // bool < bool-> error
                case D_BOOL:TYPE_ERROR("bool < bool");              break;
            }
            break;
    }
}

void TypeChecker::Check_LessEqual(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.data_type)
    {
        case D_INT:
            switch(R2.data_type)
            {
                // int <= int -> bool
                case D_INT:return;                                  break;   
                // int <= dec -> (dec)int <= dec -> dec <= dec -> bool
                case D_DEC:CodeGenerator::Convert(r1_i,D_DEC);      break;
                // int <= str -> error
                case D_STR:TYPE_ERROR("int <= str");                break;            
                // int <= bool-> error
                case D_BOOL:TYPE_ERROR("int <= bool");              break;
            }
            break;
        
        case D_DEC:
            switch(R2.data_type)
            {
                // dec <= int -> dec <= (dec)int -> dec <= dec -> bool
                case D_INT:CodeGenerator::Convert(r2_i,D_DEC);      break;
                // dec <= dec -> bool
                case D_DEC:return;                                  break;
                // dec <= str -> error
                case D_STR:TYPE_ERROR("dec <= str");                break;
                // dec <= bool-> error
                case D_BOOL:TYPE_ERROR("dec <= bool");              break;
            }
            break;
        
        case D_STR:
            switch(R2.data_type)
            {
                // str <= int -> error
                case D_INT:TYPE_ERROR("str <= int");                break;
                // str <= dec -> error
                case D_DEC:TYPE_ERROR("str <= dec");                break;
                // str <= str -> error
                case D_STR:TYPE_ERROR("str <= str");                break;
                // str <= bool-> error
                case D_BOOL:TYPE_ERROR("str <= bool");              break;
            }
            break;
        
        case D_BOOL:
            switch(R2.data_type)
            {
                // bool <= int -> error
                case D_INT:TYPE_ERROR("bool <= int");               break;
                // bool <= dec -> error
                case D_DEC:TYPE_ERROR("bool <= dec");               break;
                // bool <= str -> error
                case D_STR:TYPE_ERROR("bool <= str");               break;
                // bool <= bool-> error
                case D_BOOL:TYPE_ERROR("bool <= bool");             break;
            }
            break;
    }
}

void TypeChecker::Check_Greater(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.data_type)
    {
        case D_INT:
            switch(R2.data_type)
            {
                // int > int -> bool
                case D_INT:return;                                  break;   
                // int > dec -> (dec)int > dec -> dec > dec -> bool
                case D_DEC:CodeGenerator::Convert(r1_i,D_DEC);      break;
                // int > str -> error
                case D_STR:TYPE_ERROR("int > str");                 break;            
                // int > bool-> error
                case D_BOOL:TYPE_ERROR("int > bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.data_type)
            {
                // dec > int -> dec > (dec)int -> dec > dec -> bool
                case D_INT:CodeGenerator::Convert(r2_i,D_DEC);      break;
                // dec > dec -> bool
                case D_DEC:return;                                  break;
                // dec > str -> error
                case D_STR:TYPE_ERROR("dec > str");                 break;
                // dec > bool-> error
                case D_BOOL:TYPE_ERROR("dec > bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.data_type)
            {
                // str > int -> error
                case D_INT:TYPE_ERROR("str > int");                 break;
                // str > dec -> error
                case D_DEC:TYPE_ERROR("str > dec");                 break;
                // str > str -> error
                case D_STR:TYPE_ERROR("str > str");                 break;
                // str > bool-> error
                case D_BOOL:TYPE_ERROR("str > bool");               break;
            }
            break;
        
        case D_BOOL:
            switch(R2.data_type)
            {
                // bool > int -> error
                case D_INT:TYPE_ERROR("bool > int");                break;
                // bool > dec -> error
                case D_DEC:TYPE_ERROR("bool > dec");                break;
                // bool > str -> error
                case D_STR:TYPE_ERROR("bool > str");                break;
                // bool > bool-> error
                case D_BOOL:TYPE_ERROR("bool > bool");              break;
            }
            break;
    }
}

void TypeChecker::Check_GreaterEqual(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.data_type)
    {
        case D_INT:
            switch(R2.data_type)
            {
                // int >= int -> bool
                case D_INT:return;                                  break;   
                // int >= dec -> (dec)int >= dec -> dec >= dec -> bool
                case D_DEC:CodeGenerator::Convert(r1_i,D_DEC);      break;
                // int >= str -> error
                case D_STR:TYPE_ERROR("int >= str");                break;            
                // int >= bool-> error
                case D_BOOL:TYPE_ERROR("int >= bool");              break;
            }
            break;
        
        case D_DEC:
            switch(R2.data_type)
            {
                // dec >= int -> dec >= (dec)int -> dec >= dec -> bool
                case D_INT:CodeGenerator::Convert(r2_i,D_DEC);      break;
                // dec >= dec -> bool
                case D_DEC:return;                                  break;
                // dec >= str -> error
                case D_STR:TYPE_ERROR("dec >= str");                break;
                // dec >= bool-> error
                case D_BOOL:TYPE_ERROR("dec >= bool");              break;
            }
            break;
        
        case D_STR:
            switch(R2.data_type)
            {
                // str >= int -> error
                case D_INT:TYPE_ERROR("str >= int");                break;
                // str >= dec -> error
                case D_DEC:TYPE_ERROR("str >= dec");                break;
                // str >= str -> error
                case D_STR:TYPE_ERROR("str >= str");                break;
                // str >= bool-> error
                case D_BOOL:TYPE_ERROR("str >= bool");              break;
            }
            break;
        
        case D_BOOL:
            switch(R2.data_type)
            {
                // bool >= int -> error
                case D_INT:TYPE_ERROR("bool >= int");               break;
                // bool >= dec -> error
                case D_DEC:TYPE_ERROR("bool >= dec");               break;
                // bool >= str -> error
                case D_STR:TYPE_ERROR("bool >= str");               break;
                // bool >= bool-> error
                case D_BOOL:TYPE_ERROR("bool >= bool");             break;
            }
            break;
    }
}



// Arithmetic
void TypeChecker::Check_Add(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);
    
    switch(R1.data_type)
    {
        case D_INT:
            switch(R2.data_type)
            {
                // int + int -> int
                case D_INT:return;                                  break;
                // int + dec -> (dec)int + dec -> dec + dec -> dec
                case D_DEC:CodeGenerator::Convert(r1_i,D_DEC);      break;
                // int + str -> error
                case D_STR:TYPE_ERROR("int + str");                 break;
                // int + bool-> error
                case D_BOOL:TYPE_ERROR("int + bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.data_type)
            {
                // dec + int -> dec + (dec)int -> dec + dec -> dec 
                case D_INT:CodeGenerator::Convert(r2_i,D_DEC);      break;
                // dec + dec -> dec
                case D_DEC:return;                                  break;
                // dec + str -> error
                case D_STR:TYPE_ERROR("dec + str");                 break;
                // dec + bool-> error
                case D_BOOL:TYPE_ERROR("dec + bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.data_type)
            {
                // str + int -> error
                case D_INT:TYPE_ERROR("str + int");                 break;
                // str + dec -> error
                case D_DEC:TYPE_ERROR("str + dec");                 break;
                // str + str -> str
                case D_STR:return;                                  break;
                // str + bool-> error
                case D_BOOL:TYPE_ERROR("str + bool");               break;
            }
            break;
        
        case D_BOOL:
            switch(R2.data_type)
            {
                // bool + int-> error
                case D_INT:TYPE_ERROR("bool + int");                break;
                // bool + dec-> error
                case D_DEC:TYPE_ERROR("bool + dec");                break;
                // bool + str-> error
                case D_STR:TYPE_ERROR("bool + str");                break;
                // bool + bool->error
                case D_BOOL:TYPE_ERROR("bool + bool");              break;
            }
            break;
    }
}

void TypeChecker::Check_Sub(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);
    
    switch(R1.data_type)
    {   
        case D_INT:
            switch(R2.data_type)
            {
                // int - int -> int
                case D_INT:return;                                  break;
                // int - dec -> (dec)int - dec -> dec - dec -> dec
                case D_DEC:CodeGenerator::Convert(r1_i,D_DEC);      break;
                // int - str -> error
                case D_STR:TYPE_ERROR("int - str");                 break;
                // int - bool-> error
                case D_BOOL:TYPE_ERROR("int - bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.data_type)
            {
                // dec - int -> dec - (dec)int -> dec - dec -> dec 
                case D_INT:CodeGenerator::Convert(r2_i,D_DEC);      break;
                // dec - dec -> dec
                case D_DEC:return;                                  break;
                // dec - str -> error
                case D_STR:TYPE_ERROR("dec - str");                 break;
                // dec - bool-> error
                case D_BOOL:TYPE_ERROR("dec - bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.data_type)
            {
                // str - int -> error
                case D_INT:TYPE_ERROR("str - int");                 break;
                // str - dec -> error
                case D_DEC:TYPE_ERROR("str - dec");                 break;
                // str - str -> error
                case D_STR:TYPE_ERROR("str - str");                 break;
                // str - bool-> error
                case D_BOOL:TYPE_ERROR("str - bool");               break;
            }
            break;
        
        case D_BOOL:
            switch(R2.data_type)
            {
                // bool - int-> error
                case D_INT:TYPE_ERROR("bool - int");                break;
                // bool - dec-> error
                case D_DEC:TYPE_ERROR("bool - dec");                break;
                // bool - str-> error
                case D_STR:TYPE_ERROR("bool - str");                break;
                // bool - bool->error
                case D_BOOL:TYPE_ERROR("bool - bool");              break;
            }
            break;
    }
}

void TypeChecker::Check_Mul(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);
    
    switch(R1.data_type)
    {   
        case D_INT:
            switch(R2.data_type)
            {
                // int * int -> int
                case D_INT:return;                                  break;
                // int * dec -> (dec)int * dec -> dec * dec -> dec
                case D_DEC:CodeGenerator::Convert(r1_i,D_DEC);      break;
                // int * str -> error
                case D_STR:TYPE_ERROR("int * str");                 break;
                // int * bool-> error
                case D_BOOL:TYPE_ERROR("int * bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.data_type)
            {
                // dec * int -> dec * (dec)int -> dec * dec -> dec 
                case D_INT:CodeGenerator::Convert(r2_i,D_DEC);      break;
                // dec * dec -> dec
                case D_DEC:return;                                  break;
                // dec * str -> error
                case D_STR:TYPE_ERROR("dec * str");                 break;
                // dec * bool-> error
                case D_BOOL:TYPE_ERROR("dec * bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.data_type)
            {
                // str * int -> error
                case D_INT:TYPE_ERROR("str * int");                 break;
                // str * dec -> error
                case D_DEC:TYPE_ERROR("str * dec");                 break;
                // str * str -> error
                case D_STR:TYPE_ERROR("str * str");                 break;
                // str * bool-> error
                case D_BOOL:TYPE_ERROR("str * bool");               break;
            }
            break;
        
        case D_BOOL:
            switch(R2.data_type)
            {
                // bool * int-> error
                case D_INT:TYPE_ERROR("bool * int");                break;
                // bool * dec-> error
                case D_DEC:TYPE_ERROR("bool * dec");                break;
                // bool * str-> error
                case D_STR:TYPE_ERROR("bool * str");                break;
                // bool * bool->error
                case D_BOOL:TYPE_ERROR("bool * bool");              break;
            }
            break;
    }
}

void TypeChecker::Check_Div(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);
    
    switch(R1.data_type)
    {   
        case D_INT:
            switch(R2.data_type)
            {
                // int / int -> int
                case D_INT:return;                                  break;
                // int / dec -> (dec)int / dec -> dec / dec -> dec
                case D_DEC:CodeGenerator::Convert(r1_i,D_DEC);      break;
                // int / str -> error
                case D_STR:TYPE_ERROR("int / str");                 break;
                // int / bool-> error
                case D_BOOL:TYPE_ERROR("int / bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.data_type)
            {
                // dec / int -> dec / (dec)int -> dec / dec -> dec 
                case D_INT:CodeGenerator::Convert(r2_i,D_DEC);      break;
                // dec / dec -> dec
                case D_DEC:return;                                  break;
                // dec / str -> error
                case D_STR:TYPE_ERROR("dec / str");                 break;
                // dec / bool-> error
                case D_BOOL:TYPE_ERROR("dec / bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.data_type)
            {
                // str / int -> error
                case D_INT:TYPE_ERROR("str / int");                 break;
                // str / dec -> error
                case D_DEC:TYPE_ERROR("str / dec");                 break;
                // str / str -> error
                case D_STR:TYPE_ERROR("str / str");                 break;
                // str / bool-> error
                case D_BOOL:TYPE_ERROR("str / bool");               break;
            }
            break;
        
        case D_BOOL:
            switch(R2.data_type)
            {
                // bool / int-> error
                case D_INT:TYPE_ERROR("bool / int");                break;
                // bool / dec-> error
                case D_DEC:TYPE_ERROR("bool / dec");                break;
                // bool / str-> error
                case D_STR:TYPE_ERROR("bool / str");                break;
                // bool / bool->error
                case D_BOOL:TYPE_ERROR("bool / bool");              break;
            }
            break;
    }
}

void TypeChecker::Check_Mod(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);
    
    switch(R1.data_type)
    {   
        case D_INT:
            switch(R2.data_type)
            {
                // int % int -> int
                case D_INT:return;                                  break;
                // int % dec -> error
                case D_DEC:TYPE_ERROR("int % dec");                 break;
                // int % str -> error
                case D_STR:TYPE_ERROR("int % str");                 break;
                // int % bool-> error
                case D_BOOL:TYPE_ERROR("int % bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.data_type)
            {
                // dec % int -> error
                case D_INT:TYPE_ERROR("dec % int");                 break;
                // dec % dec -> error
                case D_DEC:TYPE_ERROR("dec % dec");                 break;
                // dec % str -> error
                case D_STR:TYPE_ERROR("dec % str");                 break;
                // dec % bool-> error
                case D_BOOL:TYPE_ERROR("dec % bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.data_type)
            {
                // str % int -> error
                case D_INT:TYPE_ERROR("str % int");                 break;
                // str % dec -> error
                case D_DEC:TYPE_ERROR("str % dec");                 break;
                // str % str -> error
                case D_STR:TYPE_ERROR("str % str");                 break;
                // str % bool-> error
                case D_BOOL:TYPE_ERROR("str % bool");               break;
            }
            break;
        
        case D_BOOL:
            switch(R2.data_type)
            {
                // bool % int-> error
                case D_INT:TYPE_ERROR("bool % int");                break;
                // bool % dec-> error
                case D_DEC:TYPE_ERROR("bool % dec");                break;
                // bool % str-> error
                case D_STR:TYPE_ERROR("bool % str");                break;
                // bool % bool->error
                case D_BOOL:TYPE_ERROR("bool % bool");              break;
            }
            break;
    }
}

void TypeChecker::Check_Neg(int r_i,int line)
{
    Register& R=general_register.GetReg(r_i);
    
    switch(R.data_type)
    {   
        // - int -> int
        case D_INT:return;                                          break;
        // - dec -> dec
        case D_DEC:return;                                          break;
        // - str -> error
        case D_STR:TYPE_ERROR(" - str");                            break;
        // - bool-> error
        case D_BOOL:TYPE_ERROR(" - bool");                          break;
    }   
}
