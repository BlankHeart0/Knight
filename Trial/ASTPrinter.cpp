#include "AbstractSyntaxTree.h"

void PrintTab(int n)
{
    cout<<endl;
    for(int i=0;i<=n+2;i++)cout<<'\t';
}

void AST::Print()
{
    translation_unit->Print(0);

    cout<<endl;
}



// Begin
void TranslationUnitAST::Print(int depth)
{
    cout<<"Translation_Unit";
    
    for(ASTNode* ast_ptr:function_definitions)
        ast_ptr->Print(depth+1);
}



// Definition
void FunctionDefinitionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Function_Definition";
    if(ret_type.is_valid)
        cout<<" return_type:"<<ret_type.lexeme;
    cout<<" function_name:"<<function_name.lexeme;
    compound_statement->Print(depth+1);
}

void LocalVariableDefinitionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"LocalVariable_Definition";

    cout<<" type:"<<data_type.lexeme;
    cout<<" variable_name:"<<variable_name.lexeme;
    if(expression)expression->Print(depth+1);
}



// Statement
void StatementAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Statement";
    
    X_statement->Print(depth+1);
}

void CompoundStatementAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Compound_Statement";
    
    for(ASTNode* ast_ptr:statements)
        ast_ptr->Print(depth+1);
}

void PrintStatementAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Print_Statement";

    expression->Print(depth);
}

void ExpressionStatementAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Expression_Statement";
    
    if(expression)expression->Print(depth+1);
    else cout<<" __BLANK__";
}



// Expression
void ExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Expression";

    assignment_expression->Print(depth+1);
}

void AssignmentExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Assignment_Expression";

    if(variable.is_valid)cout<<" variable:"<<variable.lexeme;
    logicOr_expression->Print(depth+1);    
}



void LogicOrExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"LogicOr_Expression";

    logicAnd_expression->Print(depth+1);
    for(int i=0;i<infix_operators.size();i++)
    {
        PrintTab(depth+1);
        cout<<" infix_operator:"<<infix_operators[i].lexeme;
        logicAnd_expressions[i]->Print(depth+1);
    }
}

void LogicAndExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"LogicAnd_Expression";

    equality_expression->Print(depth+1);
    for(int i=0;i<infix_operators.size();i++)
    {
        PrintTab(depth+1);
        cout<<" infix_operator:"<<infix_operators[i].lexeme;
        equality_expressions[i]->Print(depth+1);
    }
}



void EqualityExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Equality_Expression";

    relational_expression->Print(depth+1);
    for(int i=0;i<infix_operators.size();i++)
    {
        PrintTab(depth+1);
        cout<<" infix_operator:"<<infix_operators[i].lexeme;
        relational_expressions[i]->Print(depth+1);
    }
}

void RelationalExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Relational_Expression";

    plusminus_expression->Print(depth+1);
    for(int i=0;i<infix_operators.size();i++)
    {
        PrintTab(depth+1);
        cout<<" infix_operator:"<<infix_operators[i].lexeme;
        plusminus_expressions[i]->Print(depth+1);
    }
}



void PlusMinusExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"PlusMinus_Expression";

    muldiv_expression->Print(depth+1);
    for(int i=0;i<infix_operators.size();i++)
    {
        PrintTab(depth+1);
        cout<<" infix_operator:"<<infix_operators[i].lexeme;
        muldiv_expressions[i]->Print(depth+1);
    }
}

void MulDivExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"MulDiv_Expression";

    unary_expression->Print(depth+1);
    for(int i=0;i<infix_operators.size();i++)
    {
        PrintTab(depth+1);
        cout<<" infix_operator:"<<infix_operators[i].lexeme;
        unary_expressions[i]->Print(depth+1);
    }
}



void UnaryExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Unary_Expression";

    if(prefix_operator.is_valid)
        cout<<" prefix_operator:"<<prefix_operator.lexeme;
    primary_expression->Print(depth+1);
}

void PrimaryExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Primary_Expression";

    if(expression)expression->Print(depth+1);
    else if(constant.is_valid)
    {
        switch(constant.token_type)
        {
            case CONSTANT_INT:    cout<<" constant_int:"; break;
            case CONSTANT_DEC:    cout<<" constant_dec:"; break;
            case CONSTANT_STR:    cout<<" constant_str:"; break;
            case TRUE:case FALSE: cout<<" constant_bool:";break;
        }
        cout<<constant.lexeme;
    }
    else if(variable.is_valid)
    {
        cout<<" variable:"<<variable.lexeme;
    }
}
