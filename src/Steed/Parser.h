#pragma once

#include "System.h"
#include "Operand.h"
#include "Instruction.h"

class Parser
{
private:
    string line_code;

public:
    string opcode_str;
    string operand1_str;
    string operand2_str;

    Parser(string line_code);
    unique_ptr<Instruction> Parse();
};



// Operand
OperandConstant    Parse_OperandConstant    (string& operand_str);
OperandRegister    Parse_OperandRegister    (string& operand_str);
OperandType        Parse_OperandType        (string& operand_str);
OperandPermission  Parse_OperandPermission  (string& operand_str);
OperandApplication Parse_OperandApplication (string& operand_str);
OperandFunction    Parse_OperandFunction    (string& operand_str);
OperandVariable    Parse_OperandVariable    (string& operand_str);
OperandLable       Parse_OperandLable       (string& operand_str);



// Instruction
// Type
unique_ptr<Instruction> Parse_Perm  (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Test  (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Cvt   (string& operand1_str,string& operand2_str);

// Variable
unique_ptr<Instruction> Parse_Var   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Load  (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Store (string& operand1_str,string& operand2_str);

// Function
unique_ptr<Instruction> Parse_Invoke(string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Func  (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Trans (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Call  (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Ret   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Exit  (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Push  (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Pop   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Input (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Output(string& operand1_str,string& operand2_str);

// Control Flow
unique_ptr<Instruction> Parse_Lable (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Jmp   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Jmpt  (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Jmpf  (string& operand1_str,string& operand2_str);

// Binary
unique_ptr<Instruction> Parse_Or    (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_And   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Equ   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Nequ  (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Les   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Lequ  (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Gre   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Gequ  (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Add   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Sub   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Mul   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Div   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Mod   (string& operand1_str,string& operand2_str);

// Unary
unique_ptr<Instruction> Parse_Neg   (string& operand1_str,string& operand2_str);
unique_ptr<Instruction> Parse_Not   (string& operand1_str,string& operand2_str);



static unordered_map<string,unique_ptr<Instruction>(*)(string&,string&)> ParseInstruction_map
{   
    // Type
    {"PERM",Parse_Perm},    {"perm",Parse_Perm},
    {"TEST",Parse_Test},    {"test",Parse_Test},
    {"CVT",Parse_Cvt},      {"cvt",Parse_Cvt},

    // Var
    {"VAR",Parse_Var},      {"var",Parse_Var},
    {"LOAD",Parse_Load},    {"load",Parse_Load},
    {"STORE",Parse_Store},  {"store",Parse_Store},

    // Function
    {"INVOKE",Parse_Invoke},{"invoke",Parse_Invoke},
    {"FUNC",Parse_Func},    {"func",Parse_Func},
    {"TRANS",Parse_Trans},  {"trans",Parse_Trans},
    {"CALL",Parse_Call},    {"call",Parse_Call},
    {"RET",Parse_Ret},      {"ret",Parse_Ret},
    {"EXIT",Parse_Exit},    {"exit",Parse_Exit},
    {"PUSH",Parse_Push},    {"push",Parse_Push},
    {"POP",Parse_Pop},      {"pop",Parse_Pop},
    {"INPUT",Parse_Input},  {"input",Parse_Input},
    {"OUTPUT",Parse_Output},{"output",Parse_Output},

    // Control Flow
    {"LABLE",Parse_Lable},  {"lable",Parse_Lable},
    {"JMP",Parse_Jmp},      {"jmp",Parse_Jmp},
    {"JMPT",Parse_Jmpt},    {"jmpt",Parse_Jmpt},
    {"JMPF",Parse_Jmpf},    {"jmpf",Parse_Jmpf},

    // Binary
    {"OR",Parse_Or},        {"or",Parse_Or},
    {"AND",Parse_And},      {"and",Parse_And},
    {"EQU",Parse_Equ},      {"equ",Parse_Equ},
    {"NEQU",Parse_Nequ},    {"nequ",Parse_Nequ},
    {"LES",Parse_Les},      {"les",Parse_Les},
    {"LEQU",Parse_Lequ},    {"lequ",Parse_Lequ},
    {"GRE",Parse_Gre},      {"gre",Parse_Gre},
    {"GEQU",Parse_Gequ},    {"gequ",Parse_Gequ},
    {"ADD",Parse_Add},      {"add",Parse_Add},
    {"SUB",Parse_Sub},      {"sub",Parse_Sub},
    {"MUL",Parse_Mul},      {"mul",Parse_Mul},
    {"DIV",Parse_Div},      {"div",Parse_Div},
    {"MOD",Parse_Mod},      {"mod",Parse_Mod},

    //Unary
    {"NEG",Parse_Neg},    {"neg",Parse_Neg},
    {"NOT",Parse_Not},    {"not",Parse_Not},
};
