#include "Parser.h"

AST abstract_syntax_tree;

void Parser::Parse()
{
    abstract_syntax_tree.translation_unit=Parse_Translation_Unit();
}



//Begin
unique_ptr<ASTNode> Parser::Parse_Translation_Unit()
{
    diagnostor.WhoAmI("Parse_Translation_Unit");

    unique_ptr<TranslationUnitAST> node=make_unique<TranslationUnitAST>();

    while(!IsAtEnd())
    {
        if(Peek(PERMISSION))
            AddChildToVector(node->permission_definitions,
                            Parse_Permission_Definition());
        else if(Peek(INVOKE))
            AddChildToVector(node->invoke_definitions,
                            Parse_Invoke_Definition());
        else
            AddChildToVector(node->function_definitions,
                            Parse_Function_Definition());
    }

    return move(node);
}



// Definition
unique_ptr<ASTNode> Parser::Parse_Permission_Definition()
{
    diagnostor.WhoAmI("Parse_Permission_Definition");

    unique_ptr<PermissionDefinitionAST> node=make_unique<PermissionDefinitionAST>();

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

    return move(node);
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

unique_ptr<ASTNode> Parser::Parse_Invoke_Definition()
{
    diagnostor.WhoAmI("Parse_Invoke_Definition");

    unique_ptr<InvokeDefinitionAST> node=make_unique<InvokeDefinitionAST>();

    if(Match(INVOKE))
    {
        if(Match(IDENTIFIER))
        {
            node->app_name=PreviousToken();

            if(Match(COLON))
            {
                if(!Peek(IDENTIFIER))
                    node->ret_type=Parse_Type();

                if(Match(IDENTIFIER))
                {
                    node->function_name=PreviousToken();

                    if(Match(LEFT_PAREN))
                    {
                        if(!Peek(RIGHT_PAREN))
                            node->parameter_list=Parse_Parameter_List();

                        if(!Match(RIGHT_PAREN))
                            PARSE_ERROR("Right paren ')' loss"); 
                    }
                    else PARSE_ERROR("Left paren '(' loss");
                }
                else PARSE_ERROR("Function identifier loss");
            }
            else PARSE_ERROR("Colon ':' loss");
        }
        else PARSE_ERROR("App identifier loss");
    }
    else PARSE_ERROR("Keyword 'invoke' loss");
    
    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Function_Definition()
{
    diagnostor.WhoAmI("Parse_Function_Definition");

    unique_ptr<FunctionDefinitionAST> node=make_unique<FunctionDefinitionAST>();
    
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

    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Parameter()
{
    diagnostor.WhoAmI("Parse_Parameter");

    unique_ptr<ParameterAST> node=make_unique<ParameterAST>();

    node->type=Parse_Type();

    if(Match(IDENTIFIER))
    {
        node->parameter_name=PreviousToken();
    }
    else PARSE_ERROR("Parameter identifier loss");

    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Parameter_List()
{
    diagnostor.WhoAmI("Parse_Parameter_List");

    unique_ptr<ParameterListAST> node=make_unique<ParameterListAST>();

    AddChildToVector(node->parameters,Parse_Parameter());

    while(Match(COMMA))
        AddChildToVector(node->parameters,Parse_Parameter());
    
    return move(node);
}



unique_ptr<ASTNode> Parser::Parse_LocalVariable_Definition()
{
    diagnostor.WhoAmI("Parse_LocalVariable_Definition");

    unique_ptr<LocalVariableDefinitionAST> node=make_unique<LocalVariableDefinitionAST>();

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

    return move(node);
}



// Statement
unique_ptr<ASTNode> Parser::Parse_Statement()
{
    diagnostor.WhoAmI("Parse_Statement");

    unique_ptr<StatementAST> node=make_unique<StatementAST>();

    if(Peek(LEFT_BRACE)) 
        node->X_statement=Parse_Compound_Statement();
    else if(Peek(IF))
        node->X_statement=Parse_If_Statement();
    else if(Peek(WHILE))
        node->X_statement=Parse_While_Statement();
    else if(Peek(RET))
        node->X_statement=Parse_Return_Statement();
    else if(Peek(EXIT))
        node->X_statement=Parse_Exit_Statement();
    else if(Peek(INPUT))
        node->X_statement=Parse_Input_Statement();
    else if(Peek(OUTPUT))
        node->X_statement=Parse_Output_Statement();
    else if(Peek(IDENTIFIER)&&Peek(ASSIGN,2))
        node->X_statement=Parse_Assignment_Statement();
    else if(Peek(INT)||Peek(DEC)||Peek(STR)||Peek(BOOL))
        node->X_statement=Parse_LocalVariable_Definition();
    else
        node->X_statement=Parse_Expression_Statement();

    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Compound_Statement()
{
    diagnostor.WhoAmI("Parse_Compound_Statement");

    unique_ptr<CompoundStatementAST> node=make_unique<CompoundStatementAST>();

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

    return move(node);
}



unique_ptr<ASTNode> Parser::Parse_If_Statement()
{
    diagnostor.WhoAmI("Parse_If_Statement");

    unique_ptr<IfStatementAST> node=make_unique<IfStatementAST>();

    if(Match(IF))
    {
        node->If=PreviousToken();
        
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

    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_While_Statement()
{
    diagnostor.WhoAmI("Parse_While_Statement");

    unique_ptr<WhileStatementAST> node=make_unique<WhileStatementAST>();

    if(Match(WHILE))
    {
        node->While=PreviousToken();

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

    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Return_Statement()
{
    diagnostor.WhoAmI("Parse_Return_Statement");

    unique_ptr<ReturnStatementAST> node=make_unique<ReturnStatementAST>();

    if(Match(RET))
    {
        node->ret=PreviousToken();

        if(!Peek(SEMICOLON)) node->expression=Parse_Expression();
        
        MatchSemicolon();
    }
    else PARSE_ERROR("Keyword 'ret' loss");
    
    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Exit_Statement()
{
    diagnostor.WhoAmI("Parse_Exit_Statement");

    unique_ptr<ExitStatementAST> node=make_unique<ExitStatementAST>();

    if(Match(EXIT))
    {
        node->exit=PreviousToken();

        MatchSemicolon();
    }
    else PARSE_ERROR("Keyword 'exit' loss");
    
    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Input_Statement()
{
    diagnostor.WhoAmI("Parse_Input_Statement");

    unique_ptr<InputStatementAST> node=make_unique<InputStatementAST>();

    if(Match(INPUT))
    {
        if(Match(IDENTIFIER))
        {
            node->variables.push_back(PreviousToken());
            while(Match(COMMA))
            {
                if(Match(IDENTIFIER))
                    node->variables.push_back(PreviousToken());
                else PARSE_ERROR("Input identifier loss");
            }

            MatchSemicolon();
        }
        else PARSE_ERROR("Input identifier loss");
    }
    else PARSE_ERROR("Keyword 'input' loss");
    
    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Output_Statement()
{
    diagnostor.WhoAmI("Parse_Output_Statement");

    unique_ptr<OutputStatementAST> node=make_unique<OutputStatementAST>();

    if(Match(OUTPUT))
    {
        node->output=PreviousToken();

        AddChildToVector(node->expressions,Parse_Expression());
        while(Match(COMMA))
        {
            AddChildToVector(node->expressions,Parse_Expression());
        }
        
        MatchSemicolon();
    }
    else PARSE_ERROR("Keyword 'output' loss");

    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Assignment_Statement()
{
    diagnostor.WhoAmI("Parse_Assignment_Statement");

    unique_ptr<AssignmentStatementAST> node=make_unique<AssignmentStatementAST>();

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

    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Expression_Statement()
{
    diagnostor.WhoAmI("Parse_Expression_Statement");

    unique_ptr<ExpressionStatementAST> node=make_unique<ExpressionStatementAST>();

    node->expression=Parse_Expression();
    MatchSemicolon();

    return move(node);
}



// Expression
unique_ptr<ASTNode> Parser::Parse_Expression()
{
    diagnostor.WhoAmI("Parse_Expression");
    
    unique_ptr<ExpressionAST> node=make_unique<ExpressionAST>();

    node->logicOr_expression=Parse_LogicOr_Expression();

    return move(node);
}    



unique_ptr<ASTNode> Parser::Parse_LogicOr_Expression()
{
    diagnostor.WhoAmI("Parse_LogicOr_Expression");

    unique_ptr<LogicOrExpressionAST> node=make_unique<LogicOrExpressionAST>();

    node->logicAnd_expression=Parse_LogicAnd_Expression();
    while(Match(OR))
    {
        node->infix_operators.push_back(PreviousToken());
        AddChildToVector(node->logicAnd_expressions,
                        Parse_LogicAnd_Expression());
    }

    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_LogicAnd_Expression()
{
    diagnostor.WhoAmI("Parse_LogicAnd_Expression");

    unique_ptr<LogicAndExpressionAST> node=make_unique<LogicAndExpressionAST>();

    node->equality_expression=Parse_Equality_Expression();
    while(Match(AND))
    {
        node->infix_operators.push_back(PreviousToken());
        AddChildToVector(node->equality_expressions,
                        Parse_Equality_Expression());
    }

    return move(node);
}



unique_ptr<ASTNode> Parser::Parse_Equality_Expression()
{
    diagnostor.WhoAmI("Parse_Equality_Expression");

    unique_ptr<EqualityExpressionAST> node=make_unique<EqualityExpressionAST>();

    node->relational_expression=Parse_Relational_Expression();
    while(Match(EQUAL)||Match(NOT_EQUAL))
    {
        node->infix_operators.push_back(PreviousToken());   
        AddChildToVector(node->relational_expressions,
                        Parse_Relational_Expression());
    }
    
    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Relational_Expression()
{
    diagnostor.WhoAmI("Parse_Relational_Expression");

    unique_ptr<RelationalExpressionAST> node=make_unique<RelationalExpressionAST>();

    node->plusminus_expression=Parse_PlusMinus_Expression();
    while(Match(LESS)||Match(LESS_EQUAL)||Match(GREATER)||Match(GREATER_EQUAL))
    {
        node->infix_operators.push_back(PreviousToken());   
        AddChildToVector(node->plusminus_expressions,
                        Parse_PlusMinus_Expression());
    }

    return move(node);
}



unique_ptr<ASTNode> Parser::Parse_PlusMinus_Expression()
{
    diagnostor.WhoAmI("Parse_PlusMinus_Expression");

    unique_ptr<PlusMinusExpressionAST> node=make_unique<PlusMinusExpressionAST>();

    node->muldiv_expression=Parse_MulDiv_Expression();
    while(Match(PLUS)||Match(MINUS))
    {
        node->infix_operators.push_back(PreviousToken());   
        AddChildToVector(node->muldiv_expressions,
                        Parse_MulDiv_Expression());
    }

    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_MulDiv_Expression()
{
    diagnostor.WhoAmI("Parse_MulDiv_Expression");

    unique_ptr<MulDivExpressionAST> node=make_unique<MulDivExpressionAST>();

    node->unary_expression=Parse_Unary_Expression();
    while(Match(STAR)||Match(SLASH)||Match(PERCENT))
    {
        node->infix_operators.push_back(PreviousToken());
        AddChildToVector(node->unary_expressions,
                        Parse_Unary_Expression());
    }

    return move(node);
}



unique_ptr<ASTNode> Parser::Parse_Unary_Expression()
{
    diagnostor.WhoAmI("Parse_Unary_Expression");

    unique_ptr<UnaryExpressionAST> node=make_unique<UnaryExpressionAST>();

    if(Match(MINUS)||Match(NOT))
    {
        node->prefix_operator=PreviousToken();
    }

    if(Peek(IDENTIFIER)&&(Peek(LEFT_PAREN,2)||Peek(DOT,2)))
        node->functioncall_expression=Parse_FunctionCall_Expression();
    else
        node->primary_expression=Parse_Primary_Expression();

    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_Primary_Expression()
{
    diagnostor.WhoAmI("Parse_Primary_Expression");

    unique_ptr<PrimaryExpressionAST> node=make_unique<PrimaryExpressionAST>();
    
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

    return move(node);
}

unique_ptr<ASTNode> Parser::Parse_FunctionCall_Expression()
{
    diagnostor.WhoAmI("Parse_FunctionCall_Expression");

    unique_ptr<FunctionCallExpressionAST> node=make_unique<FunctionCallExpressionAST>();

    if(Peek(DOT,2))
    {
        if(Match(IDENTIFIER))
        {
            node->app=PreviousToken();
            
            if(!Match(DOT))
                PARSE_ERROR("Dot '.' loss");
        }
        else PARSE_ERROR("App identifier loss");
    }

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

    return move(node);
}



void Parser::AddChildToVector(vector<unique_ptr<ASTNode>>& vec, unique_ptr<ASTNode> child )
{
    vec.push_back(move(child));
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
