#pragma once

#include "System.h"
#include "Token.h"
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
    ASTNode* Parse_Function_Definition();
    // Statement
    ASTNode* Parse_Statement();
    ASTNode* Parse_Compound_Statement();
    ASTNode* Parse_Expression_Statement();
    // Expression
    ASTNode* Parse_Expression();
    ASTNode* Parse_MulDiv_Expression();
    ASTNode* Parse_Unary_Expression();
    ASTNode* Parse_Primary_Expression();

    void AddChildToVector(vector<ASTNode*>& vec, ASTNode* child );
    bool IsAtEnd();
    bool Match(TokenType expected);
    void MatchSemicolon();
    bool Peek(TokenType expected);
    bool Peek(TokenType expected,int n);

    Token PreviousToken();

};

#define PARSE_ERROR(error_message)                              \
        do{                                                     \
            diagnostor.Error(E_PARSER,line,error_message);      \
        }while(0)
