#include "CodeGenerator.h"

PermissionSet CodeGenerator::program_permissions;
bool CodeGenerator::isInvoke;
string CodeGenerator::gen_fucntion;
FunctionTable CodeGenerator::functable;

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
    translation_unit->CodeGen();
}



// Begin
int TranslationUnitAST::CodeGen()
{
    for(unique_ptr<ASTNode>& ast_ptr:permission_definitions)
        ast_ptr->CodeGen();

    for(unique_ptr<ASTNode>& ast_ptr:invoke_definitions)
        ast_ptr->CodeGen();

    for(unique_ptr<ASTNode>& ast_ptr:function_definitions)
        ast_ptr->CodeGen();
    
    return NOTHING;
}



// Definition
int PermissionDefinitionAST::CodeGen()
{   
    for(Token t:permissions)
    {
        if(!CodeGenerator::program_permissions.HavePermission(t.lexeme))
        {
            CodeGenerator::Permission(t.lexeme);
            CodeGenerator::program_permissions.InsertPermission(t.lexeme);
        }
    }

    return NOTHING;
}



int InvokeDefinitionAST::CodeGen()
{
    CodeGenerator::isInvoke=true;

    if(ret_type.is_valid)
        CodeGenerator::Invoke(ret_type.ToRealType(),app_name.lexeme,function_name.lexeme,app_name.line);
    else
        CodeGenerator::Invoke(app_name.lexeme,function_name.lexeme,app_name.line);
    
    CodeGenerator::gen_fucntion=app_name.lexeme+"."+function_name.lexeme;

    if(parameter_list)parameter_list->CodeGen();

    return NOTHING;
}

int FunctionDefinitionAST::CodeGen()
{
    CodeGenerator::isInvoke=false;

    if(ret_type.is_valid)
        CodeGenerator::Func(ret_type.ToRealType(),function_name.lexeme,function_name.line);
    else 
        CodeGenerator::Func(function_name.lexeme,function_name.line);

    CodeGenerator::gen_fucntion=function_name.lexeme;
    
    CodeGenerator::NowInFunction().vartable.EnterScope();
   
    // register parameters
    if(parameter_list)parameter_list->CodeGen();

    // load parameters
    int parameters_size=CodeGenerator::NowInFunction().parameters.size();
    for(int x_i=0;x_i<parameters_size;x_i++)
    {
        Parameter& parameter=CodeGenerator::NowInFunction().parameters[x_i];
        int r_i=CodeGenerator::TransX2R(x_i);
    
        CodeGenerator::Store(parameter.name,r_i,function_name.line);
    }

    for(unique_ptr<ASTNode>& ast_ptr:statements)
        ast_ptr->CodeGen();
    
    CodeGenerator::NowInFunction().vartable.LeaveScope();
    
    return NOTHING;
}

int ParameterAST::CodeGen()
{
    if(!CodeGenerator::isInvoke)
        CodeGenerator::Var(type.ToRealType(),parameter_name.lexeme,parameter_name.line);
    
    CodeGenerator::NowInFunction().parameters.push_back
        (Parameter(type.ToRealType(),parameter_name.lexeme));

    return NOTHING;
}

int ParameterListAST::CodeGen()
{
    for(unique_ptr<ASTNode>& ast_ptr:parameters)
        ast_ptr->CodeGen();

    return NOTHING;    
}

