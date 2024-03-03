#pragma once

#include "System.h"
#include "FileManager.h"
#include "Token.h"
#include "AbstractSyntaxTree.h"
#include "Register.h"

#define NOTHING -1

class CodeGenerator
{
public:
    AST abstract_syntax_tree;

    CodeGenerator(AST abstract_syntax_tree):
                      abstract_syntax_tree(abstract_syntax_tree){}

    void CodeGen();

    static GeneralRegister general_register;
    //Instruction
    static int Load(Literal literal);
    static void Print(int register_i);
    static int BinaryInstruction(int r1_i,char Operator,int r2_i);
    static int UnaryInstruction(string Operator,int register_i);
    
};