#include "CodeGenerator.h"

void CodeGenerator::Func(Token type,string function_name)
{
    functable.Add(type,function_name);

    // Opcode
    file_manager.Write(is_upper?"FUNC":"func");
    file_manager.Write("\t");

    // Operand1
    if(type.is_valid)
    {
        switch(type.token_type)
        {
            case INT: file_manager.Write(is_upper?"INT":"int");  break;
            case DEC: file_manager.Write(is_upper?"DEC":"dec");  break;
            case STR: file_manager.Write(is_upper?"STR":"str");  break;
            case BOOL:file_manager.Write(is_upper?"BOOL":"bool");break;
        }
    }
    else file_manager.Write(is_upper?"VOID":"void");
    file_manager.WriteComma();

    // Operand2
    file_manager.Write(function_name);
    file_manager.WriteEndl();
}

void CodeGenerator::Var(Token type,string variable_name)
{
    NowInFunction().vartable.Add(type,variable_name);
    int scope_i=NowInFunction().vartable.ScopeSize()-1;
    
    // Opcode
    file_manager.Write(is_upper?"VAR":"var");
    file_manager.Write("\t\t");
    
    // Operand1
    switch(type.token_type)
    {
        case INT: file_manager.Write(is_upper?"INT":"int");  break;
        case DEC: file_manager.Write(is_upper?"DEC":"dec");  break;
        case STR: file_manager.Write(is_upper?"STR":"str");  break;
        case BOOL:file_manager.Write(is_upper?"BOOL":"bool");break;
    }
    file_manager.WriteComma();
    
    // Operand2
    file_manager.Write(variable_name);
    file_manager.Write("(");
    file_manager.Write(to_string(scope_i));
    file_manager.Write(")");
    file_manager.WriteEndl();
}



//@Todo:Reduce load and store (from dragon book)
int CodeGenerator::LoadConstant(Token constant)
{   
    int register_i=-1;

    switch(constant.token_type)
    {
        case CONSTANT_INT:
            register_i= general_register.Alloc(D_INT);
            break;
        case CONSTANT_DEC:
            register_i= general_register.Alloc(D_DEC);
            break;
        case CONSTANT_STR:
            register_i= general_register.Alloc(D_STR);
            break;
        case TRUE:case FALSE:
            register_i= general_register.Alloc(D_BOOL);
            break;
    }

    //@Todo:Load error
    // Opcode
    file_manager.Write(is_upper?"LOAD":"load");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(register_i);
    file_manager.WriteComma();

    // Operand2
    file_manager.Write(constant.lexeme);
    file_manager.WriteEndl();

    return register_i;
}

int CodeGenerator::LoadVariable(Token variable)
{
    int register_i=-1;

    Variable target=NowInFunction().vartable.Visit(variable);

    switch(target.data_type)
    {
        case D_INT:
            register_i= general_register.Alloc(D_INT);
            break;
        case D_DEC:
            register_i= general_register.Alloc(D_DEC);
            break;
        case D_STR:
            register_i= general_register.Alloc(D_STR);
            break;
        case D_BOOL:
            register_i= general_register.Alloc(D_BOOL);
            break;
    }

    // Opcode
    file_manager.Write(is_upper?"LOAD":"load");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(register_i);
    file_manager.WriteComma();

    // Operand2
    file_manager.Write(target.name);
    file_manager.Write("(");
    file_manager.Write(to_string(target.scope_i));
    file_manager.Write(")");
    file_manager.WriteEndl();

    return register_i;
}

void CodeGenerator::Store(Token variable,int register_i,bool need_free)
{ 
    Variable target=NowInFunction().vartable.Visit(variable);
    TypeChecker::Check_Store(target.data_type,register_i,variable.line);

    // Opcode
    file_manager.Write(is_upper?"STORE":"store");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(target.name);
    file_manager.Write("(");
    file_manager.Write(to_string(target.scope_i));
    file_manager.Write(")");
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(register_i);
    file_manager.WriteEndl();

    if(need_free)general_register.Free(register_i);
}

