#include "CodeGenerator.h"

FunctionTable CodeGenerator::functable;
string CodeGenerator::gen_fucntion;

Function& CodeGenerator::NowInFunction()
{
    return functable.Visit(gen_fucntion);
}



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
    CodeGenerator::Func(ret_type,function_name.lexeme);
    CodeGenerator::gen_fucntion=function_name.lexeme;
    
    compound_statement->CodeGen();

    return NOTHING;
}

int LocalVariableDefinitionAST::CodeGen()
{
    //@Bug:may data_type should is type
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
    CodeGenerator::NowInFunction().vartable.EnterScope();
    for(ASTNode* ast_ptr:statements)
        ast_ptr->CodeGen();    
    CodeGenerator::NowInFunction().vartable.LeaveScope();

    return NOTHING;
}



int IfStatementAST::CodeGen()
{
    int expression_ri=expression->CodeGen();

    int lable_ifEnd=CodeGenerator::NowInFunction().NewLable();
    CodeGenerator::JumpFalse(lable_ifEnd,expression_ri);

    true_statement->CodeGen();

    //else
    if(false_statement)
    {
        int lable_elseEnd=CodeGenerator::NowInFunction().NewLable();
        CodeGenerator::Jump(lable_elseEnd);

        CodeGenerator::Lable(lable_ifEnd);
        false_statement->CodeGen();
        CodeGenerator::Lable(lable_elseEnd);
    }
    else CodeGenerator::Lable(lable_ifEnd);

    return NOTHING;
}

int WhileStatementAST::CodeGen()
{
    int lable_begin=CodeGenerator::NowInFunction().NewLable();
    int lable_end=CodeGenerator::NowInFunction().NewLable();

    CodeGenerator::Lable(lable_begin);
    int expression_ri=expression->CodeGen();
    CodeGenerator::JumpFalse(lable_end,expression_ri);

    statement->CodeGen();
    
    CodeGenerator::Jump(lable_begin);
    CodeGenerator::Lable(lable_end);

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
        general_register.Free(expression_i);
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



int LogicOrExpressionAST::CodeGen()
{
    int result_ri=logicAnd_expression->CodeGen();

    for(int i=0;i<logicAnd_expressions.size();i++)
    {
        int temp_ri=logicAnd_expressions[i]->CodeGen();

        result_ri=CodeGenerator::
        BinaryInstruction(result_ri,infix_operators[i],temp_ri);
    }

    return result_ri;
}

int LogicAndExpressionAST::CodeGen()
{
    int result_ri=equality_expression->CodeGen();

    for(int i=0;i<equality_expressions.size();i++)
    {
        int temp_ri=equality_expressions[i]->CodeGen();

        result_ri=CodeGenerator::
        BinaryInstruction(result_ri,infix_operators[i],temp_ri);
    }

    return result_ri;
}



int EqualityExpressionAST::CodeGen()
{
    int result_ri=relational_expression->CodeGen();

    for(int i=0;i<relational_expressions.size();i++)
    {
        int temp_ri=relational_expressions[i]->CodeGen();

        result_ri=CodeGenerator::
        BinaryInstruction(result_ri,infix_operators[i],temp_ri);
    }

    return result_ri;
}

int RelationalExpressionAST::CodeGen()
{
    int result_ri=plusminus_expression->CodeGen();

    for(int i=0;i<plusminus_expressions.size();i++)
    {
        int temp_ri=plusminus_expressions[i]->CodeGen();

        result_ri=CodeGenerator::
        BinaryInstruction(result_ri,infix_operators[i],temp_ri);
    }
    
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