int LocalVariableDefinitionAST::CodeGen()
{
    CodeGenerator::Var(type.ToRealType(),variable_name.lexeme,variable_name.line);
    
    //Initialize
    if(expression)
    {
        int expression_ri=expression->CodeGen();
        CodeGenerator::Store(variable_name.lexeme,expression_ri,variable_name.line);
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

    for(unique_ptr<ASTNode>& ast_ptr:statements)
        ast_ptr->CodeGen();    

    CodeGenerator::NowInFunction().vartable.LeaveScope();

    return NOTHING;
}



int IfStatementAST::CodeGen()
{
    int expression_ri=expression->CodeGen();
    
    PermissionSet register_permissions=general_register.GetReg(expression_ri).type.permissions;
    int lable_statementEnd=-1;
    if(!register_permissions.IsEmpty())  
    {
        int test_ri=CodeGenerator::Test(register_permissions,If.line);
        lable_statementEnd=CodeGenerator::NowInFunction().NewLable();
        CodeGenerator::JumpFalse(lable_statementEnd,test_ri);
    }    


    CodeGenerator::Convert(D_BOOL,expression_ri);

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


    if(!register_permissions.IsEmpty())  
    {
        CodeGenerator::Lable(lable_statementEnd);
    }

    return NOTHING;
}

int WhileStatementAST::CodeGen()
{
    int lable_begin=CodeGenerator::NowInFunction().NewLable();
    int lable_end=CodeGenerator::NowInFunction().NewLable();

    CodeGenerator::Lable(lable_begin);
    int expression_ri=expression->CodeGen();


    PermissionSet register_permissions=general_register.GetReg(expression_ri).type.permissions;
    if(!register_permissions.IsEmpty())
    {
        int test_ri=CodeGenerator::Test(register_permissions,While.line);
        CodeGenerator::JumpFalse(lable_end,test_ri);
    }


    CodeGenerator::Convert(D_BOOL,expression_ri);
    CodeGenerator::JumpFalse(lable_end,expression_ri);

    statement->CodeGen();
    
    CodeGenerator::Jump(lable_begin);
    CodeGenerator::Lable(lable_end);

    return NOTHING;
}

int ReturnStatementAST::CodeGen()
{
    int line=ret.line;

    if(expression)
    {
        if(CodeGenerator::NowInFunction().is_void)
            TYPE_ERROR("Function ret type is void");

        int expression_ri=expression->CodeGen();
        CodeGenerator::TransR2Y(expression_ri,line);
    }
    else if(!CodeGenerator::NowInFunction().is_void)
        TYPE_ERROR("Function ret type is not void");
    
    CodeGenerator::Ret();

    return NOTHING;
}

int ExitStatementAST::CodeGen()
{
    CodeGenerator::Exit();

    return NOTHING;
}

int SleepStatementAST::CodeGen()
{
    CodeGenerator::Sleep(constant.lexeme);
    
    return NOTHING;
}

int InputStatementAST::CodeGen()
{
    for(Token& variable:variables)
        CodeGenerator::Input(variable.lexeme,variable.line);

    return NOTHING;
}

int OutputStatementAST::CodeGen()
{
    for(unique_ptr<ASTNode>& ast_ptr:expressions)
    {
        int expression_ri=ast_ptr->CodeGen();
        CodeGenerator::Output(expression_ri,output.line);
    }

    CodeGenerator::Output(NOTHING,output.line);
    
    return NOTHING;
}

int AssignmentStatementAST::CodeGen()
{
    int expression_ri=expression->CodeGen();
    CodeGenerator::Store(variable.lexeme,expression_ri,variable.line);
  
    return NOTHING;
}

int ExpressionStatementAST::CodeGen()
{
    //@Todo:it breaks the packing

    int expression_ri=expression->CodeGen();
    general_register.Free(expression_ri);

    return NOTHING;
}



// Expression
int ExpressionAST::CodeGen()
{
    int result_ri=logicOr_expression->CodeGen();
    
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
    int result_ri=NOTHING;
    if(primary_expression)
        result_ri=primary_expression->CodeGen();
    else if(functioncall_expression)
        result_ri=functioncall_expression->CodeGen();

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
    
    return CodeGenerator::LoadVariable(variable.lexeme,variable.line);
}

int FunctionCallExpressionAST::CodeGen()
{
    int line=function.line;
    string function_name;
    if(app.is_valid)
        function_name=app.lexeme+"."+function.lexeme;
    else function_name=function.lexeme;

    Function& called_function=CodeGenerator::functable.Visit(function_name,line);

    if(called_function.parameters.size()!=expressions.size())
        TYPE_ERROR("Parameter and Argument number not match");

    // store argument
    vector<int> expression_ris;
    for(int i=0;i<expressions.size();i++)
        expression_ris.push_back(expressions[i]->CodeGen());

    for(int i=0;i<expressions.size();i++)
    {
        int r_i=expression_ris[i];
        Parameter& parameter=called_function.parameters[i];
        
        PermissionSet register_permissions=general_register.GetReg(r_i).type.permissions;
        PermissionSet parameter_permissions=parameter.type.permissions;
        
        PermissionSet miss_permissions=register_permissions-parameter_permissions;
        if(!miss_permissions.IsEmpty())
            TYPE_ERROR("Miss permissions"+miss_permissions.Str());

        int lable_transEnd=-1;
        if(!parameter_permissions.IsEmpty())
        {
            int test_ri=CodeGenerator::Test(parameter_permissions,line);
            lable_transEnd=CodeGenerator::NowInFunction().NewLable();
            CodeGenerator::JumpFalse(lable_transEnd,test_ri);
        }


        DataTypeChecker::Check_Store(parameter.type.data,r_i,line);
        CodeGenerator::TransR2X(i,r_i);


        if(!parameter_permissions.IsEmpty())
        {
            CodeGenerator::Lable(lable_transEnd);
        }
    }

    return CodeGenerator::Call(function_name,function.line);
}