void CodeGenerator::Convert(int register_i,DataType to_dataType)
{
    Register& R=general_register.GetReg(register_i);

    // Opcode
    file_manager.Write(is_upper?"CVT":"cvt");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(register_i);
    file_manager.WriteComma();

    // Operand2
    switch(to_dataType)
    {
        case D_INT:
            R.data_type=D_INT;
            file_manager.Write(is_upper?"INT":"int");
            break;
        case D_DEC:
            R.data_type=D_DEC;
            file_manager.Write(is_upper?"DEC":"dec");
            break;
        case D_STR:
            R.data_type=D_STR;
            file_manager.Write(is_upper?"STR":"str");
            break;
        case D_BOOL:
            R.data_type=D_BOOL;
            file_manager.Write(is_upper?"BOOL":"bool");
            break;
    }
    file_manager.WriteEndl();
}



void CodeGenerator::Print(int register_i)
{
    // Opcode
    file_manager.Write(is_upper?"PRINT":"print");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(register_i);
    file_manager.WriteEndl();

    general_register.Free(register_i);
}



//Control Flow
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

void CodeGenerator::JumpTrue(int lable_id,int register_i)
{
    // Opcode
    file_manager.Write(is_upper?"JMPT":"jmpt");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(to_string(lable_id));
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(register_i);
    file_manager.WriteEndl();

    general_register.Free(register_i);
}

void CodeGenerator::JumpFalse(int lable_id,int register_i)
{
    // Opcode
    file_manager.Write(is_upper?"JMPF":"jmpf");
    file_manager.Write("\t");

    // Operand1
    file_manager.Write(to_string(lable_id));
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(register_i);
    file_manager.WriteEndl();

    general_register.Free(register_i);
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

    return -1;
}

// Logic
int CodeGenerator::Or(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_Or(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"OR":"or");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::And(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_And(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"AND":"and");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Equal(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_Equal(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"EQU":"equ");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::NotEqual(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_NotEqual(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"NEQU":"nequ");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Less(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_Less(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"LES":"les");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::LessEqual(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_LessEqual(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"LEQU":"lequ");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Greater(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_Greater(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"GRE":"gre");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::GreaterEqual(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_GreaterEqual(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"GEQU":"gequ");
    file_manager.Write("\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

// Arithmetic
int CodeGenerator::Add(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_Add(r1_i,r2_i,line);

    // Opcode
    file_manager.Write(is_upper?"ADD":"add");
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Sub(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_Sub(r1_i,r2_i,line);

    // Opcode
    file_manager.Write((is_upper?"SUB":"sub"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Mul(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_Mul(r1_i,r2_i,line);

    // Opcode
    file_manager.Write((is_upper?"MUL":"mul"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Div(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_Div(r1_i,r2_i,line);

    // Opcode
    file_manager.Write((is_upper?"DIV":"div"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::Mod(int r1_i,int r2_i,int line)
{
    TypeChecker::Check_Mod(r1_i,r2_i,line);

    // Opcode
    file_manager.Write((is_upper?"MOD":"mod"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();

    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}



// Unary
int CodeGenerator::UnaryInstruction(Token Operator,int register_i)
{
    switch(Operator.token_type)
    {
        case MINUS:return Neg(register_i,Operator.line);
        case NOT:  return Not(register_i,Operator.line);
    }

    return -1;
}

int CodeGenerator::Neg(int register_i,int line)
{   
    TypeChecker::Check_Neg(register_i,line);

    // Opcode
    file_manager.Write((is_upper?"Neg":"neg"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(register_i);
    file_manager.WriteEndl();

    return register_i;
}

int CodeGenerator::Not(int register_i,int line)
{
    TypeChecker::Check_Not(register_i,line);

    // Opcode
    file_manager.Write((is_upper?"Not":"not"));
    file_manager.Write("\t\t");

    // Operand1
    WriteGeneralRegisterName(register_i);
    file_manager.WriteEndl();

    return register_i;
}