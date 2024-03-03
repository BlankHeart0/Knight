#include "Parser.h"

void Parser::Parse()
{
    abstract_syntax_tree.translation_unit=Parse_Translation_Unit();
}



//Begin
ASTNode* Parser::Parse_Translation_Unit()
{
    diagnostor.WhoAmI("Parse_Translation_Unit");

    TranslationUnitAST* node=new TranslationUnitAST();

    while(!IsAtEnd())
    {
        AddChildToVector(node->function_definitions,
                        Parse_Function_Definition());
    }

    return (ASTNode*)node;
}



// Definition
ASTNode* Parser::Parse_Function_Definition()
{
    diagnostor.WhoAmI("Parse_Function_Definition");

    FunctionDefinitionAST* node=new FunctionDefinitionAST();
    
    if(Match(IDENTIFIER))
    {
        node->function_name=PreviousToken().lexeme;

        if(!Match(LEFT_PAREN))PARSE_ERROR("Left paren '(' loss");
        if(!Match(RIGHT_PAREN))PARSE_ERROR("Right paren ')' loss");

        node->compound_statement=Parse_Compound_Statement();
    }
    else PARSE_ERROR("Function identifier loss");

    return (ASTNode*)node;
}



// Statement
ASTNode* Parser::Parse_Statement()
{
    diagnostor.WhoAmI("Parse_Statement");

    StatementAST* node=new StatementAST();

    if(Peek(LEFT_BRACE)) 
        node->X_statement=Parse_Compound_Statement();
    else if(Peek(PRINT))
        node->X_statement=Parse_Print_Statement();
    else
        node->X_statement=Parse_Expression_Statement();

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Print_Statement()
{
    diagnostor.WhoAmI("Parse_Print_Statement");

    PrintStatementAST* node=new PrintStatementAST();

    if(Match(PRINT))
    {
        node->expression=Parse_Expression();
        MatchSemicolon();
    }
    else PARSE_ERROR("Keyword 'print' loss");

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Compound_Statement()
{
    diagnostor.WhoAmI("Parse_Compound_Statement");

    CompoundStatementAST* node=new CompoundStatementAST();

    if (Match(LEFT_BRACE))
	{
        while(!Match(RIGHT_BRACE))
        {
            AddChildToVector(node->statements,
                            Parse_Statement());
        }
        if(PreviousToken().token_type!=RIGHT_BRACE)
            PARSE_ERROR("Right barce '}' loss");
    }
    else PARSE_ERROR("Left barce '{' loss");

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Expression_Statement()
{
    diagnostor.WhoAmI("Parse_Expression_Statement");

    ExpressionStatementAST* node=new ExpressionStatementAST();

    if(!Peek(SEMICOLON)) node->expression=Parse_Expression();
    
    MatchSemicolon();

    return (ASTNode*)node;
}



// Expression
ASTNode* Parser::Parse_Expression()
{
    diagnostor.WhoAmI("Parse_Expression");

    ExpressionAST* node=new ExpressionAST();

    node->muldiv_expression=Parse_MulDiv_Expression();
    while(Match(PLUS)||Match(MINUS))
    {
        if(PreviousToken().token_type==PLUS)
            node->infix_operators.push_back('+');
        else if(PreviousToken().token_type==MINUS)
            node->infix_operators.push_back('-');
        
        AddChildToVector(node->muldiv_expressions,
                        Parse_MulDiv_Expression());
    }

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_MulDiv_Expression()
{
    diagnostor.WhoAmI("Parse_MulDiv_Expression");

    MulDivExpressionAST* node=new MulDivExpressionAST();

    node->unary_expression=Parse_Unary_Expression();
    while(Match(STAR)||Match(SLASH)||Match(PERCENT))
    {
        switch(PreviousToken().token_type)
        {
            case STAR:    node->infix_operators.push_back('*');break;
            case SLASH:   node->infix_operators.push_back('/');break;
            case PERCENT: node->infix_operators.push_back('%');break;
        }

        AddChildToVector(node->unary_expressions,
                        Parse_Unary_Expression());
    }

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Unary_Expression()
{
    diagnostor.WhoAmI("Parse_Unary_Expression");

    UnaryExpressionAST* node=new UnaryExpressionAST();

    if(Match(MINUS))
    {
        node->prefix_operator="-";
    }

    node->primary_expression=Parse_Primary_Expression();

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Primary_Expression()
{
    diagnostor.WhoAmI("Parse_Primary_Expression");

    PrimaryExpressionAST* node=new PrimaryExpressionAST();

    if(Match(CONSTANT_INT)||Match(CONSTANT_DEC)||Match(CONSTANT_STR))
    {
        node->literal=PreviousToken().literal;
    }
    else if(Match(LEFT_PAREN))
    {
        node->expression=Parse_Expression();
        if(!Match(RIGHT_PAREN))PARSE_ERROR("Right paren ')' loss");
    }

    else PARSE_ERROR("Primary character loss");

    return (ASTNode*)node;
}



void Parser::AddChildToVector(vector<ASTNode*>& vec, ASTNode* child )
{
    vec.push_back(child);
}

bool Parser::IsAtEnd()
{
    return tokens[current].token_type==CODE_EOF;
}

bool Parser::Match(TokenType expected)
{
    line=tokens[current].line;

    if(!IsAtEnd()&&expected==tokens[current].token_type)
    {
        current++;
        return true;
    }
    return false;
}

void Parser::MatchSemicolon()
{
    if(!Match(SEMICOLON))PARSE_ERROR("Semicolon ';' loss");
}

bool Parser::Peek(TokenType expected)
{
    return Peek(expected,1);
}

bool Parser::Peek(TokenType expected,int n)
{
    if(current+n-1<tokens.size()-1&&expected==tokens[current+n-1].token_type)return true;
    return false;
}

Token Parser::PreviousToken()
{
    return tokens[current-1];
}