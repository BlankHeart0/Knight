#pragma once

#include "System.h"
#include "Instruction.h"

class Parser
{
public: 
    string knightASM_code;
    int current;

    string opcode;
    string operand1;
    string operand2;

    Parser(string knightASM_code):
        knightASM_code(knightASM_code),current(0){}

    Instruction* Parse();
};

// Operand
OperandConstant Parse_OperandConstant(string& operand_str);
OperandRegister Parse_OperandRegister(string& operand_str);

// Load
Instruction* Parse_Load_ConstantToRegister(string& operand1,string& operand2);

// Print
Instruction* Parse_Print(string& operand1,string& operand2);

// Binary
Instruction* Parse_Add(string& operand1,string& operand2);
Instruction* Parse_Sub(string& operand1,string& operand2);
Instruction* Parse_Mul(string& operand1,string& operand2);
Instruction* Parse_Div(string& operand1,string& operand2);
Instruction* Parse_Mod(string& operand1,string& operand2);

// Unary
Instruction* Parse_Neg(string& operand1,string& operand2);


static unordered_map<string,Instruction* (*)(string&,string&)> ParseFunction_map
{
    // Load
    {"Load",Parse_Load_ConstantToRegister},
    
    // Print
    {"Print",Parse_Print},

    // Binary
    {"Add",Parse_Add},
    {"Sub",Parse_Sub},
    {"Mul",Parse_Mul},
    {"Div",Parse_Div},
    {"Mod",Parse_Mod},

    //Unary
    {"Neg",Parse_Neg}
};