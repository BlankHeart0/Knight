#include "CodeGenerator.h"

GeneralRegister CodeGenerator::general_register;
VariableTable CodeGenerator::vartable;

void CodeGenerator::CodeGen()
{
    abstract_syntax_tree.CodeGen();
}

void AST::CodeGen()
{
    cout<<"--- --- CodeGen Begin --- ---"<<endl;
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
    //file_manager.Write(function_name.lexeme+":\n");
    compound_statement->CodeGen();

    return NOTHING;
}

int LocalVariableDefinitionAST::CodeGen()
{
    CodeGenerator::Var(data_type,variable_name.lexeme);
    //Initialize
    if(expression)
    {
        int expression_i=expression->CodeGen();
        CodeGenerator::Store(variable_name,expression_i,true);
    }

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
    CodeGenerator::vartable.EnterScope();
    for(ASTNode* ast_ptr:statements)
        ast_ptr->CodeGen();    
    CodeGenerator::vartable.LeaveScope();

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
    //@Todo:it breaks the packing
    if(expression)
    {
        int expression_i=expression->CodeGen();
        CodeGenerator::general_register.Free(expression_i);
    }
    return NOTHING;
}



// Expression
int ExpressionAST::CodeGen()
{
    int result_ri=assignment_expression->CodeGen();
    
    return result_ri;
}

int AssignmentExpressionAST::CodeGen()
{
    int result_ri=logicOr_expression->CodeGen();

    if(variable.is_valid)
        CodeGenerator::Store(variable,result_ri,false);
    
    return result_ri;
}

int PlusMinusExpressionAST::CodeGen()
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

    if(!prefix_operator.is_valid) return result_ri;
    
    return CodeGenerator::
           UnaryInstruction(prefix_operator,result_ri);
}

int PrimaryExpressionAST::CodeGen()
{
    if(expression)
        return expression->CodeGen();
    else if(constant.is_valid)
        return CodeGenerator::LoadConstant(constant);
    
    return CodeGenerator::LoadVariable(variable);
}