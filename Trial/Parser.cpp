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
        if(Peek(PERMISSION))
            AddChildToVector(node->permission_definitions,
                            Parse_Permission_Definition());
        else
            AddChildToVector(node->function_definitions,
                            Parse_Function_Definition());
    }

    return (ASTNode*)node;
}



// Definition
ASTNode* Parser::Parse_Permission_Definition()
{
    diagnostor.WhoAmI("Parse_Permission_Definition");

    PermissionDefinitionAST* node=new PermissionDefinitionAST();

    if(Match(PERMISSION))
    {
        if(Match(IDENTIFIER))
        {
            node->permissions.push_back(PreviousToken());
            while(Match(COMMA))
            {
                if(Match(IDENTIFIER))
                    node->permissions.push_back(PreviousToken());
                else PARSE_ERROR("Permission identifier loss");
            }
        }
        else PARSE_ERROR("Permission identifier loss");
    }
    else PARSE_ERROR("Keyword 'permission' loss");

    return (ASTNode*)node;
}



TypeAsToken Parser::Parse_Type()
{
    diagnostor.WhoAmI("Parse_Type");

    Token data_token;
    vector<Token> permissions_token;

    if(Match(INT)||Match(DEC)||Match(STR)||Match(BOOL))
    {
        data_token=PreviousToken();
    }
    else PARSE_ERROR("Data type loss");

    if(Match(LESS))
    {
        if(Match(IDENTIFIER))
        {
            permissions_token.push_back(PreviousToken());
            while(Match(COMMA))
            {
                if(Match(IDENTIFIER))
                    permissions_token.push_back(PreviousToken());
                else PARSE_ERROR("Permission identifier loss");
            }
            if(!Match(GREATER))PARSE_ERROR("Greater '>' loss");
        }
        else PARSE_ERROR("Permission identifier loss");
    }

    return TypeAsToken(data_token,permissions_token);
}

