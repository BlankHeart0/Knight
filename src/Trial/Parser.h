#pragma once

#include "System.h"
#include "AbstractSyntaxTree.h"
#include "Diagnostor.h"

class Parser
{
public:
    vector<Token> tokens;
    int current;
    int line;

    Parser(vector<Token> tokens):tokens(tokens),current(0),line(0){}

    void Parse();

    // Begin
    unique_ptr<ASTNode> Parse_Translation_Unit();

    // Definition
    unique_ptr<ASTNode> Parse_Permission_Definition();

    TypeAsToken Parse_Type();
    unique_ptr<ASTNode> Parse_Invoke_Definition();
    unique_ptr<ASTNode> Parse_Function_Definition();
    unique_ptr<ASTNode> Parse_Parameter();
    unique_ptr<ASTNode> Parse_Parameter_List();

    unique_ptr<ASTNode> Parse_LocalVariable_Definition();
    
    // Statement
    unique_ptr<ASTNode> Parse_Statement();
    unique_ptr<ASTNode> Parse_Compound_Statement();

    unique_ptr<ASTNode> Parse_If_Statement();
    unique_ptr<ASTNode> Parse_While_Statement();
    unique_ptr<ASTNode> Parse_Return_Statement();
    unique_ptr<ASTNode> Parse_Exit_Statement();
    unique_ptr<ASTNode> Parse_Input_Statement();
    unique_ptr<ASTNode> Parse_Output_Statement();
    unique_ptr<ASTNode> Parse_Assignment_Statement();
    unique_ptr<ASTNode> Parse_Expression_Statement();

    // Expression
    unique_ptr<ASTNode> Parse_Expression();

    unique_ptr<ASTNode> Parse_LogicOr_Expression();
    unique_ptr<ASTNode> Parse_LogicAnd_Expression();

    unique_ptr<ASTNode> Parse_Equality_Expression();
    unique_ptr<ASTNode> Parse_Relational_Expression();

    unique_ptr<ASTNode> Parse_PlusMinus_Expression();
    unique_ptr<ASTNode> Parse_MulDiv_Expression();
    
    unique_ptr<ASTNode> Parse_Unary_Expression();
    unique_ptr<ASTNode> Parse_Primary_Expression();
    unique_ptr<ASTNode> Parse_FunctionCall_Expression();

    void AddChildToVector(vector<unique_ptr<ASTNode>>& vec, unique_ptr<ASTNode> child );
    Token PreviousToken();

    bool IsAtEnd();
    bool Match(TokenType expected);
    void MatchSemicolon();
    bool Peek(TokenType expected);
    bool Peek(TokenType expected,int n);

};

#define PARSE_ERROR(error_message)                              \
        do{                                                     \
            diagnostor.Error(E_PARSER,line,error_message);      \
        }while(0)
