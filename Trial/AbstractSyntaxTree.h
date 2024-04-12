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
    unique_ptr<ASTNode> translation_unit;

    void CodeGen();
    void Print();
};

extern AST abstract_syntax_tree;



// Begin
class TranslationUnitAST: public ASTNode
{
public:    
    vector<unique_ptr<ASTNode>> permission_definitions;
    vector<unique_ptr<ASTNode>> function_definitions;
    
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
    unique_ptr<ASTNode> parameter_list;
    vector<unique_ptr<ASTNode>> statements;

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
    vector<unique_ptr<ASTNode>> parameters;
 
    int CodeGen() override;
    void Print(int depth) override;
};



class LocalVariableDefinitionAST: public ASTNode
{
public:
    TypeAsToken type;
    Token variable_name;
    unique_ptr<ASTNode> expression;
    
    int CodeGen() override;
    void Print(int depth) override;
};



// Statement
class StatementAST: public ASTNode
{
public:
    unique_ptr<ASTNode> X_statement;

    int CodeGen() override;
    void Print(int depth) override;
};

class CompoundStatementAST: public ASTNode
{
public:
    vector<unique_ptr<ASTNode>> statements;

    int CodeGen() override;
    void Print(int depth) override;
};



class IfStatementAST: public ASTNode
{
public:
    Token If;
    unique_ptr<ASTNode> expression;
    unique_ptr<ASTNode> true_statement;
    unique_ptr<ASTNode> false_statement;

    int CodeGen() override;
    void Print(int depth) override;
};

class WhileStatementAST: public ASTNode
{
public:
    Token While;
    unique_ptr<ASTNode> expression;
    unique_ptr<ASTNode> statement;

    int CodeGen() override;
    void Print(int depth) override;
};

class ReturnStatementAST: public ASTNode
{
public:
    Token ret;
    unique_ptr<ASTNode> expression;
        
    int CodeGen() override;
    void Print(int depth) override;
};

class ExitStatementAST: public ASTNode
{
public:
    Token exit;

    int CodeGen() override;
    void Print(int depth) override;
};

class InputStatementAST: public ASTNode
{
public:
    vector<Token> variables;
        
    int CodeGen() override;
    void Print(int depth) override;  
};

class OutputStatementAST: public ASTNode
{
public:
    Token output;
    vector<unique_ptr<ASTNode>> expressions;

    int CodeGen() override;
    void Print(int depth) override;
};

class AssignmentStatementAST: public ASTNode
{
public:
    Token variable;
    unique_ptr<ASTNode> expression;

    int CodeGen() override;
    void Print(int depth) override;
};

class ExpressionStatementAST: public ASTNode
{
public:
    unique_ptr<ASTNode> expression;

    int CodeGen() override;
    void Print(int depth) override;
};



// Expression
class ExpressionAST: public ASTNode
{
public:
    unique_ptr<ASTNode> logicOr_expression;
    
    int CodeGen() override;
    void Print(int depth) override;
};



class LogicOrExpressionAST: public ASTNode
{
public:
    unique_ptr<ASTNode> logicAnd_expression;
    vector<Token> infix_operators;
    vector<unique_ptr<ASTNode>> logicAnd_expressions;
        
    int CodeGen() override;
    void Print(int depth) override;
};

class LogicAndExpressionAST: public ASTNode
{
public:
    unique_ptr<ASTNode> equality_expression;
    vector<Token> infix_operators;
    vector<unique_ptr<ASTNode>> equality_expressions;

    int CodeGen() override;
    void Print(int depth) override;
};



class EqualityExpressionAST: public ASTNode
{
public:
    unique_ptr<ASTNode> relational_expression;
    vector<Token> infix_operators;
    vector<unique_ptr<ASTNode>> relational_expressions;

    int CodeGen() override;
    void Print(int depth) override;
};

class RelationalExpressionAST: public ASTNode
{
public:
    unique_ptr<ASTNode> plusminus_expression;
    vector<Token> infix_operators;
    vector<unique_ptr<ASTNode>> plusminus_expressions;
    
    int CodeGen() override;
    void Print(int depth) override;
};



class PlusMinusExpressionAST: public ASTNode
{
public:
    unique_ptr<ASTNode> muldiv_expression;
    vector<Token> infix_operators;
    vector<unique_ptr<ASTNode>> muldiv_expressions;

    int CodeGen() override;
    void Print(int depth) override;
};

class MulDivExpressionAST: public ASTNode
{
public:
    unique_ptr<ASTNode> unary_expression;
    vector<Token> infix_operators;
    vector<unique_ptr<ASTNode>> unary_expressions;

    int CodeGen() override;
    void Print(int depth) override;
};



class UnaryExpressionAST: public ASTNode
{
public:
    Token prefix_operator;
    unique_ptr<ASTNode> primary_expression;
    unique_ptr<ASTNode> functioncall_expression;

    int CodeGen() override;
    void Print(int depth) override;
};

class PrimaryExpressionAST: public ASTNode
{
public:
    unique_ptr<ASTNode> expression;
    Token constant;
    Token variable;

    int CodeGen() override;
    void Print(int depth) override;
};

class FunctionCallExpressionAST: public ASTNode
{
public:
    Token function;
    vector<unique_ptr<ASTNode>> expressions;

    int CodeGen() override;
    void Print(int depth) override;
};