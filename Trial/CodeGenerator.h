#pragma once

#include "System.h"
#include "FileManager.h"
#include "Token.h"
#include "AbstractSyntaxTree.h"
#include "Register.h"
#include "SymbolTable.h"

#define NOTHING -1

class CodeGenerator
{
public:
    AST abstract_syntax_tree;

    CodeGenerator(AST abstract_syntax_tree):
                      abstract_syntax_tree(abstract_syntax_tree){}

    void CodeGen();

    static GeneralRegister general_register;
    static VariableTable vartable;
    
    //Instruction
    static void Var(Token type,string variable_name);
    static int LoadConstant(Token constant);
    static int LoadVariable(Token variable);
    static void Store(Token variable,int register_i,bool need_free);
    static void Print(int register_i);
    static int BinaryInstruction(int r1_i,Token Operator,int r2_i);
    static int UnaryInstruction(Token Operator,int register_i);

};