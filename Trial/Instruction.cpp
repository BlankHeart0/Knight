#include "CodeGenerator.h"

//@Todo:Reduce load and store (from dragon book)
int CodeGenerator::Load(Literal literal)
{   
    int register_i=-1;

    switch(literal.literal_type)
    {
        case L_INT:
            register_i= general_register.Alloc(S_INT);
            break;
        case L_DEC:
            register_i= general_register.Alloc(S_DEC);
            break;
        case L_STR:
            register_i= general_register.Alloc(S_STR);
            break;
    }

    //@Todo:Load error

    file_manager.Write("Load\t");
    WriteGeneralRegisterName(register_i);

    file_manager.WriteComma();
    switch(literal.literal_type)
    {
        case L_INT:  
            file_manager.Write(to_string(literal.literal_int));
            break;
        case L_DEC:
            file_manager.Write(to_string(literal.literal_dec));
            break;
        case L_STR:
            file_manager.Write("\""+literal.literal_str+"\"");
            break;
    }
    file_manager.WriteEndl();

    return register_i;
}


void CodeGenerator::Print(int register_i)
{
    file_manager.Write("Print\t");
    WriteGeneralRegisterName(register_i);
    file_manager.WriteEndl();

    general_register.Free(register_i);
}

int CodeGenerator::BinaryInstruction(int r1_i,char Operator,int r2_i)
{   
    string operator_instruction;

    switch(Operator)
    {
        case '+':operator_instruction="Add";break;
        case '-':operator_instruction="Sub";break;
        case '*':operator_instruction="Mul";break;
        case '/':operator_instruction="Div";break;
        case '%':operator_instruction="Mod";break;
    }

    file_manager.Write(operator_instruction+"\t\t");
    WriteGeneralRegisterName(r1_i);
    file_manager.WriteComma();
    WriteGeneralRegisterName(r2_i);
    file_manager.WriteEndl();

    general_register.Free(r2_i);

    return r1_i;
}

int CodeGenerator::UnaryInstruction(string Operator,int register_i)
{
    string operator_instruction;

    if(Operator=="-")operator_instruction="Neg\t\t";

    file_manager.Write(operator_instruction);
    WriteGeneralRegisterName(register_i);
    file_manager.WriteEndl();

    return register_i;
}
