#include "DataTypeChecker.h"

// Assignment
void DataTypeChecker::Check_Store(DataType data,int r_i,int line)
{
    Register& R=general_register.GetReg(r_i);

    switch(data)
    {
        case D_INT:
            switch(R.type.data)
            {
                // int=int -> int
                case D_INT:return;                                      break;
                // int=dec -> int=(int)dec -> int=int -> int
                case D_DEC:CodeGenerator::Convert(D_INT,r_i);           break;
                // int=str -> error
                case D_STR:TYPE_ERROR("int = str");                     break;
                // int=bool-> int=(int)bool-> int=int -> int
                case D_BOOL:CodeGenerator::Convert(D_INT,r_i);          break;
            }
            break;
        
        case D_DEC:
            switch(R.type.data)
            {
                // dec=int -> dec=(dec)int -> dec=dec -> dec
                case D_INT:CodeGenerator::Convert(D_DEC,r_i);           break;
                // dec=dec -> dec
                case D_DEC:return;                                      break;
                // dec=str -> error
                case D_STR:TYPE_ERROR("dec = str");                     break;
                // dec=bool-> error
                case D_BOOL:TYPE_ERROR("dec = bool");                   break;
            }
            break;
        
        case D_STR:
            switch(R.type.data)
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
            switch(R.type.data)
            {
                // bool=int-> bool=(bool)int -> bool=bool -> bool 
                case D_INT:CodeGenerator::Convert(D_BOOL,r_i);          break;
                // bool=dec-> bool=(bool)dec -> bool=bool -> bool 
                case D_DEC:CodeGenerator::Convert(D_BOOL,r_i);          break;
                // bool=str-> error
                case D_STR:TYPE_ERROR("bool = str");                    break;
                // bool=bool->bool
                case D_BOOL:return;                                     break;
            }
            break;
    }
}



// Logic
void DataTypeChecker::Check_Or(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.type.data)
    {   
        case D_INT:
            switch(R2.type.data)
            {
                // int or int -> (bool)int or (bool)int -> bool or bool -> bool
                // int or dec -> (bool)int or (bool)dec -> bool or bool -> bool
                case D_INT: 
                case D_DEC:
                    CodeGenerator::Convert(D_BOOL,r1_i);
                    CodeGenerator::Convert(D_BOOL,r2_i);
                    break;
                // int or str -> error
                case D_STR:TYPE_ERROR("int or str");                break;
                // int or bool-> (bool)int or bool -> bool or bool -> bool
                case D_BOOL:CodeGenerator::Convert(D_BOOL,r1_i);    break;
            }
            break;

        case D_DEC:
            switch(R2.type.data)
            {
                // dec or int -> (bool)dec or (bool)int -> bool or bool -> bool
                // dec or dec -> (bool)dec or (bool)dec -> bool or bool -> bool
                case D_INT: 
                case D_DEC:
                    CodeGenerator::Convert(D_BOOL,r1_i);
                    CodeGenerator::Convert(D_BOOL,r2_i);
                    break;
                // dec or str -> error
                case D_STR:TYPE_ERROR("dec or str");                break;
                // dec or bool-> (bool)dec or bool -> bool or bool -> bool
                case D_BOOL:CodeGenerator::Convert(D_BOOL,r1_i);    break;
            }
            break;
        
        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
            {
                // bool or int -> bool or (bool)int -> bool or bool -> bool
                case D_INT:CodeGenerator::Convert(D_BOOL,r2_i);     break;
                // bool or dec -> bool or (bool)dec -> bool or bool -> bool
                case D_DEC:CodeGenerator::Convert(D_BOOL,r2_i);     break;
                // bool or str-> error
                case D_STR:TYPE_ERROR("bool or str");               break;
                // bool or bool-> bool
                case D_BOOL:return;                                 break;
            }
            break;
    }
}

