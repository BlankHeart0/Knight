#pragma once

#include "System.h"

enum TokenType
{
    //Keyword
    INT, DEC, STR,
    BOOL, TRUE, FALSE,
    IF, ELSE, WHILE,
    INPUT, OUTPUT, 
    RET, EXIT, 
    PERMISSION,

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
    NOT, AND, OR,       //not and or

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
    "INPUT", "OUTPUT", 
    "RET", "EXIT", 
    "PERMISSION",

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
    "NOT", "AND", "OR",     //not and or

    //Constant
    "CONSTANT_INT", "CONSTANT_DEC", "CONSTANT_STR",

    //End
    "CODE_EOF"
};

static unordered_map<string,TokenType>Keyword_map
{
    {"int",INT}, {"dec",DEC}, {"str",STR},
    {"bool",BOOL}, {"true", TRUE}, {"false",FALSE},
    {"if",IF}, {"else",ELSE}, {"while",WHILE},
    {"input",INPUT}, {"output",OUTPUT}, 
    {"ret",RET}, {"exit",EXIT}, 
    {"permission",PERMISSION},
    {"not",NOT}, {"and",AND}, {"or",OR}
};

class Token{
public:
    bool is_valid;
    TokenType token_type;
    string lexeme;
    int line;

    Token():is_valid(false){}
    Token(TokenType token_type,string lexeme,int line):
        is_valid(true),token_type(token_type),lexeme(lexeme),line(line){}
};