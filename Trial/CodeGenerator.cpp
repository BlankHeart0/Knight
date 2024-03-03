#include "CodeGenerator.h"

GeneralRegister CodeGenerator::general_register;

void CodeGenerator::CodeGen()
{
    abstract_syntax_tree.CodeGen();
}

void AST::CodeGen()
{
    cout<<"--- --- CodeGen Begin --- ---"<<endl;
    file_manager.Write("Hello Knight!\n\n");
    translation_unit->CodeGen();
    cout<<"--- --- CodeGen Done --- ---"<<endl;
}



// Begin
int TranslationUnitAST::CodeGen()
{
    for(ASTNode* ast_ptr:function_definitions)
        ast_ptr->CodeGen();
    
    return NOTHING;
}



// Definition
int FunctionDefinitionAST::CodeGen()
{
    file_manager.Write(function_name+":\n");
    compound_statement->CodeGen();

    return NOTHING;
}



// Statement
int StatementAST::CodeGen()
{
    X_statement->CodeGen();

    return NOTHING;
}

int CompoundStatementAST::CodeGen()
{
    for(ASTNode* ast_ptr:statements)
        ast_ptr->CodeGen();

    return NOTHING;
}

int PrintStatementAST::CodeGen()
{
    int expression_ri=expression->CodeGen();
    CodeGenerator::Print(expression_ri);

    return NOTHING;
}

int ExpressionStatementAST::CodeGen()
{
    if(expression)expression->CodeGen();

    return NOTHING;
}



// Expression
int ExpressionAST::CodeGen()
{
    int result_ri=muldiv_expression->CodeGen();

    for(int i=0;i<infix_operators.size();i++)
    {
        int temp_ri=muldiv_expressions[i]->CodeGen();

        result_ri=CodeGenerator::
        BinaryInstruction(result_ri,infix_operators[i],temp_ri);
    }

    return result_ri;
}

int MulDivExpressionAST::CodeGen()
{
    int result_ri=unary_expression->CodeGen();
    
    for(int i=0;i<infix_operators.size();i++)
    {
        int temp_ri=unary_expressions[i]->CodeGen();

        result_ri=CodeGenerator::
                  BinaryInstruction(result_ri,infix_operators[i],temp_ri);
    }

    return result_ri;
}

int UnaryExpressionAST::CodeGen()
{
    int result_ri=primary_expression->CodeGen();

    if(prefix_operator=="") return result_ri;
    
    return CodeGenerator::
           UnaryInstruction(prefix_operator,result_ri);
}

int PrimaryExpressionAST::CodeGen()
{
    if(expression)return expression->CodeGen();

    return CodeGenerator::Load(literal);
}