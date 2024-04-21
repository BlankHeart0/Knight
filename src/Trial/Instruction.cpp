#include "CodeGenerator.h"

// Type
void CodeGenerator::Permission(string permission)
{
    // Opcode
    file_manager.Write(is_upper?"PERM":"perm");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(permission);
    file_manager.WriteComma();

    // Operand2
    file_manager.Write("0");
    file_manager.WriteEndl();
}

int CodeGenerator::Test(PermissionSet permissions,int line)
{
    // Static permission check
    PermissionSet miss_permissions=permissions-program_permissions;
    if(!miss_permissions.IsEmpty())
        TYPE_ERROR("Miss permissions"+miss_permissions.Str());

    // Dynamic permission check
    int r_i=general_register.Alloc(Type(D_BOOL,PermissionType()));

    // Opcode
    file_manager.Write(is_upper?"TEST":"test");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r_i);
    file_manager.WriteComma();

    // Operand2
    file_manager.Write(permissions.Str());
    file_manager.WriteEndl();

    return r_i;
}

void CodeGenerator::Convert(DataType to_dtype,int r_i)
{    
    Register& R=general_register.GetReg(r_i);

    // Opcode
    file_manager.Write(is_upper?"CVT":"cvt");
    file_manager.Write("\t\t");

    // Operand1  
    R.type.data=to_dtype;
    switch(to_dtype)
    {
        case D_INT: file_manager.Write(is_upper?"INT":"int");  break;
        case D_DEC: file_manager.Write(is_upper?"DEC":"dec");  break;
        case D_STR: file_manager.Write(is_upper?"STR":"str");  break;
        case D_BOOL:file_manager.Write(is_upper?"BOOL":"bool");break;
    }
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r_i);
    file_manager.WriteEndl();
}



// Variable
void CodeGenerator::Var(Type type,string variable_name,int line)
{
    NowInFunction().vartable.Add(type,variable_name,line);
    int scope_i=NowInFunction().vartable.Visit(variable_name,line).scope_i;
    
    // Opcode
    file_manager.Write(is_upper?"VAR":"var");
    file_manager.Write("\t\t");
    
    // Operand1
    file_manager.Write(type.Str());
    file_manager.WriteComma();
    
    // Operand2
    file_manager.Write(variable_name);
    file_manager.Write("(");
    file_manager.Write(to_string(scope_i));
    file_manager.Write(")");
    file_manager.WriteEndl();
}

int CodeGenerator::LoadConstant(Token constant)
{   
    int r_i=-1;

    switch(constant.token_type)
    {
        case CONSTANT_INT:
            r_i=general_register.Alloc(Type(D_INT,PermissionType()));
            break;
        case CONSTANT_DEC:
            r_i=general_register.Alloc(Type(D_DEC,PermissionType()));
            break;
        case CONSTANT_STR:
            r_i=general_register.Alloc(Type(D_STR,PermissionType()));
            break;
        case TRUE:case FALSE:
            r_i=general_register.Alloc(Type(D_BOOL,PermissionType()));
            break;
    }

    // Opcode
    file_manager.Write(is_upper?"LOAD":"load");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r_i);
    file_manager.WriteComma();

    // Operand2
    file_manager.Write(constant.lexeme);
    file_manager.WriteEndl();

    return r_i;
}

int CodeGenerator::LoadVariable(string variable_name,int line)
{
    int r_i=-1;

    Variable variable=NowInFunction().vartable.Visit(variable_name,line);
    r_i=general_register.Alloc(variable.type);

    // Opcode
    file_manager.Write(is_upper?"LOAD":"load");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r_i);
    file_manager.WriteComma();

    // Operand2
    file_manager.Write(variable.name);
    file_manager.Write("(");
    file_manager.Write(to_string(variable.scope_i));
    file_manager.Write(")");
    file_manager.WriteEndl();

    return r_i;
}

