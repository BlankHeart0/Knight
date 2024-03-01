#pragma once

#include "SystemHead.h"

enum TokenType
{
    //Keyword
    INT, DEC, STR,
    IF, ELSE, WHILE,
    RET,

    //Identifier
    IDENTIFIER,

    //Separator
    SEMICOLON, COMMA, COLON, // ; , :
    LEFT_PAREN, RIGHT_PAREN, // ( )
    LEFT_BRACE, RIGHT_BRACE, // { }

    //Operator
    PLUS, MINUS, STAR, SLASH, MOD, // + - * / %
    
    ASSIGN, // =

    EQUAL, NOT_EQUAL,       // ?= !=
    LESS, LESS_EQUAL,       // <  <=
    GREATER, GREATER_EQUAL, // >  >=

    //Constant
    CONSTANT_INT, CONSTANT_DEC, CONSTANT_STR,

    //End
    CODE_EOF
};