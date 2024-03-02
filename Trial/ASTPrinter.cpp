#include "AbstractSyntaxTree.h"

void PrintTab(int n)
{
    cout<<endl;
    for(int i=0;i<=n+1;i++)cout<<'\t';
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
    
    cout<<" function_name:"<<function_name;
    compound_statement->Print(depth+1);
}



// Statement
void StatementAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Statement";
    
    compound_or_expression_statement->Print(depth+1);
}

void CompoundStatementAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Compound_Statement";
    
    for(ASTNode* ast_ptr:statements)
        ast_ptr->Print(depth+1);
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
    
    muldiv_expression->Print(depth+1);
    for(int i=0;i<infix_operators.size();i++)
    {
        PrintTab(depth+1);
        cout<<" infix_operator:"<<infix_operators[i];
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
        cout<<" infix_operator:"<<infix_operators[i];
        unary_expressions[i]->Print(depth+1);
    }
}

void UnaryExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Unary_Expression";

    if(prefix_operator!="")
        cout<<" prefix_operator:"<<prefix_operator;
    primary_expression->Print(depth+1);
}

void PrimaryExpressionAST::Print(int depth)
{
    PrintTab(depth);
    cout<<"Primary_Expression";

    if(expression)expression->Print(depth+1);
    else 
    {
        switch(literal.literal_type)
        {
            case L_INT:
                cout<<" constant_int:"<<literal.literal_int;
                break;
            case L_DEC:
                cout<<" constant_dec:"<<literal.literal_dec;
                break;
            case L_STR:
                cout<<" constant_str:"<<literal.literal_str;
                break;
        }
    }
}