void CodeGenerator::Store(string variable_name,int r_i,int line)
{         
    Variable variable=NowInFunction().vartable.Visit(variable_name,line);

    PermissionSet variable_permissions=variable.type.permissions;
    PermissionSet register_permissions=general_register.GetReg(r_i).type.permissions;
    PermissionSet need_permissions=register_permissions-variable_permissions;
    int lable_storeEnd=-1;
    if(!need_permissions.IsEmpty())
    {
        int test_ri=CodeGenerator::Test(need_permissions,line);
        lable_storeEnd=CodeGenerator::NowInFunction().NewLable();
        CodeGenerator::JumpFalse(lable_storeEnd,test_ri);
    }


    DataTypeChecker::Check_Store(variable.type.data,r_i,line);

    // Opcode
    file_manager.Write(is_upper?"STORE":"store");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(variable.name);
    file_manager.Write("(");
    file_manager.Write(to_string(variable.scope_i));
    file_manager.Write(")");
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r_i);
    file_manager.WriteEndl();

    general_register.Free(r_i);


    if(!need_permissions.IsEmpty())
    {
        CodeGenerator::Lable(lable_storeEnd);
    }
}



// Fucntion
void CodeGenerator::Invoke(string app_name,string function_name,int line)
{
    functable.Add(app_name+"."+function_name,line);
    
    // Opcode
    file_manager.Write(is_upper?"INVOKE":"invoke");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(app_name);
    file_manager.WriteComma();

    // Operand2
    file_manager.Write(function_name);
    file_manager.WriteEndl();
}

void CodeGenerator::Invoke(Type type,string app_name,string function_name,int line)
{
    functable.Add(type,app_name+"."+function_name,line);
    
    // Opcode
    file_manager.Write(is_upper?"INVOKE":"invoke");
    file_manager.Write("\t");
    
    // Operand1
    file_manager.Write(app_name);
    file_manager.WriteComma();

    // Operand2
    file_manager.Write(function_name);
    file_manager.WriteEndl();
}

void CodeGenerator::Func(string function_name,int line)
{
    functable.Add(function_name,line);

    // Opcode
    file_manager.Write(is_upper?"FUNC":"func");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(function_name);
    file_manager.WriteEndl();
}

void CodeGenerator::Func(Type type,string function_name,int line)
{
    functable.Add(type,function_name,line);

    // Opcode
    file_manager.Write(is_upper?"FUNC":"func");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(function_name);
    file_manager.WriteEndl();
}

int CodeGenerator::TransX2R(int x_i)
{
    Parameter& parameter=NowInFunction().parameters[x_i];

    int r_i= general_register.Alloc(parameter.type);
    
    // Opcode
    file_manager.Write(is_upper?"TRANS":"trans");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r_i);
    file_manager.WriteComma();

    // Operand2
    file_manager.Write(is_upper?"X":"x");
    file_manager.Write(to_string(x_i));
    file_manager.WriteEndl();

    return r_i;
}

void CodeGenerator::TransR2X(int x_i,int r_i)
{
    // Opcode
    file_manager.Write(is_upper?"TRANS":"trans");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(is_upper?"X":"x");
    file_manager.Write(to_string(x_i));
    file_manager.WriteComma();
    
    // Operand2
    WriteGeneralRegisterName(r_i);
    file_manager.WriteEndl();

    general_register.Free(r_i);
}

void CodeGenerator::TransY2R(int r_i)
{
    // Opcode
    file_manager.Write(is_upper?"TRANS":"trans");
    file_manager.Write("\t");
    
    // Operand1
    WriteGeneralRegisterName(r_i);
    file_manager.WriteComma();

    // Operand2
    file_manager.Write(is_upper?"Y":"y");
    file_manager.WriteEndl();
}

void CodeGenerator::TransR2Y(int r_i,int line)
{
    PermissionSet ret_permissions=NowInFunction().ret_type.permissions;
    PermissionSet register_permissions=general_register.GetReg(r_i).type.permissions;
    PermissionSet need_permissions=register_permissions-ret_permissions;
    int lable_transEnd=-1;
    if(!need_permissions.IsEmpty())
    {
        int test_ri=CodeGenerator::Test(need_permissions,line);
        lable_transEnd=CodeGenerator::NowInFunction().NewLable();
        CodeGenerator::JumpFalse(lable_transEnd,test_ri);
    }


    DataTypeChecker::Check_Store(NowInFunction().ret_type.data,r_i,line);

    // Opcode
    file_manager.Write(is_upper?"TRANS":"trans");
    file_manager.Write("\t");
    
    // Operand1
    file_manager.Write(is_upper?"Y":"y");
    file_manager.WriteComma();
    
    // Operand2
    WriteGeneralRegisterName(r_i);
    file_manager.WriteEndl();

    general_register.Free(r_i);


    if(!need_permissions.IsEmpty())
    {
        CodeGenerator::Lable(lable_transEnd);
    }
}

