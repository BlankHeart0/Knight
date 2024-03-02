#pragma once

#include "System.h"

enum TokenType
{
    //Keyword
    INT, DEC, STR,
    BOOL, TRUE, FALSE,
    IF, ELSE, WHILE,
    RET,

    //Identifier
    IDENTIFIER,

    //Separator
    SEMICOLON, COMMA, COLON, // ; , :
    LEFT_PAREN, RIGHT_PAREN, // ( )
    LEFT_BRACE, RIGHT_BRACE, // { }
    
    //Operator
    PLUS, MINUS, STAR, SLASH, PERCENT, // + - * / %
    
    ASSIGN, // =

    EQUAL, NOT_EQUAL,       // ?= !=
    LESS, LESS_EQUAL,       // <  <=
    GREATER, GREATER_EQUAL, // >  >=

    //Constant
    CONSTANT_INT, CONSTANT_DEC, CONSTANT_STR,

    //End
    CODE_EOF
};

static vector<string>TokenType_text
{
    //Keyword
    "INT", "DEC", "STR",
    "BOOL", "TRUE", "FALSE",
    "IF", "ELSE", "WHILE",
    "RET",

    //Identifier
    "IDENTIFIER",

    //Separator
    "SEMICOLON", "COMMA", "COLON", // ; , :
    "LEFT_PAREN", "RIGHT_PAREN", // ( )
    "LEFT_BRACE", "RIGHT_BRACE", // { }
    
    //Operator
    "PLUS", "MINUS", "STAR", "SLASH", "PERCENT", // + - * / %
    
    "ASSIGN", // =

    "EQUAL", "NOT_EQUAL",       // ?= !=
    "LESS", "LESS_EQUAL",       // <  <=
    "GREATER", "GREATER_EQUAL", // >  >=

    //Constant
    "CONSTANT_INT", "CONSTANT_DEC", "CONSTANT_STR",

    //End
    "CODE_EOF"
};

static unordered_map<string,TokenType>Keyword_map
{
    {"int",INT}, {"dec",DEC}, {"str",STR},
    {"bool",BOOL}, {"true", TRUE}, {"flase",FALSE},
    {"if",IF}, {"else",ELSE}, {"while",WHILE},
    {"ret",RET}
};


enum LiteralType
{
    L_INT,L_DEC,L_STR,
};

class Literal
{
public:
    bool is_valid;
    LiteralType literal_type;

    int literal_int;
    double literal_dec;
    string literal_str;
    
    Literal():is_valid(false){}
    Literal(int literal_int):is_valid(true),literal_type(L_INT),literal_int(literal_int){}
    Literal(double literal_dec):is_valid(true),literal_type(L_DEC),literal_dec(literal_dec){}
    Literal(string literal_str):is_valid(true),literal_type(L_STR),literal_str(literal_str){}

};

class Token{
public:
    TokenType token_type;
    string lexeme;
    Literal literal;
    int line;

    Token(TokenType token_type,string lexeme,Literal literal,int line):
        token_type(token_type),lexeme(lexeme),literal(literal),line(line){}
};