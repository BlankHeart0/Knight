#pragma once

#include "System.h"
#include "FileManager.h"
#include "Token.h"
#include "Type.h"
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

    static string gen_fucntion;
    static Function& NowInFunction();
    static FunctionTable functable;

    // Instruction
    // Variable
    static void Var(Token type,string variable_name);   // VAR var
    static int  LoadConstant(Token constant);           // LOAD load
    static int  LoadVariable(Token variable);           // LOAD load
    static void Store(Token variable,int r_i,bool need_free);// STORE store
    static void Convert(DataType to_dataType,int r_i);       // CVT cvt
    
    // Function    
    static void Func(Token type,string function_name);  // FUNC func
    static int  TransX2R(int x_i);                      // TRANS trans
    static void TransR2X(int x_i,int r_i);              // TRANS trans
    static void TransY2R(int r_i);                      // TRANS trans
    static void TransR2Y(int r_i,int line);             // TRANS trans
    static int  Call(Token function);                   // CALL call
    static void Ret();                                  // RET ret
    static void Push(int r_i);                          // PUSH push
    static void Pop(int r_i);                           // POP pop
    static void Print(int r_i);                         // PRINT print
    
    // Control Flow
    static void Lable(int lable_id);                    // LABLE lable  
    static void Jump(int lable_id);                     // JMP jmp
    static void JumpTrue(int lable_id,int r_i);         // JMPT jmpt
    static void JumpFalse(int lable_id,int r_i);        // JMPF jmpf
    
    // Binary
    static int BinaryInstruction(int r1_i,Token Operator,int r2_i);
    // Logic
    static int Or(int r1_i,int r2_i,int line);          // OR or
    static int And(int r1_i,int r2_i,int line);         // AND and
    static int Equal(int r1_i,int r2_i,int line);       // EQU equ
    static int NotEqual(int r1_i,int r2_i,int line);    // NEQU nequ
    static int Less(int r1_i,int r2_i,int line);        // LES les
    static int LessEqual(int r1_i,int r2_i,int line);   // LEQU lequ
    static int Greater(int r1_i,int r2_i,int line);     // GRE gre
    static int GreaterEqual(int r1_i,int r2_i,int line);// GEQU gequ
    // Arithmetic
    static int Add(int r1_i,int r2_i,int line);         // ADD add
    static int Sub(int r1_i,int r2_i,int line);         // SUB sub
    static int Mul(int r1_i,int r2_i,int line);         // MUL mul
    static int Div(int r1_i,int r2_i,int line);         // DIV div
    static int Mod(int r1_i,int r2_i,int line);         // MOD mod

    // Unary
    static int UnaryInstruction(Token Operator,int r_i);
    static int Neg(int r_i,int line);                   // NEG neg
    static int Not(int r_i,int line);                   // NOT not

};