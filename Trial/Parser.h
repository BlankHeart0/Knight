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
    AST abstract_syntax_tree;

    Parser(vector<Token> tokens):tokens(tokens),current(0),line(0){}

    void Parse();

    // Begin
    ASTNode* Parse_Translation_Unit();

    // Definition
    ASTNode* Parse_Permission_Definition();

    TypeAsToken Parse_Type();
    ASTNode* Parse_Function_Definition();
    ASTNode* Parse_Parameter();
    ASTNode* Parse_Parameter_List();

    ASTNode* Parse_LocalVariable_Definition();
    
    // Statement
    ASTNode* Parse_Statement();
    ASTNode* Parse_Compound_Statement();

    ASTNode* Parse_If_Statement();
    ASTNode* Parse_While_Statement();
    ASTNode* Parse_Return_Statement();
    ASTNode* Parse_Print_Statement();
    ASTNode* Parse_Assignment_Statement();
    ASTNode* Parse_Expression_Statement();

    // Expression
    ASTNode* Parse_Expression();

    ASTNode* Parse_LogicOr_Expression();
    ASTNode* Parse_LogicAnd_Expression();

    ASTNode* Parse_Equality_Expression();
    ASTNode* Parse_Relational_Expression();

    ASTNode* Parse_PlusMinus_Expression();
    ASTNode* Parse_MulDiv_Expression();
    
    ASTNode* Parse_Unary_Expression();
    ASTNode* Parse_Primary_Expression();
    ASTNode* Parse_FunctionCall_Expression();

    void AddChildToVector(vector<ASTNode*>& vec, ASTNode* child );
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
