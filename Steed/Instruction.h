#pragma once

#include "System.h"
#include "Operand.h"
#include "Register.h"

class Instruction
{
public:
    virtual ~Instruction(){}
    virtual void Excute()=0;
};



// Load
class Load_ConstantToRegister: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandConstant operand2_constant;

    Load_ConstantToRegister
        (OperandRegister operand1_register,OperandConstant operand2_constant):
        operand1_register(operand1_register),operand2_constant(operand2_constant){}

    void Excute() override;
};



// Print
class Print: public Instruction
{
public:
    OperandRegister operand1_register;

    Print(OperandRegister operand1_register):operand1_register(operand1_register){}

    void Excute() override;
};



// Binary
class Add: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Add(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register){}

    void Excute() override;
};

class Sub: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Sub(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register){}
    
    void Excute() override;
};

class Mul: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Mul(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register){}
    
    void Excute() override;
};

class Div: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;

    Div(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register){}
    
    void Excute() override;
};

class Mod: public Instruction
{
public:
    OperandRegister operand1_register;
    OperandRegister operand2_register;
    
    Mod(OperandRegister operand1_register,OperandRegister operand2_register):
        operand1_register(operand1_register),operand2_register(operand2_register){}
  
    void Excute() override;
};



// Unary
class Neg: public Instruction
{
public:
    OperandRegister operand1_register;

    Neg(OperandRegister operand1_register):operand1_register(operand1_register){}

    void Excute() override;
};