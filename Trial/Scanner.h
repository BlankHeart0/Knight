#pragma once

#include "System.h"
#include "Token.h"
#include "Diagnostor.h"

class Scanner{
public:
    string source;
    vector<Token> tokens;
    int start;
    int current;
    int line;

    Scanner(string source):source(source),start(0),current(0),line(1){}

    void ScanTokens();
    void ScanToken();

    void Scan_Number();
    void Scan_Str();
    char NextChar();

    void ScanIdentifierKeyword();


    bool IsAtEnd();
    char Advance();
    bool Match(char expected);
    char Peek();
    char PeekNext();

  
    bool IsDigit(char c);
    bool IsAlphaUnderline(char c);
    bool IsDigitAlphaUnderline(char c);

    void AddToken(TokenType token_type,Literal literal);
    void AddToken(TokenType token_type);
    void AddToken(TokenType token_type,int literal_int);
    void AddToken(TokenType token_type,double literal_dec);
    void AddToken(TokenType token_type,string literal_str);

    void Tokens_PrintTable();
};

#define SCAN_ERROR(error_message)                               \
        do{                                                     \
            diagnostor.Error(E_SCANNER,line,error_message);     \
        }while(0)