void DataTypeChecker::Check_And(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.type.data)
    {   
        case D_INT:
            switch(R2.type.data)
            {
                // int and int -> (bool)int and (bool)int -> bool and bool -> bool
                // int and dec -> (bool)int and (bool)dec -> bool and bool -> bool
                case D_INT: 
                case D_DEC:
                    CodeGenerator::Convert(D_BOOL,r1_i);
                    CodeGenerator::Convert(D_BOOL,r2_i);
                    break;
                // int and str -> error
                case D_STR:TYPE_ERROR("int and str");               break;
                // int and bool-> (bool)int and bool -> bool and bool -> bool
                case D_BOOL:CodeGenerator::Convert(D_BOOL,r1_i);    break;
            }
            break;

        case D_DEC:
            switch(R2.type.data)
            {
                // dec and int -> (bool)dec and (bool)int -> bool and bool -> bool
                // dec and dec -> (bool)dec and (bool)dec -> bool and bool -> bool
                case D_INT: 
                case D_DEC:
                    CodeGenerator::Convert(D_BOOL,r1_i);
                    CodeGenerator::Convert(D_BOOL,r2_i);
                    break;
                // dec and str -> error
                case D_STR:TYPE_ERROR("dec and str");               break;
                // dec and bool-> (bool)dec and bool -> bool and bool -> bool
                case D_BOOL:CodeGenerator::Convert(D_BOOL,r1_i);    break;
            }
            break;
        
        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
            {
                // bool and int -> bool and (bool)int -> bool and bool -> bool
                case D_INT:CodeGenerator::Convert(D_BOOL,r2_i);     break;
                // bool and dec -> bool and (bool)dec -> bool and bool -> bool
                case D_DEC:CodeGenerator::Convert(D_BOOL,r2_i);     break;
                // bool and str-> error
                case D_STR:TYPE_ERROR("bool and str");              break;
                // bool and bool-> bool
                case D_BOOL:return;                                 break;
            }
            break;
    }
}

void DataTypeChecker::Check_Not(int r_i,int line)
{
    Register& R=general_register.GetReg(r_i);
    
    switch(R.type.data)
    {
        // not int -> not (bool)int -> not bool -> bool
        case D_INT:CodeGenerator::Convert(D_BOOL,r_i);              break;
        // not dec -> not (bool)dec -> not bool -> bool
        case D_DEC:CodeGenerator::Convert(D_BOOL,r_i);              break;
        // not str -> error
        case D_STR:TYPE_ERROR("not str");                           break;
        // not bool-> bool
        case D_BOOL:return;                                         break;
    }
}

void DataTypeChecker::Check_Equal(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.type.data)
    {
        case D_INT:
            switch(R2.type.data)
            {
                // int ?= int -> bool
                case D_INT:return;                                  break;
                // int ?= dec -> (dec)int ?= dec -> dec ?= dec -> bool
                case D_DEC:CodeGenerator::Convert(D_DEC,r1_i);      break;
                // int ?= str -> error
                case D_STR:TYPE_ERROR("int ?= str");                break;
                // int ?= bool-> (bool)int ?= bool -> bool ?= bool -> bool
                case D_BOOL:CodeGenerator::Convert(D_BOOL,r1_i);    break;
            }
            break;

        case D_DEC:
            switch(R2.type.data)
            {
                // dec ?= int -> dec ?= (dec)int -> dec ?= dec -> bool
                case D_INT:CodeGenerator::Convert(D_DEC,r2_i);      break;
                // dec ?= dec -> bool
                case D_DEC:return;                                  break;
                // dec ?= str -> error
                case D_STR:TYPE_ERROR("dec ?= str");                break;
                // dec ?= bool-> (bool)dec ?= bool -> bool ?= bool -> bool
                case D_BOOL:CodeGenerator::Convert(D_BOOL,r1_i);    break;
            }
            break;

        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
            {
                // bool ?= int -> bool ?= (bool)int -> bool ?= bool -> bool
                case D_INT:CodeGenerator::Convert(D_BOOL,r2_i);     break;
                // bool ?= dec -> bool ?= (bool)dec -> bool ?= bool -> bool
                case D_DEC:CodeGenerator::Convert(D_BOOL,r2_i);     break;
                // bool ?= str -> error
                case D_STR:TYPE_ERROR("bool ?= str");               break;
                // bool ?= bool-> bool
                case D_BOOL:return;                                 break;
            }
            break;
    }
}

void DataTypeChecker::Check_NotEqual(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.type.data)
    {
        case D_INT:
            switch(R2.type.data)
            {
                // int != int -> bool
                case D_INT:return;                                  break;
                // int != dec -> (dec)int != dec -> dec != dec -> bool
                case D_DEC:CodeGenerator::Convert(D_DEC,r1_i);      break;
                // int != str -> error
                case D_STR:TYPE_ERROR("int != str");                break;
                // int != bool-> (bool)int != bool -> bool != bool -> bool
                case D_BOOL:CodeGenerator::Convert(D_BOOL,r1_i);    break;
            }
            break;

        case D_DEC:
            switch(R2.type.data)
            {
                // dec != int -> dec != (dec)int -> dec != dec -> bool
                case D_INT:CodeGenerator::Convert(D_DEC,r2_i);      break;
                // dec != dec -> bool
                case D_DEC:return;                                  break;
                // dec != str -> error
                case D_STR:TYPE_ERROR("dec != str");                break;
                // dec != bool-> (bool)dec != bool -> bool != bool -> bool
                case D_BOOL:CodeGenerator::Convert(D_BOOL,r1_i);    break;
            }
            break;

        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
            {
                // bool != int -> bool != (bool)int -> bool != bool -> bool
                case D_INT:CodeGenerator::Convert(D_BOOL,r2_i);     break;
                // bool != dec -> bool != (bool)dec -> bool != bool -> bool
                case D_DEC:CodeGenerator::Convert(D_BOOL,r2_i);     break;
                // bool != str -> error
                case D_STR:TYPE_ERROR("bool != str");               break;
                // bool != bool-> bool
                case D_BOOL:return;                                 break;
            }
            break;
    }
}