ASTNode* Parser::Parse_Function_Definition()
{
    diagnostor.WhoAmI("Parse_Function_Definition");

    FunctionDefinitionAST* node=new FunctionDefinitionAST();
    
    if(!Peek(IDENTIFIER))
        node->ret_type=Parse_Type();

    if(Match(IDENTIFIER))
    {
        node->function_name=PreviousToken();

        if(Match(LEFT_PAREN))
        {
            if(!Peek(RIGHT_PAREN))
                node->parameter_list=Parse_Parameter_List();

            if(Match(RIGHT_PAREN))
            {
                if(Match(LEFT_BRACE))
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
            }
            else PARSE_ERROR("Right paren ')' loss");
        }
        else PARSE_ERROR("Left paren '(' loss");
    }
    else PARSE_ERROR("Function identifier loss");

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Parameter()
{
    diagnostor.WhoAmI("Parse_Parameter");

    ParameterAST* node=new ParameterAST();

    node->type=Parse_Type();

    if(Match(IDENTIFIER))
    {
        node->parameter_name=PreviousToken();
    }
    else PARSE_ERROR("Parameter identifier loss");

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Parameter_List()
{
    diagnostor.WhoAmI("Parse_Parameter_List");

    ParameterListAST* node=new ParameterListAST();

    AddChildToVector(node->parameters,Parse_Parameter());

    while(Match(COMMA))
        AddChildToVector(node->parameters,Parse_Parameter());
    
    return (ASTNode*)node;
}



ASTNode* Parser::Parse_LocalVariable_Definition()
{
    diagnostor.WhoAmI("Parse_LocalVariable_Definition");

    LocalVariableDefinitionAST* node=new LocalVariableDefinitionAST();

    node->type=Parse_Type();

    if(Match(IDENTIFIER))
    {
        node->variable_name=PreviousToken();
        //Initialize
        if(Match(COLON))
        {
            node->expression=Parse_Expression();
        }
        MatchSemicolon();
    }
    else PARSE_ERROR("Variable identifier loss");

    return (ASTNode*)node;
}



// Statement
ASTNode* Parser::Parse_Statement()
{
    diagnostor.WhoAmI("Parse_Statement");

    StatementAST* node=new StatementAST();

    if(Peek(LEFT_BRACE)) 
        node->X_statement=Parse_Compound_Statement();
    else if(Peek(IF))
        node->X_statement=Parse_If_Statement();
    else if(Peek(WHILE))
        node->X_statement=Parse_While_Statement();
    else if(Peek(RET))
        node->X_statement=Parse_Return_Statement();
    else if(Peek(PRINT))
        node->X_statement=Parse_Print_Statement();
    else if(Peek(IDENTIFIER))
        node->X_statement=Parse_Assignment_Statement();
    else if(Peek(INT)||Peek(DEC)||Peek(STR)||Peek(BOOL))
        node->X_statement=Parse_LocalVariable_Definition();
    else
        node->X_statement=Parse_Expression_Statement();

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



ASTNode* Parser::Parse_If_Statement()
{
    diagnostor.WhoAmI("Parse_If_Statement");

    IfStatementAST* node=new IfStatementAST();

    if(Match(IF))
    {
        if(Match(LEFT_PAREN))
        {
            node->expression=Parse_Expression();
            if(Match(RIGHT_PAREN))
            {
                node->true_statement=Parse_Statement();
                if(Match(ELSE))
                {
                    node->false_statement=Parse_Statement();
                }
            }
            else PARSE_ERROR("Right paren ')' loss");
        }
        else PARSE_ERROR("Left paren '(' loss");
    }
    else PARSE_ERROR("Keyword 'if' loss");

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_While_Statement()
{
    diagnostor.WhoAmI("Parse_While_Statement");

    WhileStatementAST* node=new WhileStatementAST();

    if(Match(WHILE))
    {
        if(Match(LEFT_PAREN))
        {
            node->expression=Parse_Expression();
            if(Match(RIGHT_PAREN))
            {
                node->statement=Parse_Statement();
            }
            else PARSE_ERROR("Right paren ')' loss");
        }
        else PARSE_ERROR("Left paren '(' loss");
    }
    else PARSE_ERROR("Keyword 'while' loss");

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Return_Statement()
{
    diagnostor.WhoAmI("Parse_Return_Statement");

    ReturnStatementAST* node=new ReturnStatementAST();

    if(Match(RET))
    {
        node->ret=PreviousToken();

        if(!Peek(SEMICOLON)) node->expression=Parse_Expression();
        
        MatchSemicolon();
    }
    else PARSE_ERROR("Keyword 'ret' loss");
    
    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Print_Statement()
{
    diagnostor.WhoAmI("Parse_Print_Statement");

    PrintStatementAST* node=new PrintStatementAST();

    if(Match(PRINT))
    {
        AddChildToVector(node->expressions,Parse_Expression());
        while(Match(COMMA))
        {
            AddChildToVector(node->expressions,Parse_Expression());
        }
        MatchSemicolon();
    }
    else PARSE_ERROR("Keyword 'print' loss");

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Assignment_Statement()
{
    diagnostor.WhoAmI("Parse_Assignment_Statement");

    AssignmentStatementAST* node=new AssignmentStatementAST();

    if(Match(IDENTIFIER))
    {
        node->variable=PreviousToken();
        if(Match(ASSIGN))
        {
            node->expression=Parse_Expression();
            MatchSemicolon();
        }
        else PARSE_ERROR("Assign '=' loss");
    }
    else PARSE_ERROR("Variable identifier loss");

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Expression_Statement()
{
    diagnostor.WhoAmI("Parse_Expression_Statement");

    ExpressionStatementAST* node=new ExpressionStatementAST();

    node->expression=Parse_Expression();
    MatchSemicolon();

    return (ASTNode*)node;
}



// Expression
ASTNode* Parser::Parse_Expression()
{
    diagnostor.WhoAmI("Parse_Expression");
    
    ExpressionAST* node=new ExpressionAST();

    node->logicOr_expression=Parse_LogicOr_Expression();

    return (ASTNode*)node;
}    



ASTNode* Parser::Parse_LogicOr_Expression()
{
    diagnostor.WhoAmI("Parse_LogicOr_Expression");

    LogicOrExpressionAST* node=new LogicOrExpressionAST();

    node->logicAnd_expression=Parse_LogicAnd_Expression();
    while(Match(OR))
    {
        node->infix_operators.push_back(PreviousToken());
        AddChildToVector(node->logicAnd_expressions,
                        Parse_LogicAnd_Expression());
    }

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_LogicAnd_Expression()
{
    diagnostor.WhoAmI("Parse_LogicAnd_Expression");

    LogicAndExpressionAST* node=new LogicAndExpressionAST();

    node->equality_expression=Parse_Equality_Expression();
    while(Match(AND))
    {
        node->infix_operators.push_back(PreviousToken());
        AddChildToVector(node->equality_expressions,
                        Parse_Equality_Expression());
    }

    return (ASTNode*)node;
}



ASTNode* Parser::Parse_Equality_Expression()
{
    diagnostor.WhoAmI("Parse_Equality_Expression");

    EqualityExpressionAST* node=new EqualityExpressionAST();

    node->relational_expression=Parse_Relational_Expression();
    while(Match(EQUAL)||Match(NOT_EQUAL))
    {
        node->infix_operators.push_back(PreviousToken());   
        AddChildToVector(node->relational_expressions,
                        Parse_Relational_Expression());
    }
    
    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Relational_Expression()
{
    diagnostor.WhoAmI("Parse_Relational_Expression");

    RelationalExpressionAST* node=new RelationalExpressionAST();

    node->plusminus_expression=Parse_PlusMinus_Expression();
    while(Match(LESS)||Match(LESS_EQUAL)||Match(GREATER)||Match(GREATER_EQUAL))
    {
        node->infix_operators.push_back(PreviousToken());   
        AddChildToVector(node->plusminus_expressions,
                        Parse_PlusMinus_Expression());
    }

    return (ASTNode*)node;
}



ASTNode* Parser::Parse_PlusMinus_Expression()
{
    diagnostor.WhoAmI("Parse_PlusMinus_Expression");

    PlusMinusExpressionAST* node=new PlusMinusExpressionAST();

    node->muldiv_expression=Parse_MulDiv_Expression();
    while(Match(PLUS)||Match(MINUS))
    {
        node->infix_operators.push_back(PreviousToken());   
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
        node->infix_operators.push_back(PreviousToken());
        AddChildToVector(node->unary_expressions,
                        Parse_Unary_Expression());
    }

    return (ASTNode*)node;
}



ASTNode* Parser::Parse_Unary_Expression()
{
    diagnostor.WhoAmI("Parse_Unary_Expression");

    UnaryExpressionAST* node=new UnaryExpressionAST();

    if(Match(MINUS)||Match(NOT))
    {
        node->prefix_operator=PreviousToken();
    }

    if(Peek(IDENTIFIER)&&Peek(LEFT_PAREN,2))
        node->functioncall_expression=Parse_FunctionCall_Expression();
    else
        node->primary_expression=Parse_Primary_Expression();

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_Primary_Expression()
{
    diagnostor.WhoAmI("Parse_Primary_Expression");

    PrimaryExpressionAST* node=new PrimaryExpressionAST();
    
    if(Match(LEFT_PAREN))
    {
        node->expression=Parse_Expression();
        if(!Match(RIGHT_PAREN))PARSE_ERROR("Right paren ')' loss");
    }
    else if(Match(CONSTANT_INT)||Match(CONSTANT_DEC)||Match(CONSTANT_STR)
          ||Match(TRUE)||Match(FALSE))
    {
        node->constant=PreviousToken();
    }
    else if(Match(IDENTIFIER))
    {
        node->variable=PreviousToken();
    }
    else PARSE_ERROR("Primary character loss");

    return (ASTNode*)node;
}

ASTNode* Parser::Parse_FunctionCall_Expression()
{
    diagnostor.WhoAmI("Parse_FunctionCall_Expression");

    FunctionCallExpressionAST* node=new FunctionCallExpressionAST();

    if(Match(IDENTIFIER))
    {
        node->function=PreviousToken();
        if(Match(LEFT_PAREN))
        {
            if(!Peek(RIGHT_PAREN))
            {
                AddChildToVector(node->expressions,
                                Parse_Expression());
                
                while(Match(COMMA))
                {
                    AddChildToVector(node->expressions,
                                    Parse_Expression());
                }
            }

            if(!Match(RIGHT_PAREN))PARSE_ERROR("Right paren ')' loss");
        }
        else PARSE_ERROR("Left paren '(' loss");
    }
    else PARSE_ERROR("Function identifier loss");

    return (ASTNode*)node;
}



void Parser::AddChildToVector(vector<ASTNode*>& vec, ASTNode* child )
{
    vec.push_back(child);
}

Token Parser::PreviousToken()
{
    return tokens[current-1];
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
