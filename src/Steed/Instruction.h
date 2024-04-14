#pragma once

#include "System.h"
#include "Operand.h"
#include "Register.h"

class Instruction
{
public:
    bool is_directive;

    Instruction(bool is_directive):is_directive(is_directive){}

    virtual ~Instruction(){}
    virtual void Excute()=0;
};


// Type
class Perm: public Instruction
{
public:
    OperandPermission operand1_permission;
    OperandFlag       operand2_flag;

    Perm(OperandPermission operand1_permission, OperandFlag operand2_flag):
        operand1_permission(operand1_permission),operand2_flag(operand2_flag),
        Instruction(true){}

    void Excute() override;
};

class Test: public Instruction
{
public:
    OperandRegister   operand1_register;
    OperandPermission operand2_permission;

    Test(OperandRegister operand1_register,OperandPermission operand2_permission):
        operand1_register(operand1_register),operand2_permission(operand2_permission),
        Instruction(false){}

    void Excute() override;    
};

class Cvt: public Instruction
{
public:
    OperandType     operand1_type;
    OperandRegister operand2_register;

    Cvt(OperandType operand1_type,OperandRegister operand2_register):
        operand1_type(operand1_type),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;    
};



// Variable
class Var: public Instruction
{
public:
    OperandType     operand1_type;
    OperandVariable operand2_variable;

    Var(OperandType operand1_type,OperandVariable operand2_variable):
        operand1_type(operand1_type),operand2_variable(operand2_variable),
        Instruction(false){}

    void Excute() override;
};

class LoadConstant: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandConstant operand2_constant;

    LoadConstant(OperandRegister operand1_register,OperandConstant operand2_constant):
        operand1_register(operand1_register),operand2_constant(operand2_constant),
        Instruction(false){}

    void Excute() override;
};

class LoadVariable: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandVariable operand2_variable;

    LoadVariable(OperandRegister operand1_register,OperandVariable operand2_variable):
        operand1_register(operand1_register),operand2_variable(operand2_variable),
        Instruction(false){}

    void Excute() override;
};

class Store: public Instruction
{
public:
    OperandVariable operand1_variable;
    OperandRegister operand2_register;

    Store(OperandVariable operand1_variable,OperandRegister operand2_register):
        operand1_variable(operand1_variable),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;    
};



// Function
class Invoke: public Instruction
{
public:
    OperandApplication operand1_application;
    OperandFunction    operand2_function;

    Invoke(OperandApplication operand1_application,OperandFunction operand2_function):
        operand1_application(operand1_application),operand2_function(operand2_function),
        Instruction(true){}

    void Excute() override;  
};

class Func: public Instruction
{
public:
    OperandType     operand1_type;
    OperandFunction operand2_function;

    Func(OperandType operand1_type,OperandFunction operand2_function):
        operand1_type(operand1_type),operand2_function(operand2_function),
        Instruction(true){}

    void Excute() override;  
};

class Trans: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Trans(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;  
};

class Call:public Instruction
{
public:
    OperandFunction operand1_function;

    Call(OperandFunction operand1_function):
        operand1_function(operand1_function),
        Instruction(false){}

    void Excute() override;  
};

class Ret:public Instruction
{
public:
    Ret():Instruction(false){}

    void Excute() override;  
};

class Exit:public Instruction
{
public:
    Exit():Instruction(false){}

    void Excute() override;
};

class Sleep:public Instruction
{
public:
    OperandNatural operand1_natural;

    Sleep(OperandNatural operand1_natural):
        operand1_natural(operand1_natural),
        Instruction(false){}

    void Excute() override;  
};

class Push:public Instruction
{
public:
    OperandRegister operand1_register;

    Push(OperandRegister operand1_register):
        operand1_register(operand1_register),
        Instruction(false){}

    void Excute() override;  
};

class Pop:public Instruction
{
public:
    OperandRegister operand1_register;

    Pop(OperandRegister operand1_register):
        operand1_register(operand1_register),
        Instruction(false){}

    void Excute() override; 
};

class Input: public Instruction
{
public:
    OperandVariable operand1_variable;

    Input(OperandVariable operand1_variable):
        operand1_variable(operand1_variable),
        Instruction(false){}

    void Excute() override;
};

class OutputRegister: public Instruction
{
public:
    OperandRegister operand1_register;

    OutputRegister(OperandRegister operand1_register):
        operand1_register(operand1_register),
        Instruction(false){}

    void Excute() override;
};

class OutputEndline: public Instruction
{
public:
    OutputEndline():Instruction(false){}

    void Excute() override;
};



// Control Flow
class Lable: public Instruction
{
public:
    OperandLable operand1_lable;

    Lable(OperandLable operand1_lable):
        operand1_lable(operand1_lable),
        Instruction(true){}
    
    void Excute() override;
};

class Jmp: public Instruction
{
public:
    OperandLable operand1_lable;
    
    Jmp(OperandLable operand1_lable):
        operand1_lable(operand1_lable),
        Instruction(false){}

    void Excute() override;
};

class Jmpt: public Instruction
{
public:
    OperandLable    operand1_lable;
    OperandRegister operand2_register;

    Jmpt(OperandLable operand1_lable,OperandRegister operand2_register):
        operand1_lable(operand1_lable),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;
};

class Jmpf: public Instruction
{
public:
    OperandLable    operand1_lable;
    OperandRegister operand2_register;

    Jmpf(OperandLable operand1_lable,OperandRegister operand2_register):
        operand1_lable(operand1_lable),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;
};



// Binary
class Or: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Or(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;
};

class And: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    And(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;
};

class Equ: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Equ(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;
};

class Nequ: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Nequ(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;
};

class Les: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Les(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;
};

class Lequ: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Lequ(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;
};

class Gre: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Gre(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;
};

class Gequ: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Gequ(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;
};

class Add: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Add(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}

    void Excute() override;
};

class Sub: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Sub(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}
    
    void Excute() override;
};

class Mul: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Mul(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}
    
    void Excute() override;
};

class Div: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Div(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}
    
    void Excute() override;
};

class Mod: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;
    
    Mod(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register),
        Instruction(false){}
  
    void Excute() override;
};



// Unary
class Neg: public Instruction
{
public:
    OperandRegister operand1_register;

    Neg(OperandRegister operand1_register):
        operand1_register(operand1_register),
        Instruction(false){}

    void Excute() override;
};

class Not: public Instruction
{
public:
    OperandRegister operand1_register;

    Not(OperandRegister operand1_register):
        operand1_register(operand1_register),
        Instruction(false){}

    void Excute() override;
};
