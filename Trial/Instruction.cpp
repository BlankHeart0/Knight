#include "CodeGenerator.h"

void CodeGenerator::Var(Token type,string variable_name)
{
    vartable.Add(type,variable_name);
    int scope_i=vartable.ScopeSize()-1;

    file_manager.Write("Var\t\t");
    
    // Operand1
    switch(type.token_type)
    {
        case INT: file_manager.Write("INT"); break;
        case DEC: file_manager.Write("DEC"); break;
        case STR: file_manager.Write("STR"); break;
        case BOOL:file_manager.Write("BOOL");break;
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
            register_i= general_register.Alloc(S_INT);
            break;
        case CONSTANT_DEC:
            register_i= general_register.Alloc(S_DEC);
            break;
        case CONSTANT_STR:
            register_i= general_register.Alloc(S_STR);
            break;
        case TRUE:case FALSE:
            register_i= general_register.Alloc(S_BOOL);
            break;
    }

    //@Todo:Load error

    file_manager.Write("Load\t");

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

    Variable target=vartable.Visit(variable);

    switch(target.data_type)
    {
        case D_INT:
            register_i= general_register.Alloc(S_INT);
            break;
        case D_DEC:
            register_i= general_register.Alloc(S_DEC);
            break;
        case D_STR:
            register_i= general_register.Alloc(S_STR);
            break;
        case D_BOOL:
            register_i= general_register.Alloc(S_BOOL);
            break;
    }

    file_manager.Write("Load\t");

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
    file_manager.Write("Store\t");

    // Operand1
    Variable target=vartable.Visit(variable);
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



void CodeGenerator::Print(int register_i)
{
    file_manager.Write("Print\t");

    // Operand1
    WriteGeneralRegisterName(register_i);
    file_manager.WriteEndl();

    general_register.Free(register_i);
}

int CodeGenerator::BinaryInstruction(int r1_i,Token Operator,int r2_i)
{   
    string opcode;

    switch(Operator.token_type)
    {
        case PLUS:   opcode="Add";break;
        case MINUS:  opcode="Sub";break;
        case STAR:   opcode="Mul";break;
        case SLASH:  opcode="Div";break;
        case PERCENT:opcode="Mod";break;
    }

    file_manager.Write(opcode+"\t\t");
    
    // Operand1
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();
    
    // Operand2
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::UnaryInstruction(Token Operator,int register_i)
{
    string opcode;

    switch(Operator.token_type)
    {
        case MINUS:opcode="Neg";break;
    }
    
    file_manager.Write(opcode+"\t\t");
    
    // Operand1
    WriteGeneralRegisterName(register_i);
    file_manager.WriteEndl();

    return register_i;
}
