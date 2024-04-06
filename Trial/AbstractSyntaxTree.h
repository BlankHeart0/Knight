#pragma once

#include "System.h"
#include "Token.h"
#include "Type.h"

class ASTNode
{
public:
    virtual ~ASTNode(){}
    virtual int CodeGen()=0;
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
    vector<ASTNode*> permission_definitions;
    vector<ASTNode*> function_definitions;
    
    int CodeGen() override;

    void Print(int depth) override;
};



// Definition
class PermissionDefinitionAST: public ASTNode
{
public:
    vector<Token> permissions;

    int CodeGen() override;

    void Print(int depth) override;
};



class FunctionDefinitionAST: public ASTNode
{
public:
    TypeAsToken ret_type;
    Token function_name;
    ASTNode* parameter_list;
    vector<ASTNode*> statements;

    FunctionDefinitionAST():parameter_list(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};

class ParameterAST: public ASTNode
{
public:
    TypeAsToken type;
    Token parameter_name;
     
    int CodeGen() override;
    
    void Print(int depth) override;
};

class ParameterListAST: public ASTNode
{
public:
    vector<ASTNode*> parameters;
 
    int CodeGen() override;
    
    void Print(int depth) override;
};



class LocalVariableDefinitionAST: public ASTNode
{
public:
    TypeAsToken type;
    Token variable_name;
    ASTNode* expression;

    LocalVariableDefinitionAST():expression(nullptr){}
    
    int CodeGen() override;
    
    void Print(int depth) override;
};



// Statement
class StatementAST: public ASTNode
{
public:
    ASTNode* X_statement;

    StatementAST():X_statement(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};

class CompoundStatementAST: public ASTNode
{
public:
    vector<ASTNode*> statements;

    int CodeGen() override;

    void Print(int depth) override;
};



class IfStatementAST: public ASTNode
{
public:
    ASTNode* expression;
    ASTNode* true_statement;
    ASTNode* false_statement;

    IfStatementAST():expression(nullptr),
        true_statement(nullptr),false_statement(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};

class WhileStatementAST: public ASTNode
{
public:
    ASTNode* expression;
    ASTNode* statement;

    WhileStatementAST():expression(nullptr),statement(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};

class ReturnStatementAST: public ASTNode
{
public:
    Token ret;
    ASTNode* expression;

    ReturnStatementAST():expression(nullptr){}
        
    int CodeGen() override;

    void Print(int depth) override;
};

class PrintStatementAST: public ASTNode
{
public:
    vector<ASTNode*> expressions;

    int CodeGen() override;

    void Print(int depth) override;
};

class AssignmentStatementAST: public ASTNode
{
public:
    Token variable;
    ASTNode* expression;

    AssignmentStatementAST():expression(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};

class ExpressionStatementAST: public ASTNode
{
public:
    ASTNode* expression;

    ExpressionStatementAST():expression(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};



// Expression
class ExpressionAST: public ASTNode
{
public:
    ASTNode* logicOr_expression;

    ExpressionAST():logicOr_expression(nullptr){}
    
    int CodeGen() override;

    void Print(int depth) override;
};



class LogicOrExpressionAST: public ASTNode
{
public:
    ASTNode* logicAnd_expression;
    vector<Token> infix_operators;
    vector<ASTNode*> logicAnd_expressions;

    LogicOrExpressionAST():logicAnd_expression(nullptr){}
        
    int CodeGen() override;

    void Print(int depth) override;
};

class LogicAndExpressionAST: public ASTNode
{
public:
    ASTNode* equality_expression;
    vector<Token> infix_operators;
    vector<ASTNode*> equality_expressions;

    LogicAndExpressionAST():equality_expression(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};



class EqualityExpressionAST: public ASTNode
{
public:
    ASTNode* relational_expression;
    vector<Token> infix_operators;
    vector<ASTNode*> relational_expressions;

    EqualityExpressionAST():relational_expression(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};

class RelationalExpressionAST: public ASTNode
{
public:
    ASTNode* plusminus_expression;
    vector<Token> infix_operators;
    vector<ASTNode*> plusminus_expressions;

    RelationalExpressionAST():plusminus_expression(nullptr){}
    
    int CodeGen() override;

    void Print(int depth) override;
};



class PlusMinusExpressionAST: public ASTNode
{
public:
    ASTNode* muldiv_expression;
    
    vector<Token> infix_operators;
    vector<ASTNode*> muldiv_expressions;

    PlusMinusExpressionAST():muldiv_expression(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};

class MulDivExpressionAST: public ASTNode
{
public:
    ASTNode* unary_expression;

    vector<Token> infix_operators;
    vector<ASTNode*> unary_expressions;

    MulDivExpressionAST():unary_expression(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};



class UnaryExpressionAST: public ASTNode
{
public:
    Token prefix_operator;
    ASTNode* primary_expression;
    ASTNode* functioncall_expression;

    UnaryExpressionAST():
        primary_expression(nullptr),functioncall_expression(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};

class PrimaryExpressionAST: public ASTNode
{
public:
    ASTNode* expression;
    Token constant;
    Token variable;

    PrimaryExpressionAST():expression(nullptr){}

    int CodeGen() override;

    void Print(int depth) override;
};

class FunctionCallExpressionAST: public ASTNode
{
public:
    Token function;
    vector<ASTNode*> expressions;

    int CodeGen() override;

    void Print(int depth) override;
};