#include "Parser.h"

Instruction* Parser::Parse()
{
    // Opcode
    int end=current;
    while(isalpha(knightASM_code[end]))end++;
    opcode=knightASM_code.substr(0,end);

    // Operand1
    while(!isalpha(knightASM_code[end]))end++;
    current=end;
    while(end<knightASM_code.size()&&knightASM_code[end]!=',')end++;
    operand1=knightASM_code.substr(current,end-current);

    // Operand2
    if(end<knightASM_code.size())
    {
        current=++end;
        while(end<knightASM_code.size())end++;
        operand2=knightASM_code.substr(current,end-current);
    }  

    return ParseFunction_map[opcode](operand1,operand2);
}



// Operand
OperandConstant Parse_OperandConstant(string& operand_str)
{
    int current=0;

    // Number
    if(isdigit(operand_str[current]))
    {
        int part_int=0;
        double part_decimal=0;
        bool is_decimal=false;

        while(current<operand_str.size()
            &&isdigit(operand_str[current]))
        {
            part_int=part_int*10+operand_str[current]-'0';
            current++;
        }
        
        if(current<operand_str.size())
        {
            is_decimal=true;
            current++;
            for(int i=1;current<operand_str.size();i++,current++)
            {
                part_decimal+=(double)(operand_str[current]-'0')/pow(10,i);
            }
        }
        
        if(is_decimal)return OperandConstant((double)part_int+part_decimal);
        else return OperandConstant(part_int);
    }

    // String
    return OperandConstant(operand_str.substr(1,operand_str.size()-2));
}

OperandRegister Parse_OperandRegister(string& operand_str)
{
    //@Todo:only General Register now
    int current=1;
    int register_i=0;
    while(current<operand_str.size()&&isdigit(operand_str[current]))
    {
        register_i=register_i*10+operand_str[current]-'0';
        current++;
    }

    return OperandRegister(R_General,register_i);
}

OperandType Parse_OperandType(string& operand_str)
{
    if(operand_str=="INT")return OperandType(D_INT);
    else if(operand_str=="DEC")return OperandType(D_DEC);
    
    return OperandType(D_STR);
}

OperandVariable Parse_OperandVariable(string& operand_str)
{
    int current=0;
    //@Bug:I think it must have (
    while(operand_str[current]!='(')current++;
    string variable_name=operand_str.substr(0,current);
    //@Bug: Also ...
    current++;
    int scope_i=0;
    while(operand_str[current]!=')')
    {
        scope_i=scope_i*10+operand_str[current]-'0';
        current++;
    }

    return OperandVariable(variable_name,scope_i);
}



// Var
Instruction* Parse_Var(string& operand1,string& operand2)
{
    Var* instruction=new Var
        (Parse_OperandType(operand1),Parse_OperandVariable(operand2));
    
    return (Instruction*)instruction;
}



// Load
Instruction* Parse_Load(string& operand1,string& operand2)
{   
    // LoadConstant
    if(isdigit(operand2[0])||operand2[0]=='\"')
    {
        LoadConstant* instruction=new LoadConstant
            (Parse_OperandRegister(operand1),Parse_OperandConstant(operand2));

        return (Instruction*)instruction;
    }

    // LoadVariable
    LoadVariable* instruction=new LoadVariable
        (Parse_OperandRegister(operand1),Parse_OperandVariable(operand2));
    
    return (Instruction*)instruction;
}

// Store
Instruction* Parse_Store(string& operand1,string& operand2)
{
    Store* instruction=new Store
        (Parse_OperandVariable(operand1),Parse_OperandRegister(operand2));
    
    return (Instruction*)instruction;
}



// Print
Instruction* Parse_Print(string& operand1,string& operand2)
{
    Print* instruction=new Print
        (Parse_OperandRegister(operand1));
    
    return (Instruction*)instruction;
}



// Binary
Instruction* Parse_Add(string& operand1,string& operand2)
{
    Add* instruction=new Add
        (Parse_OperandRegister(operand1),Parse_OperandRegister(operand2));
    
    return (Instruction*)instruction;
}

Instruction* Parse_Sub(string& operand1,string& operand2)
{
    Sub* instruction=new Sub
        (Parse_OperandRegister(operand1),Parse_OperandRegister(operand2));
    
    return (Instruction*)instruction;
}

Instruction* Parse_Mul(string& operand1,string& operand2)
{
    Mul* instruction=new Mul
        (Parse_OperandRegister(operand1),Parse_OperandRegister(operand2));
    
    return (Instruction*)instruction;
}

Instruction* Parse_Div(string& operand1,string& operand2)
{
    Div* instruction=new Div
        (Parse_OperandRegister(operand1),Parse_OperandRegister(operand2));
    
    return (Instruction*)instruction;
}

Instruction* Parse_Mod(string& operand1,string& operand2)
{
    Mod* instruction=new Mod
        (Parse_OperandRegister(operand1),Parse_OperandRegister(operand2));
    
    return (Instruction*)instruction;
}



// Unary
Instruction* Parse_Neg(string& operand1,string& operand2)
{
    Neg* instruction=new Neg
        (Parse_OperandRegister(operand1));

    return (Instruction*)instruction;
}