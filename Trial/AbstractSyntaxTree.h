#pragma once

#include "System.h"
#include "Token.h"

class ASTNode
{
public:
    virtual ~ASTNode(){}
    //virtual int CodeGen()=0;
    virtual void Print(int depth)=0;
};

class AST
{
public:
    ASTNode* translation_unit;

    AST():translation_unit(nullptr){}

    void CodeGen();
    void Print();
};



// Begin
class TranslationUnitAST: public ASTNode
{
public:
    vector<ASTNode*>function_definitions;
    
    //int CodeGen() override;

    void Print(int depth) override;
};



// Definition
class FunctionDefinitionAST: public ASTNode
{
public:
    string function_name;
    ASTNode* compound_statement;

    FunctionDefinitionAST():compound_statement(nullptr){}

    //int CodeGen() override;

    void Print(int depth) override;
};



// Statement
class StatementAST: public ASTNode
{
public:
    ASTNode* X_statement;

    StatementAST():X_statement(nullptr){}

    //int CodeGen() override;

    void Print(int depth) override;
};

class CompoundStatementAST: public ASTNode
{
public:
    vector<ASTNode*>statements;

    //int CodeGen() override;

    void Print(int depth) override;
};

class PrintStatementAST: public ASTNode
{
public:
    ASTNode* expression;
    PrintStatementAST():expression(nullptr){}

    //int CodeGen() override;

    void Print(int depth) override;

};

class ExpressionStatementAST: public ASTNode
{
public:
    ASTNode* expression;

    ExpressionStatementAST():expression(nullptr){}

    //int CodeGen() override;

    void Print(int depth) override;
};



// Expression
class ExpressionAST: public ASTNode
{
public:
    ASTNode* muldiv_expression;
    
    vector<char> infix_operators;
    vector<ASTNode*> muldiv_expressions;

    ExpressionAST():muldiv_expression(nullptr){}

    //int CodeGen() override;

    void Print(int depth) override;
};

class MulDivExpressionAST: public ASTNode
{
public:
    ASTNode* unary_expression;

    vector<char> infix_operators;
    vector<ASTNode*> unary_expressions;

    MulDivExpressionAST():unary_expression(nullptr){}

    //int CodeGen() override;

    void Print(int depth) override;
};

class UnaryExpressionAST: public ASTNode
{
public:
    string prefix_operator;
    ASTNode* primary_expression;

    UnaryExpressionAST():prefix_operator(""),primary_expression(nullptr){}

    //int CodeGen() override;

    void Print(int depth) override;
};

class PrimaryExpressionAST: public ASTNode
{
public:
    ASTNode* expression;
    Literal literal;

    PrimaryExpressionAST():expression(nullptr){}

    //int CodeGen() override;

    void Print(int depth) override;
};