int CodeGenerator::Call(string function_name,int line)
{
    Function& called_function=CodeGenerator::functable.Visit(function_name,line);

    // save used general register
    vector<int>used_ri;
    for(int r_i=0;r_i<general_register.table.size();r_i++)
    {
        if(!general_register.table[r_i].free)
        {
            used_ri.push_back(r_i);
            Push(r_i);
        }
    }

    // Opcode
    file_manager.Write(is_upper?"CALL":"call");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(called_function.name);
    file_manager.WriteEndl();

    // recover used general register
    for(int i=used_ri.size()-1;i>=0;i--)
    {
        Pop(used_ri[i]);
    }

    // get the ret value
    if(!called_function.is_void)
    {
        int r_i= general_register.Alloc(called_function.ret_type);
        TransY2R(r_i);
        return r_i;
    }

    //@Bug:don't use void function's ret value
    return NOTHING;
}

void CodeGenerator::Ret()
{
    // Opcode
    file_manager.Write(is_upper?"RET":"ret");
    file_manager.Write("\t\t");

    file_manager.WriteEndl();
}

void CodeGenerator::Exit()
{
    // Opcode
    file_manager.Write(is_upper?"EXIT":"exit");
    file_manager.Write("\t");

    file_manager.WriteEndl();
}

void CodeGenerator::Sleep(string time)
{
    // Opcode
    file_manager.Write(is_upper?"SLEEP":"sleep");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(time);
    file_manager.WriteEndl();
}

void CodeGenerator::Push(int r_i)
{
    // Opcode
    file_manager.Write(is_upper?"PUSH":"push");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r_i);
    file_manager.WriteEndl();
}

void CodeGenerator::Pop(int r_i)
{
    // Opcode
    file_manager.Write(is_upper?"POP":"pop");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r_i);
    file_manager.WriteEndl();
}

void CodeGenerator::Input(string variable_name,int line)
{
    Variable variable=NowInFunction().vartable.Visit(variable_name,line);

    // Opcode
    file_manager.Write(is_upper?"INPUT":"input");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(variable.name);
    file_manager.Write("(");
    file_manager.Write(to_string(variable.scope_i));
    file_manager.Write(")");
    file_manager.WriteEndl();
}

void CodeGenerator::Output(int r_i,int line)
{
    if(r_i==NOTHING)
    {
        // Opcode
        file_manager.Write(is_upper?"OUTPUT":"output");
        file_manager.Write("\t");
        // Operand1
        file_manager.Write(is_upper?"ENDLINE":"endline");
        file_manager.WriteEndl();

        return;
    }


    PermissionSet register_permissions=general_register.GetReg(r_i).type.permissions;
    int lable_printEnd=-1;
    if(!register_permissions.IsEmpty())  
    {
        int test_ri=CodeGenerator::Test(register_permissions,line);
        lable_printEnd=CodeGenerator::NowInFunction().NewLable();
        CodeGenerator::JumpFalse(lable_printEnd,test_ri);
    }    


    // Opcode
    file_manager.Write(is_upper?"OUTPUT":"output");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r_i);
    file_manager.WriteEndl();

    general_register.Free(r_i);


    if(!register_permissions.IsEmpty())  
    {
        CodeGenerator::Lable(lable_printEnd);
    }
}



// Control Flow
void CodeGenerator::Lable(int lable_id)
{
    // Opcode
    file_manager.Write(is_upper?"LABLE":"lable");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(to_string(lable_id));
    file_manager.WriteEndl();
}  

void CodeGenerator::Jump(int lable_id)
{
    // Opcode
    file_manager.Write(is_upper?"JMP":"jmp");
    file_manager.Write("\t\t");

    // Operand1
    file_manager.Write(to_string(lable_id));
    file_manager.WriteEndl();
}

