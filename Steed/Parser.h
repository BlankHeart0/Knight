#pragma once

#include "System.h"
#include "Instruction.h"
#include "Operand.h"

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
OperandType Parse_OperandType(string& operand_str);
OperandVariable Parse_OperandVariable(string& operand_str);

// Var
Instruction* Parse_Var(string& operand1,string& operand2);
// Load&Store
Instruction* Parse_Load(string& operand1,string& operand2);
Instruction* Parse_Store(string& operand1,string& operand2);

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
    // Var
    {"Var",Parse_Var},
    // Load
    {"Load",Parse_Load},
    {"Store",Parse_Store},
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