void DataTypeChecker::Check_Less(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.type.data)
    {
        case D_INT:
            switch(R2.type.data)
            {
                // int < int -> bool
                case D_INT:return;                                  break;   
                // int < dec -> (dec)int < dec -> dec < dec -> bool
                case D_DEC:CodeGenerator::Convert(D_DEC,r1_i);      break;
                // int < str -> error
                case D_STR:TYPE_ERROR("int < str");                 break;            
                // int < bool-> error
                case D_BOOL:TYPE_ERROR("int < bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.type.data)
            {
                // dec < int -> dec < (dec)int -> dec < dec -> bool
                case D_INT:CodeGenerator::Convert(D_DEC,r2_i);      break;
                // dec < dec -> bool
                case D_DEC:return;                                  break;
                // dec < str -> error
                case D_STR:TYPE_ERROR("dec < str");                 break;
                // dec < bool-> error
                case D_BOOL:TYPE_ERROR("dec < bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
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

void DataTypeChecker::Check_LessEqual(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.type.data)
    {
        case D_INT:
            switch(R2.type.data)
            {
                // int <= int -> bool
                case D_INT:return;                                  break;   
                // int <= dec -> (dec)int <= dec -> dec <= dec -> bool
                case D_DEC:CodeGenerator::Convert(D_DEC,r1_i);      break;
                // int <= str -> error
                case D_STR:TYPE_ERROR("int <= str");                break;            
                // int <= bool-> error
                case D_BOOL:TYPE_ERROR("int <= bool");              break;
            }
            break;
        
        case D_DEC:
            switch(R2.type.data)
            {
                // dec <= int -> dec <= (dec)int -> dec <= dec -> bool
                case D_INT:CodeGenerator::Convert(D_DEC,r2_i);      break;
                // dec <= dec -> bool
                case D_DEC:return;                                  break;
                // dec <= str -> error
                case D_STR:TYPE_ERROR("dec <= str");                break;
                // dec <= bool-> error
                case D_BOOL:TYPE_ERROR("dec <= bool");              break;
            }
            break;
        
        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
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

void DataTypeChecker::Check_Greater(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.type.data)
    {
        case D_INT:
            switch(R2.type.data)
            {
                // int > int -> bool
                case D_INT:return;                                  break;   
                // int > dec -> (dec)int > dec -> dec > dec -> bool
                case D_DEC:CodeGenerator::Convert(D_DEC,r1_i);      break;
                // int > str -> error
                case D_STR:TYPE_ERROR("int > str");                 break;            
                // int > bool-> error
                case D_BOOL:TYPE_ERROR("int > bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.type.data)
            {
                // dec > int -> dec > (dec)int -> dec > dec -> bool
                case D_INT:CodeGenerator::Convert(D_DEC,r2_i);      break;
                // dec > dec -> bool
                case D_DEC:return;                                  break;
                // dec > str -> error
                case D_STR:TYPE_ERROR("dec > str");                 break;
                // dec > bool-> error
                case D_BOOL:TYPE_ERROR("dec > bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
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

void DataTypeChecker::Check_GreaterEqual(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);

    switch(R1.type.data)
    {
        case D_INT:
            switch(R2.type.data)
            {
                // int >= int -> bool
                case D_INT:return;                                  break;   
                // int >= dec -> (dec)int >= dec -> dec >= dec -> bool
                case D_DEC:CodeGenerator::Convert(D_DEC,r1_i);      break;
                // int >= str -> error
                case D_STR:TYPE_ERROR("int >= str");                break;            
                // int >= bool-> error
                case D_BOOL:TYPE_ERROR("int >= bool");              break;
            }
            break;
        
        case D_DEC:
            switch(R2.type.data)
            {
                // dec >= int -> dec >= (dec)int -> dec >= dec -> bool
                case D_INT:CodeGenerator::Convert(D_DEC,r2_i);      break;
                // dec >= dec -> bool
                case D_DEC:return;                                  break;
                // dec >= str -> error
                case D_STR:TYPE_ERROR("dec >= str");                break;
                // dec >= bool-> error
                case D_BOOL:TYPE_ERROR("dec >= bool");              break;
            }
            break;
        
        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
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
void DataTypeChecker::Check_Add(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);
    
    switch(R1.type.data)
    {
        case D_INT:
            switch(R2.type.data)
            {
                // int + int -> int
                case D_INT:return;                                  break;
                // int + dec -> (dec)int + dec -> dec + dec -> dec
                case D_DEC:CodeGenerator::Convert(D_DEC,r1_i);      break;
                // int + str -> error
                case D_STR:TYPE_ERROR("int + str");                 break;
                // int + bool-> error
                case D_BOOL:TYPE_ERROR("int + bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.type.data)
            {
                // dec + int -> dec + (dec)int -> dec + dec -> dec 
                case D_INT:CodeGenerator::Convert(D_DEC,r2_i);      break;
                // dec + dec -> dec
                case D_DEC:return;                                  break;
                // dec + str -> error
                case D_STR:TYPE_ERROR("dec + str");                 break;
                // dec + bool-> error
                case D_BOOL:TYPE_ERROR("dec + bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
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

void DataTypeChecker::Check_Sub(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);
    
    switch(R1.type.data)
    {   
        case D_INT:
            switch(R2.type.data)
            {
                // int - int -> int
                case D_INT:return;                                  break;
                // int - dec -> (dec)int - dec -> dec - dec -> dec
                case D_DEC:CodeGenerator::Convert(D_DEC,r1_i);      break;
                // int - str -> error
                case D_STR:TYPE_ERROR("int - str");                 break;
                // int - bool-> error
                case D_BOOL:TYPE_ERROR("int - bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.type.data)
            {
                // dec - int -> dec - (dec)int -> dec - dec -> dec 
                case D_INT:CodeGenerator::Convert(D_DEC,r2_i);      break;
                // dec - dec -> dec
                case D_DEC:return;                                  break;
                // dec - str -> error
                case D_STR:TYPE_ERROR("dec - str");                 break;
                // dec - bool-> error
                case D_BOOL:TYPE_ERROR("dec - bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
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

void DataTypeChecker::Check_Mul(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);
    
    switch(R1.type.data)
    {   
        case D_INT:
            switch(R2.type.data)
            {
                // int * int -> int
                case D_INT:return;                                  break;
                // int * dec -> (dec)int * dec -> dec * dec -> dec
                case D_DEC:CodeGenerator::Convert(D_DEC,r1_i);      break;
                // int * str -> error
                case D_STR:TYPE_ERROR("int * str");                 break;
                // int * bool-> error
                case D_BOOL:TYPE_ERROR("int * bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.type.data)
            {
                // dec * int -> dec * (dec)int -> dec * dec -> dec 
                case D_INT:CodeGenerator::Convert(D_DEC,r2_i);      break;
                // dec * dec -> dec
                case D_DEC:return;                                  break;
                // dec * str -> error
                case D_STR:TYPE_ERROR("dec * str");                 break;
                // dec * bool-> error
                case D_BOOL:TYPE_ERROR("dec * bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
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

void DataTypeChecker::Check_Div(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);
    
    switch(R1.type.data)
    {   
        case D_INT:
            switch(R2.type.data)
            {
                // int / int -> int
                case D_INT:return;                                  break;
                // int / dec -> (dec)int / dec -> dec / dec -> dec
                case D_DEC:CodeGenerator::Convert(D_DEC,r1_i);      break;
                // int / str -> error
                case D_STR:TYPE_ERROR("int / str");                 break;
                // int / bool-> error
                case D_BOOL:TYPE_ERROR("int / bool");               break;
            }
            break;
        
        case D_DEC:
            switch(R2.type.data)
            {
                // dec / int -> dec / (dec)int -> dec / dec -> dec 
                case D_INT:CodeGenerator::Convert(D_DEC,r2_i);      break;
                // dec / dec -> dec
                case D_DEC:return;                                  break;
                // dec / str -> error
                case D_STR:TYPE_ERROR("dec / str");                 break;
                // dec / bool-> error
                case D_BOOL:TYPE_ERROR("dec / bool");               break;
            }
            break;
        
        case D_STR:
            switch(R2.type.data)
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
            switch(R2.type.data)
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

void DataTypeChecker::Check_Mod(int r1_i,int r2_i,int line)
{
    Register& R1=general_register.GetReg(r1_i);
    Register& R2=general_register.GetReg(r2_i);
    
    switch(R1.type.data)
    {   
        case D_INT:
            switch(R2.type.data)
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
            switch(R2.type.data)
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
            switch(R2.type.data)
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
            switch(R2.type.data)
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

void DataTypeChecker::Check_Neg(int r_i,int line)
{
    Register& R=general_register.GetReg(r_i);
    
    switch(R.type.data)
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