void CodeGenerator::JumpTrue(int lable_id,int r_i)
{
    // Opcode
    file_manager.Write(is_upper?"JMPT":"jmpt");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(to_string(lable_id));
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r_i);
    file_manager.WriteEndl();

    general_register.Free(r_i);
}

void CodeGenerator::JumpFalse(int lable_id,int r_i)
{
    // Opcode
    file_manager.Write(is_upper?"JMPF":"jmpf");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(to_string(lable_id));
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r_i);
    file_manager.WriteEndl();

    general_register.Free(r_i);
}



// Binary
int CodeGenerator::BinaryInstruction(int r1_i,Token Operator,int r2_i)
{   
    switch(Operator.token_type)
    {
        // Logic
        case OR:            return Or(r1_i,r2_i,Operator.line);
        case AND:           return And(r1_i,r2_i,Operator.line);
        case EQUAL:         return Equal(r1_i,r2_i,Operator.line);
        case NOT_EQUAL:     return NotEqual(r1_i,r2_i,Operator.line);
        case LESS:          return Less(r1_i,r2_i,Operator.line);
        case LESS_EQUAL:    return LessEqual(r1_i,r2_i,Operator.line);
        case GREATER:       return Greater(r1_i,r2_i,Operator.line);
        case GREATER_EQUAL: return GreaterEqual(r1_i,r2_i,Operator.line);

        // Arithmetic
        case PLUS:          return Add(r1_i,r2_i,Operator.line);
        case MINUS:         return Sub(r1_i,r2_i,Operator.line);
        case STAR:          return Mul(r1_i,r2_i,Operator.line);
        case SLASH:         return Div(r1_i,r2_i,Operator.line);
        case PERCENT:       return Mod(r1_i,r2_i,Operator.line);
    }

    return NOTHING;
}

// Logic
int CodeGenerator::Or(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_Or(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"OR":"or");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.data=D_BOOL;
    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::And(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_And(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"AND":"and");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.data=D_BOOL;
    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Equal(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_Equal(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"EQU":"equ");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.data=D_BOOL;
    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::NotEqual(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_NotEqual(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"NEQU":"nequ");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.data=D_BOOL;
    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Less(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_Less(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"LES":"les");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.data=D_BOOL;
    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::LessEqual(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_LessEqual(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"LEQU":"lequ");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.data=D_BOOL;
    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Greater(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_Greater(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"GRE":"gre");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.data=D_BOOL;
    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::GreaterEqual(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_GreaterEqual(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"GEQU":"gequ");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.data=D_BOOL;
    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

// Arithmetic
int CodeGenerator::Add(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_Add(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"ADD":"add");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Sub(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_Sub(r1_i,r2_i,line);

    // Opcode
    file_manager.Write((is_upper?"SUB":"sub"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Mul(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_Mul(r1_i,r2_i,line);

    // Opcode
    file_manager.Write((is_upper?"MUL":"mul"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Div(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_Div(r1_i,r2_i,line);

    // Opcode
    file_manager.Write((is_upper?"DIV":"div"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Mod(int r1_i,int r2_i,int line)
{
    DataTypeChecker::Check_Mod(r1_i,r2_i,line);

    // Opcode
    file_manager.Write((is_upper?"MOD":"mod"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.GetReg(r1_i).type.permissions+=
    general_register.GetReg(r2_i).type.permissions;

    general_register.Free(r2_i);

    return r1_i;
}



// Unary
int CodeGenerator::UnaryInstruction(Token Operator,int r_i)
{
    switch(Operator.token_type)
    {
        case MINUS:return Neg(r_i,Operator.line);
        case NOT:  return Not(r_i,Operator.line);
    }

    return -1;
}

int CodeGenerator::Neg(int r_i,int line)
{   
    DataTypeChecker::Check_Neg(r_i,line);

    // Opcode
    file_manager.Write((is_upper?"NEG":"neg"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r_i);
    file_manager.WriteEndl();

    return r_i;
}

int CodeGenerator::Not(int r_i,int line)
{
    DataTypeChecker::Check_Not(r_i,line);

    // Opcode
    file_manager.Write((is_upper?"NOT":"not"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r_i);
    file_manager.WriteEndl();

    return r_i;
}